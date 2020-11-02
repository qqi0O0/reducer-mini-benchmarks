#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "defs.h"


int main() {
  srand(0);

  Vector* arr = (Vector*) malloc(ARR_LEN * sizeof(Vector));
  int* indices = (int*) malloc(NUM_SUM * sizeof(int));
  for (int i = 0; i < ARR_LEN; i++) {
    for (int j = 0; j < VECTOR_LEN; j++) {
      arr[i].ele[j] = rand() % ARR_MAX_ELE;
    }
  }
  for (int i = 0; i < NUM_SUM; i++) {
    indices[i] = rand() % ARR_LEN;
  }

  eval_serial(arr, indices);
  eval_associative_red(arr, indices);
  eval_commutative_red(arr, indices);
}