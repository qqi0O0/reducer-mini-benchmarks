#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "fasttime.h"
#include "defs.h"


int trial_serial(uint8_t* image) {
  Hist n = {};
  for (int j = 0; j < PAR_ITER; j++) {
    uint8_t pixel = image[j];
    n.ele[pixel]++;
  }
  return n.ele[1] + n.ele[2];
}

void eval_serial(uint8_t* image) {
  int* results = (int*) malloc(SER_ITER * sizeof(int));

  fasttime_t start = gettime();
  for (int i = 0; i < SER_ITER; i++) {
    results[i] = trial_serial(image);
  }
  fasttime_t stop = gettime();

  if (!results_ok(results)) {
    printf("not ok\n");
    printf("%d %d %d\n", results[0], results[1], results[SER_ITER-1]);
    return;
  }
  printf("%f\t%d\n", tdiff_sec(start, stop), results[0]);
}
