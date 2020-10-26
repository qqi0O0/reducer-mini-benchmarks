#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "fasttime.h"
#include "defs.h"

#define CILK_NWORKERS 16


Vector local_views[CILK_NWORKERS];

Vector n;


int main() {
  srand(0);

  long* arr = (long*) malloc(ARR_LEN * VECTOR_LEN * sizeof(long));
  for (int i = 0; i < ARR_LEN * VECTOR_LEN; i++) {
    arr[i] = rand() % ARR_MAX_ELE;
  }

  fasttime_t start = gettime();
  // Sum
  cilk_for (int i = 0; i < ARR_LEN; i++) {
    for (int j = 0; j < VECTOR_LEN; j++) {
      local_views[__cilkrts_get_worker_number()].ele[j] += arr[i * VECTOR_LEN + j];
    }
  }
  for (int i = 0; i < CILK_NWORKERS; i++) {
    for (int j = 0; j < VECTOR_LEN; j++) {
      n.ele[j] += local_views[i].ele[j];
    }
  }
  fasttime_t stop = gettime();

  printf("Elapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), n.ele[0]);
}
