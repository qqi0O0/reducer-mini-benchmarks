#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "defs.h"


int main() {
  srand(0);

  cilk_spawn printf("1\n");

  int* image = (int*) malloc(WIDTH * sizeof(int));
  for (int j = 0; j < WIDTH; j++) {
    image[j] = rand() % PIXEL_MAX_VAL;
  }

#if METHOD == 0
  eval_serial(image);
#elif METHOD == 1
  eval_associative_red(image);
#elif METHOD == 2
  eval_commutative_red(image);
#elif METHOD == 3
  eval_commutative_red_builtin(image);
#endif
}
