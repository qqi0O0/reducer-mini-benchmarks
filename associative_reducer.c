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


void eval_associative_red(Vector* arr, int* indices) {
  CILK_C_REGISTER_REDUCER(n);

  fasttime_t start = gettime();
  // Sum
  for (int j = 0; j < NUM_SUM_OUTER * NUM_SUM_INNER; j += NUM_SUM_INNER) {
#pragma cilk grainsize 1
    cilk_for (int i = 0; i < NUM_SUM_INNER; i++) {
      vector_add(&REDUCER_VIEW(n), &arr[indices[i + j]]);
    }
  }
  fasttime_t stop = gettime();

  long sum = 0;
  for (int i = 0; i < VECTOR_LEN; i++) {
    sum += REDUCER_VIEW(n).ele[i];
  }
  printf("%f\t%ld\n", tdiff_sec(start, stop), sum);

  CILK_C_UNREGISTER_REDUCER(n);
}
