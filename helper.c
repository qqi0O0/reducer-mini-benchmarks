#include "defs.h"


#if INLINE_HELPER != 1
__attribute__((noinline)) void hist_add(Hist* left, Hist* right) {
  for (int i = 0; i < VECTOR_LEN; i++) {
    left->ele[i] = left->ele[i] + right->ele[i];
  }
}
#endif

void sum_reduce(void* key, void* left, void* right) {
  Hist* left_h = (Hist*) left;
  Hist* right_h = (Hist*) right;
  hist_add(left_h, right_h);
}

void sum_identity(void* key, void* value) {
  for (int i = 0; i < PIXEL_MAX_VAL; i++) {
    ((Hist*)value)->ele[i] = 0;
  }
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
