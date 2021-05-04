#include <inttypes.h>
#include <string.h>


#define PIXEL_MAX_VAL 256


void sum_reduce(void*, void*, void*);
void sum_identity(void*, void*);
void sum_destroy(void*, void*);

int results_ok(int* results);

void eval_associative_red(uint8_t*);
void eval_commutative_red(uint8_t*);
void eval_commutative_red_builtin(uint8_t*);
void eval_serial(uint8_t*);
