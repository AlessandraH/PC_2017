/**
 * covariance.h: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#ifndef COVARIANCE_H
# define COVARIANCE_H

/* Default to STANDARD_DATASET. */
# if !defined(ULTRAMINI_DATASET) && !defined(MINI_DATASET) && !defined(SMALL_DATASET) && !defined(LARGE_DATASET) && !defined(EXTRALARGE_DATASET) && !defined(XXL_DATASET)
#  define STANDARD_DATASET
# endif

/* Do not define anything if the user manually defines the size. */
# if !defined(N) && !defined(M)
/* Define the possible dataset sizes. */
#  ifdef ULTRAMINI_DATASET
#   define N 4
#   define M 4
#  endif

#  ifdef MINI_DATASET
#   define N 32
#   define M 32
#  endif

#  ifdef SMALL_DATASET
#   define N 512
#   define M 512
#  endif

#  ifdef STANDARD_DATASET // Default if unspecified.
#   define N 1024
#   define M 1024
#  endif

#  ifdef LARGE_DATASET
#   define N 2048
#   define M 2048
#  endif

#  ifdef EXTRALARGE_DATASET
#   define N 4096
#   define M 4096
#  endif
# endif /* !N */

#  ifdef XXL_DATASET /* Default if unspecified. */
#   define N 8192
#   define M 8192
#  endif

# define _PB_N POLYBENCH_LOOP_BOUND(N,n)
# define _PB_M POLYBENCH_LOOP_BOUND(M,m)

# ifndef DATA_TYPE
#  define DATA_TYPE double
#  define DATA_PRINTF_MODIFIER "%0.2lf "
# endif


#endif /* !COVARIANCE_H */
