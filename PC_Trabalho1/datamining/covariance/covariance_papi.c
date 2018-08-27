/**
 * covariance.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <omp.h>
#include "papi.h"

/* Include polybench common header. */
#include <polybench.h>

/* Include benchmark-specific header. */
/* Default data type is double, default size is 4000. */
#include "covariance.h"

#define NUM_EVENTS 6
//#define NUM_COUNTERS 7
//#define MAX_MULTIPLEX_COUNTERS 128

int event[NUM_EVENTS] = {PAPI_L1_TCM, PAPI_L2_TCM, PAPI_L3_TCM, PAPI_FP_INS, PAPI_TOT_CYC, PAPI_TOT_INS};
long long values[NUM_EVENTS];

DATA_TYPE float_n, **data, **symmat, *mean;

pthread_barrier_t barreira;

struct args {
  int colunai, colunaf;
  int n,m;
};

DATA_TYPE **criaMatriz(int l, int c) {
  int i;
  DATA_TYPE **matriz = (DATA_TYPE **) malloc(l * sizeof(DATA_TYPE *));
  for(i=0; i<l; i++) {
    matriz[i] = (DATA_TYPE *) malloc(c * sizeof(DATA_TYPE));
  }
  return matriz;
}

/* Array initialization. */
static void init_array (int m, int n, DATA_TYPE *float_n) {

  int i, j;

  *float_n = 1.2;

  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      data[i][j] = ((DATA_TYPE) i*j) / M;

}


/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */
static void print_array(int m) {

	int i, j;

  for (i = 0; i < m; i++)
    for (j = 0; j < m; j++) {
      fprintf (stderr, DATA_PRINTF_MODIFIER, symmat[i][j]);
      if ((i * m + j) % 20 == 0) fprintf (stderr, "\n");
    }
  fprintf (stderr, "\n");

}


/* Main computational kernel. The whole function will be timed,
   including the call and return. */
static void kernel_covariance(int m, int n, DATA_TYPE float_n) {

	int i, j, j1, j2;

  /* Determine mean of column vectors of input data matrix */
  for (j = 0; j < _PB_M; j++) {
      mean[j] = 0.0;
      for (i = 0; i < _PB_N; i++)
        mean[j] += data[i][j];
      mean[j] /= float_n;
  }

  /* Center the column vectors. */
  for (i = 0; i < _PB_N; i++)
    for (j = 0; j < _PB_M; j++)
      data[i][j] -= mean[j];

  /* Calculate the m * m covariance matrix. */
  for (j1 = 0; j1 < _PB_M; j1++)
    for (j2 = j1; j2 < _PB_M; j2++) {
    		symmat[j1][j2] = 0.0;
        for (i = 0; i < _PB_N; i++)
	       symmat[j1][j2] += data[i][j1] * data[i][j2];
        symmat[j2][j1] = symmat[j1][j2];
      }

}

void *covariance_pthread(void *argumentos) {
  int colunai, colunaf;
	int i, j, j1, j2;
  int n,m;

  struct args *a;
  a = (struct args *) argumentos;
  colunai = (int) a->colunai;
  colunaf = (int) a->colunaf;
  n = (int) a->n;
  m = (int) a->m;

  /* Determine mean of column vectors of input data matrix */
  for (j = colunai; j < colunaf; j++) {
      mean[j] = 0.0;
      for (i = 0; i < _PB_N; i++) {
        mean[j] += data[i][j];
      }
      mean[j] /= float_n;
  }

  /* Center the column vectors. */
  for (i = 0; i < _PB_N; i++) {
    for (j = colunai; j < colunaf; j++) {
      data[i][j] -= mean[j];
    }
  }

  pthread_barrier_wait (&barreira);
  /* Calculate the m * m covariance matrix. */
  for (j1 = colunai; j1 < colunaf; j1++){
    for (j2 = j1; j2 < _PB_M; j2++) {
        symmat[j1][j2] = 0.0;
        for (i = 0; i < _PB_N; i++) {
          symmat[j1][j2] += data[i][j1] * data[i][j2];
        }
        symmat[j2][j1] = symmat[j1][j2];
      }
  }

}

