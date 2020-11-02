#define ARR_LEN 1000
#define ARR_MAX_ELE 200
#define VECTOR_LEN 8
#define NUM_SUM 100000000

typedef struct Vector {
  long ele[VECTOR_LEN];
} Vector;


void vector_add(Vector*, Vector*);

void eval_associative_red(Vector*, int*);
void eval_commutative_red(Vector*, int*);
void eval_serial(Vector*, int*);
