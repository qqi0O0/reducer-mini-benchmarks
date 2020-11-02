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
    for (int j = 0; j < VECTOR_LEN; j++) {
      local_views[worker_number].ele[j] += arr[i].ele[j];
    }
  }
  for (int i = 0; i < CILK_NWORKERS; i++) {
    for (int j = 0; j < VECTOR_LEN; j++) {
      n.ele[j] += local_views[i].ele[j];
    }
  }
  fasttime_t stop = gettime();

  printf("Commutative reducer\nElapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), n.ele[0]);
}
