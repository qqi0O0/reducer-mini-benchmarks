#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "fasttime.h"

#define ARR_LEN 100000000
#define ARR_MAX_ELE 200


long n;


int main() {
  srand(0);

  long* arr = (long*) malloc(ARR_LEN * sizeof(long));
  for (int i = 0; i < ARR_LEN; i++) {
    arr[i] = rand() % ARR_MAX_ELE;
  }

  fasttime_t start = gettime();
  // Sum
  for (int i = 0; i < ARR_LEN; i++) {
    n += arr[i];
  }
  fasttime_t stop = gettime();

  printf("Elapsed execution time: %f sec; sum %ld\n",
      tdiff_sec(start, stop), n);
}
