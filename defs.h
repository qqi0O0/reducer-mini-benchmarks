//#define ARR_LEN 10000
//#define VECTOR_LEN 64
#define ARR_MAX_ELE 200
#define NUM_SUM 100000000
#define INLINE_HELPER 0

typedef struct Vector {
  long ele[VECTOR_LEN];
} __attribute__((aligned (64))) Vector;


#if INLINE_HELPER == 1
static inline void vector_add(Vector* left, Vector* right) {
  for (int i = 0; i < VECTOR_LEN; i++) {
    left->ele[i] = left->ele[i] + right->ele[i];
  }
}
#else
__attribute__((noinline)) void vector_add(Vector* left, Vector* right);
#endif

void eval_associative_red(Vector*, int*);
void eval_commutative_red(Vector*, int*);
void eval_serial(Vector*, int*);
