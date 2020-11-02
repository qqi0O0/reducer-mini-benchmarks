#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "fasttime.h"
#include "defs.h"


void sum_reduce(void* key, void* left, void* right) {
  vector_add((Vector*)left, (Vector*)right);
}

void sum_identity(void* key, void* value) {
  for (int i = 0; i < VECTOR_LEN; i++) {
    ((Vector*)value)->ele[i] = 0;
  }
}

void sum_destroy(void* key, void* value) {
}

typedef CILK_C_DECLARE_REDUCER(Vector) SumReducer;


SumReducer n = CILK_C_INIT_REDUCER(Vector,
    sum_reduce, sum_identity, sum_destroy);


void eval_associative_red(Vector* arr) {
  CILK_C_REGISTER_REDUCER(n);

  fasttime_t start = gettime();
  // Sum
  cilk_for (int i = 0; i < ARR_LEN; i++) {
    vector_add(&REDUCER_VIEW(n), &arr[i]);
  }
  fasttime_t stop = gettime();

  printf("Associative reducer\nElapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), REDUCER_VIEW(n).ele[0]);

  CILK_C_UNREGISTER_REDUCER(n);
}
