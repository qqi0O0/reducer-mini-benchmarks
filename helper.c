#include "defs.h"


void sum_reduce(void* key, void* left, void* right) {
  *((long *)left) += *((long *)right);
}

void sum_identity(void* key, void* value) {
  *((long *)value) = 0;
}

void sum_destroy(void* key, void* value) {
}

int results_ok(int* results) {
  for (int i = 1; i < SER_ITER; i++) {
    if (results[i] != results[0]) {
      return 0;
    }
  }
  return 1;
}
