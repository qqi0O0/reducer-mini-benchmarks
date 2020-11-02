#include "defs.h"


void vector_add(Vector* left, Vector* right) {
  for (int i = 0; i < VECTOR_LEN; i++) {
    ((Vector*)left)->ele[i] = ((Vector*)left)->ele[i] + ((Vector*)right)->ele[i];
  }
}
