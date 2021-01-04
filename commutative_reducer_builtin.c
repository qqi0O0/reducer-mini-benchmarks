#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "fasttime.h"
#include "defs.h"


void sum_identity(void* key, void* value) {
  for (int i = 0; i < VECTOR_LEN; i++) {
    ((Vector*)value)->ele[i] = 0;
  }
}

void sum_destroy(void* key, void* value) {
}

typedef CILK_C_DECLARE_REDUCER(Vector) ComSumReducer;


ComSumReducer n = CILK_C_INIT_COM_REDUCER(Vector,
    vector_add, sum_identity, sum_destroy);


void eval_commutative_red_builtin(Vector* arr, int* indices) {
  CILK_C_REGISTER_COM_REDUCER(n);

  fasttime_t start = gettime();
  // Sum
  for (int j = 0; j < NUM_SUM_OUTER * NUM_SUM_INNER; j += NUM_SUM_INNER) {
#pragma cilk grainsize 1
    cilk_for (int i = 0; i < NUM_SUM_INNER; i++) {
      vector_add(&COM_REDUCER_VIEW(n), &arr[indices[i + j]]);
    }
  }
  COM_REDUCER_MERGE(n);
  fasttime_t stop = gettime();

  long sum = 0;
  for (int i = 0; i < VECTOR_LEN - 2; i++) {
    sum += REDUCER_VIEW(n).ele[i];
  }
  //printf("%f\t%ld\n", tdiff_sec(start, stop), sum);
  printf("%f\t%ld\t%ld\t%ld\n",
      tdiff_sec(start, stop), sum,
      COM_REDUCER_VIEW(n).ele[VECTOR_LEN - 2],
      COM_REDUCER_VIEW(n).ele[VECTOR_LEN - 1]);

  //CILK_C_UNREGISTER_REDUCER(n);
}
