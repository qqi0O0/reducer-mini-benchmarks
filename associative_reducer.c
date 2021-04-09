#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "fasttime.h"
#include "defs.h"


typedef CILK_C_DECLARE_REDUCER(Hist) SumReducer;


SumReducer n = CILK_C_INIT_REDUCER(Hist,
    sum_reduce, sum_identity, sum_destroy);


int trial_associative(uint8_t* image) {
  for (int i = 0; i < PIXEL_MAX_VAL; i++) {
    REDUCER_VIEW(n).ele[i] = 0;
  }
#pragma cilk grainsize GRAINSIZE
  cilk_for (int j = 0; j < PAR_ITER; j++) {
    uint8_t pixel = image[j];
    REDUCER_VIEW(n).ele[pixel]++;
  }
  return REDUCER_VIEW(n).ele[1] + REDUCER_VIEW(n).ele[2];
}

void eval_associative_red(uint8_t* image) {
  CILK_C_REGISTER_REDUCER(n);

  int* results = (int*) malloc(SER_ITER * sizeof(int));

  fasttime_t start = gettime();
  for (int i = 0; i < SER_ITER; i++) {
    results[i] = trial_associative(image);
  }
  fasttime_t stop = gettime();

  if (!results_ok(results)) {
    return;
  }
  printf("%f\t%d\n", tdiff_sec(start, stop), results[0]);

  CILK_C_UNREGISTER_REDUCER(n);
}
