#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "fasttime.h"
#include "defs.h"


void eval_serial(Vector* arr) {
  Vector n = {};

  fasttime_t start = gettime();
  // Sum
  for (int i = 0; i < ARR_LEN; i++) {
    vector_add(&n, &arr[i]);
  }
  fasttime_t stop = gettime();

  printf("Serial\nElapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), n.ele[0]);
}
