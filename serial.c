#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "fasttime.h"
#include "defs.h"


void eval_serial(Vector* arr, int* indices) {
  Vector n = {};

  fasttime_t start = gettime();
  // Sum
  for (int i = 0; i < NUM_SUM; i++) {
    vector_add(&n, &arr[indices[i]]);
  }
  fasttime_t stop = gettime();

  printf("Serial\nElapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), n.ele[0]);
}
