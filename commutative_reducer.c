#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "fasttime.h"

#define ARR_LEN 100000000
#define ARR_MAX_ELE 200
#define CILK_NWORKERS 16


long local_views[CILK_NWORKERS];

long n;


int main() {
  srand(0);

  long* arr = (long*) malloc(ARR_LEN * sizeof(long));
  for (int i = 0; i < ARR_LEN; i++) {
    arr[i] = rand() % ARR_MAX_ELE;
  }

  fasttime_t start = gettime();
  // Sum
  cilk_for (int i = 0; i < ARR_LEN; i++) {
    local_views[__cilkrts_get_worker_number()] += arr[i];
  }
  for (int i = 0; i < CILK_NWORKERS; i++) {
    n += local_views[i];
  }
  fasttime_t stop = gettime();

  printf("Elapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), n);
}
