#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "fasttime.h"
#include "defs.h"


void eval_serial(long* arr) {
  Vector n = {};

  fasttime_t start = gettime();
  // Sum
  for (int i = 0; i < ARR_LEN; i++) {
    for (int j = 0; j < VECTOR_LEN; j++) {
      n.ele[j] += arr[i * VECTOR_LEN + j];
    }
  }
  fasttime_t stop = gettime();

  printf("Serial\nElapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), n.ele[0]);
}
