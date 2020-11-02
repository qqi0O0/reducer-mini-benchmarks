#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "defs.h"


int main() {
  srand(0);

  Vector* arr = (Vector*) malloc(ARR_LEN * sizeof(Vector));
  for (int i = 0; i < ARR_LEN; i++) {
    for (int j = 0; j < VECTOR_LEN; j++) {
      arr[i].ele[j] = rand() % ARR_MAX_ELE;
    }
  }

  eval_serial(arr);
  eval_associative_red(arr);
  eval_commutative_red(arr);
}
