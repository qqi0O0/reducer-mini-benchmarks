#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include "defs.h"


int main() {
  srand(0);

  int8_t* image = (int8_t*) malloc(WIDTH * HEIGHT * sizeof(int8_t));
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int index = i * WIDTH + j;
      image[index] = rand() % PIXEL_MAX_VAL;
    }
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