void covariance_openmp(int m, int n, int nt, DATA_TYPE float_n) {

  #pragma omp parallel num_threads(nt)
  {
    /* Determine mean of column vectors of input data matrix */
    #pragma omp for simd
    for (int j = 0; j < _PB_M; j++) {
        mean[j] = 0.0;
        for (int i = 0; i < _PB_N; i++) {
          mean[j] += data[i][j];
        }
        mean[j] /= float_n;
    }

    /* Center the column vectors. */
    #pragma omp for simd
    for (int i = 0; i < _PB_N; i++)
      for (int j = 0; j < _PB_M; j++)
        data[i][j] -= mean[j];

    /* Calculate the m * m covariance matrix. */
    #pragma omp for simd
    for (int j1 = 0; j1 < _PB_M; j1++)
      for (int j2 = j1; j2 < _PB_M; j2++) {
      		symmat[j1][j2] = 0.0;
          for (int i = 0; i < _PB_N; i++) {
  	        symmat[j1][j2] += data[i][j1] * data[i][j2];
          }

          symmat[j2][j1] = symmat[j1][j2];
      }
  }

}

int main(int argc, char** argv) {
  /* Retrieve problem size. */
  int n = N;
  int m = M;

  int exec = atoi(argv[1]);
  int nro_threads = atoi(argv[2]);

  /* Variable declaration/allocation. */
  data = criaMatriz(n,m);
  symmat = criaMatriz(m,m);
  mean = (DATA_TYPE *) malloc(m * sizeof(DATA_TYPE));

  /* Initialize array(s). */
  init_array (m, n, &float_n);

//  /* Start timer. */
//  polybench_start_instruments;

//  PAPI_read_counters(values, NUM_EVENTS);

  switch (exec) {

    case 1: {
      /* Run PThreads */
      if(PAPI_start_counters(event, NUM_EVENTS) != PAPI_OK) {
        printf("Fim do PAPI\n");
	exit(1);
      }
      pthread_t t[nro_threads];
      pthread_barrier_init(&barreira, NULL, nro_threads);
      struct args a[nro_threads];
      int saltoC = m/nro_threads;
      int saltoL = n/nro_threads;
      int coluna = 0;
      for(int i=0; i<nro_threads; i++) {
        a[i].colunai = coluna;
        a[i].colunaf = coluna + saltoC;
        a[i].n = n;
        a[i].m = m;
        pthread_create(&t[i], NULL, covariance_pthread, (void *) &a[i]);
        coluna = a[i].colunaf;
      }
      for(int i=0; i<nro_threads; i++) {
        pthread_join(t[i], NULL);
      }
      pthread_barrier_destroy(&barreira);
    }
    break;

    case 2: {
      /* Run OpenMP */
      if(PAPI_start_counters(event, NUM_EVENTS) != PAPI_OK) {
        printf("Fim do PAPI\n");
	exit(1);
      }
      covariance_openmp (m, n, nro_threads, float_n);
    }
    break;

    default: {
      /* Run kernel. */
      if(PAPI_start_counters(event, NUM_EVENTS) != PAPI_OK) {
        printf("Fim do PAPI\n");
	exit(1);
      }
      kernel_covariance (m, n, float_n);
    }
    break;
  }

  if(PAPI_read_counters(values, NUM_EVENTS) != PAPI_OK) {
    printf("Fim do PAPI no READ!\n");
    exit(1);
  }

  printf("\n\n");
  printf("TOTAL L1 Cache MISS: \t%lld\n", values[0]);
  printf("TOTAL L2 Cache MISS: \t%lld\n", values[1]);
  printf("TOTAL L3 Cache MISS: \t%lld\n", values[2]);
  printf("TOTAL FP Instructions: \t%lld\n", values[3]);
  printf("TOTAL Cycles: \t%lld\n", values[4]);
  printf("TOTAL Instructions: \t%lld\n", values[5]);


//  /* Stop and print timer. */
//  polybench_stop_instruments;
//  polybench_print_instruments;

  /* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  polybench_prevent_dce(print_array(m));

  /* Be clean. */
  free(data);
  free(symmat);
  free(mean);

  return 0;
}
