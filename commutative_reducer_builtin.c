#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "fasttime.h"
#include "defs.h"


typedef CILK_C_DECLARE_REDUCER(long) ComSumReducer;


ComSumReducer n_com = CILK_C_INIT_COM_REDUCER(long,
    sum_reduce, sum_identity, sum_destroy);


int trial_commutative_builtin(uint8_t* image) {
  COM_REDUCER_VIEW(n_com) = 0;
#pragma cilk grainsize GRAINSIZE
  cilk_for (int j = 0; j < PAR_ITER; j++) {
    COM_REDUCER_VIEW(n_com) += image[j];
  }
  COM_REDUCER_MERGE(n_com);
  return COM_REDUCER_VIEW(n_com);
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
    printf("not ok\n");
    printf("%d %d %d\n", results[0], results[1], results[SER_ITER-1]);
    return;
  }
  printf("%f\t%d\n", tdiff_sec(start, stop), results[0]);

  //CILK_C_UNREGISTER_REDUCER(n_com);
}
