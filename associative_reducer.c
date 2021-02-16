#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "fasttime.h"
#include "defs.h"


typedef CILK_C_DECLARE_REDUCER(Hist) SumReducer;


SumReducer n = CILK_C_INIT_REDUCER(Hist,
    sum_reduce, sum_identity, sum_destroy);


void eval_associative_red(int* image) {
  CILK_C_REGISTER_REDUCER(n);

  fasttime_t start = gettime();
  // Sum
  for (int i = 0; i < HEIGHT; i++) {
#pragma cilk grainsize GRAINSIZE
    cilk_for (int j = 0; j < WIDTH; j++) {
      int index = i * WIDTH + j;
      int pixel = image[index];
      REDUCER_VIEW(n).ele[pixel]++;
    }
  }
  fasttime_t stop = gettime();

  printf("%f\t%d\t%d\t%d\n", tdiff_sec(start, stop),
      REDUCER_VIEW(n).ele[0],
      REDUCER_VIEW(n).ele[1],
      REDUCER_VIEW(n).ele[255]);

  CILK_C_UNREGISTER_REDUCER(n);
}
