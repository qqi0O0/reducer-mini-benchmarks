#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "fasttime.h"
#include "defs.h"

#define CILK_NWORKERS 16


void eval_commutative_red(Vector* arr) {
  Vector local_views[CILK_NWORKERS] = {};
  Vector n = {};

  fasttime_t start = gettime();
  // Sum
  cilk_for (int i = 0; i < ARR_LEN; i++) {
    int worker_number = __cilkrts_get_worker_number();
    vector_add(&local_views[worker_number], &arr[i]);
  }
  for (int i = 0; i < CILK_NWORKERS; i++) {
    vector_add(&n, &local_views[i]);
  }
  fasttime_t stop = gettime();

  printf("Commutative reducer\nElapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), n.ele[0]);
}
