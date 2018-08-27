Trabalho 1 - PC
(Paralelizar, usando PThreads e OpenMP, covariance do [Polybench 3.2](http://web.cse.ohio-state.edu/~pouchet.2/software/polybench/)

Para compilar:
gcc -O0 -I utilities -I datamining/covariance utilities/polybench.c datamining/covariance/covariance.c -std=gnu99 -DPOLYBENCH_TIME -DLARGE_DATASET -DPOLYBENCH_DUMP_ARRAYS -o cov_time -fopenmp -pthread

Para executar individualmente:
./cov_time <NT> <EXEC>
   NT (nro_threads): potencias de 2 e 
   EXEC: 0 sequencial, 1 pthread, 2 openmp.

Para executar shell script:
./covariance.sh
