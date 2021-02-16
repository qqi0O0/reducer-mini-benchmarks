#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "fasttime.h"
#include "defs.h"

#define CILK_NWORKERS 16

// Without "Atomic", reading directly from tls_worker can cause a wrong answer
//extern __thread _Atomic(struct __cilkrts_worker *)tls_worker;
extern __thread struct __cilkrts_worker *tls_worker;


void eval_commutative_red(int* image) {
  Hist* local_views;
  //local_views = malloc(CILK_NWORKERS * sizeof(Hist));
  local_views = aligned_alloc(64 * 8, CILK_NWORKERS * sizeof(Hist));
  memset(local_views, 0, CILK_NWORKERS * sizeof(Hist));

  Hist n = {};

  fasttime_t start = gettime();
  // Sum
  for (int i = 0; i < HEIGHT; i++) {
#pragma cilk grainsize GRAINSIZE
    cilk_for (int j = 0; j < WIDTH; j++) {
      //int worker_number = (int) (*(((uint64_t*) tls_worker) + 4));
      int worker_number = __cilkrts_get_worker_number();
      int index = i * WIDTH + j;
      int pixel = image[index];
      local_views[worker_number].ele[pixel]++;
    }
  }
  for (int i = 0; i < CILK_NWORKERS; i++) {
    hist_add(&n, &local_views[i]);
  }
  fasttime_t stop = gettime();

  printf("%f\t%d\t%d\t%d\n", tdiff_sec(start, stop), n.ele[0], n.ele[1], n.ele[255]);

  free(local_views);
}
