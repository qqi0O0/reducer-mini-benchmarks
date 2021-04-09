#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "fasttime.h"
#include "defs.h"


typedef CILK_C_DECLARE_REDUCER(Hist) ComSumReducer;


ComSumReducer n_com = CILK_C_INIT_COM_REDUCER(Hist,
    sum_reduce, sum_identity, sum_destroy);


void eval_commutative_red_builtin(uint8_t* image) {
  CILK_C_REGISTER_COM_REDUCER(n_com);

  fasttime_t start = gettime();
  // Sum
  for (int i = 0; i < SER_ITER; i++) {
#pragma cilk grainsize GRAINSIZE
    cilk_for (int j = 0; j < PAR_ITER; j++) {
      uint8_t pixel= image[j];
      COM_REDUCER_VIEW(n_com).ele[pixel]++;
    }
  }
  COM_REDUCER_MERGE(n_com);
  fasttime_t stop = gettime();

  printf("%f\t%u\t%u\t%u\n", tdiff_sec(start, stop),
      COM_REDUCER_VIEW(n_com).ele[0],
      COM_REDUCER_VIEW(n_com).ele[1],
      COM_REDUCER_VIEW(n_com).ele[255]);

  //CILK_C_UNREGISTER_REDUCER(n_com);
}
