#define ARR_LEN 10000000
#define ARR_MAX_ELE 200
#define VECTOR_LEN 10

typedef struct Vector {
  long ele[VECTOR_LEN];
} Vector;


void eval_associative_red(Vector*);
void eval_commutative_red(Vector*);
void eval_serial(Vector*);
