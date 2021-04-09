#include <inttypes.h>


#define PIXEL_MAX_VAL 256
#define PAR_ITER 10000
#define SER_ITER 10000
#define INLINE_HELPER 1
#define GRAINSIZE 1


typedef struct Hist{
  int ele[PIXEL_MAX_VAL];
} __attribute__((aligned (64))) Hist;


#if INLINE_HELPER == 1
static inline void hist_add(Hist* left, Hist* right) {
  for (int i = 0; i < PIXEL_MAX_VAL; i++) {
    left->ele[i] = left->ele[i] + right->ele[i];
  }
}
#else
__attribute__((noinline)) void vector_add(Hist* left, Hist* right);
#endif

void sum_reduce(void*, void*, void*);
void sum_identity(void*, void*);
void sum_destroy(void*, void*);

void eval_associative_red(int*);
void eval_commutative_red(int*);
void eval_commutative_red_builtin(int*);
void eval_serial(int*);
