#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "fasttime.h"

#define ARR_LEN 100000000
#define ARR_MAX_ELE 200


void sum_reduce(void* key, void* left, void* right) {
  *((long*)left) = *((long*)left) + *((long*)right);
}

void sum_identity(void* key, void* value) {
  *((long*)value) = 0;
}

void sum_destroy(void* key, void* value) {
}

typedef CILK_C_DECLARE_REDUCER(long) SumReducer;


SumReducer n = CILK_C_INIT_REDUCER(long,
    sum_reduce, sum_identity, sum_destroy, 0);


int main() {
  CILK_C_REGISTER_REDUCER(n);

  srand(0);

  long* arr = (long*) malloc(ARR_LEN * sizeof(long));
  for (int i = 0; i < ARR_LEN; i++) {
    arr[i] = rand() % ARR_MAX_ELE;
  }

  fasttime_t start = gettime();
  // Sum
  cilk_for (int i = 0; i < ARR_LEN; i++) {
    REDUCER_VIEW(n) += arr[i];
  }
  fasttime_t stop = gettime();

  printf("Elapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), REDUCER_VIEW(n));

  CILK_C_UNREGISTER_REDUCER(n);
}
