#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "fasttime.h"
#include "defs.h"


Vector n;


int main() {
  srand(0);

  long* arr = (long*) malloc(ARR_LEN * VECTOR_LEN * sizeof(long));
  for (int i = 0; i < ARR_LEN * VECTOR_LEN; i++) {
    arr[i] = rand() % ARR_MAX_ELE;
  }

  fasttime_t start = gettime();
  // Sum
  for (int i = 0; i < ARR_LEN; i++) {
    for (int j = 0; j < VECTOR_LEN; j++) {
      n.ele[j] += arr[i * VECTOR_LEN + j];
    }
  }
  fasttime_t stop = gettime();

  printf("Elapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), n.ele[0]);
}
