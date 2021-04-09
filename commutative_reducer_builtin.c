#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "fasttime.h"
#include "defs.h"


typedef CILK_C_DECLARE_REDUCER(Hist) ComSumReducer;


ComSumReducer n_com = CILK_C_INIT_COM_REDUCER(Hist,
    sum_reduce, sum_identity, sum_destroy);


int trial_commutative_builtin(uint8_t* image) {
#pragma cilk grainsize GRAINSIZE
  cilk_for (int j = 0; j < PAR_ITER; j++) {
    uint8_t pixel = image[j];
    COM_REDUCER_VIEW(n_com).ele[pixel]++;
  }
  COM_REDUCER_MERGE(n_com);
  int result = COM_REDUCER_VIEW(n_com).ele[1] + COM_REDUCER_VIEW(n_com).ele[2];

  for (int i = 0; i < PIXEL_MAX_VAL; i++) {
    COM_REDUCER_VIEW(n_com).ele[i] = 0;
  }

  return result;
}

void eval_commutative_red_builtin(uint8_t* image) {
  CILK_C_REGISTER_COM_REDUCER(n_com);

  int* results = (int*) malloc(SER_ITER * sizeof(int));

  fasttime_t start = gettime();
  for (int i = 0; i < SER_ITER; i++) {
    results[i] = trial_commutative_builtin(image);
  }
  fasttime_t stop = gettime();

  if (!results_ok(results)) {
    return;
  }
  printf("%f\t%d\n", tdiff_sec(start, stop), results[0]);

  //CILK_C_UNREGISTER_REDUCER(n_com);
}
