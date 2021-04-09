#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "fasttime.h"
#include "defs.h"


void eval_serial(int* image) {
  Hist n = {};

  fasttime_t start = gettime();
  // Collect
  for (int i = 0; i < SER_ITER; i++) {
    for (int j = 0; j < PAR_ITER; j++) {
      int pixel = image[j];
      n.ele[pixel]++;
    }
  }
  fasttime_t stop = gettime();

  printf("%f\t%d\t%d\t%d\n", tdiff_sec(start, stop), n.ele[0], n.ele[1], n.ele[255]);
}
