#define ARR_LEN 10000000
#define ARR_MAX_ELE 200
#define VECTOR_LEN 10

typedef struct Vector {
  long ele[10];
} Vector;


void eval_associative_red(long*);
void eval_commutative_red(long*);
void eval_serial(long*);
