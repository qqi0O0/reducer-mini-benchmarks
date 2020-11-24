#include "defs.h"


#if INLINE_HELPER != 1
__attribute__((noinline)) void vector_add(Vector* left, Vector* right) {
  for (int i = 0; i < VECTOR_LEN; i++) {
    left->ele[i] = left->ele[i] + right->ele[i];
  }
}
#endif
