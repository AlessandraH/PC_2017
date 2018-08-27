#! /bin/bash

gcc -O0 -I utilities -I datamining/covariance utilities/polybench.c datamining/covariance/covariance.c -std=gnu99 -DPOLYBENCH_TIME -DLARGE_DATASET -DPOLYBENCH_DUMP_ARRAYS -o cov_time -fopenmp -pthread

printf "Sequencial\n"
./cov_time 0 2 2>results/sequencial/cov_time_seq_1.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_2.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_3.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_4.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_5.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_6.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_7.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_8.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_9.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_10.out
./cov_time 0 2 2>results/sequencial/cov_time_seq_11.out

printf "OpenMP - 2-threads\n"
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_1.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_2.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_3.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_4.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_5.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_6.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_7.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_8.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_9.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_10.out
./cov_time 2 2 2>results/openmp/2-threads/cov_time_omp2t_11.out

printf "OpenMP - 4-threads\n"
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_1.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_2.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_3.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_4.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_5.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_6.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_7.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_8.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_9.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_10.out
./cov_time 2 4 2>results/openmp/4-threads/cov_time_omp4t_11.out

printf "OpenMP - 8-threads\n"
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_1.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_2.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_3.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_4.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_5.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_6.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_7.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_8.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_9.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_10.out
./cov_time 2 8 2>results/openmp/8-threads/cov_time_omp8t_11.out

printf "OpenMP - 16-threads\n"
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_1.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_2.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_3.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_4.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_5.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_6.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_7.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_8.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_9.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_10.out
./cov_time 2 16 2>results/openmp/16-threads/cov_time_omp16t_11.out

printf "OpenMP - 32-threads\n"
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_1.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_2.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_3.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_4.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_5.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_6.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_7.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_8.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_9.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_10.out
./cov_time 2 32 2>results/openmp/32-threads/cov_time_omp32t_11.out

printf "Pthreads - 2-threads\n"
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_1.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_2.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_3.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_4.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_5.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_6.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_7.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_8.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_9.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_10.out
./cov_time 1 2 2>results/pthreads/2-threads/cov_time_pthread2t_11.out

printf "PThreads - 4-threads\n"
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_1.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_2.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_3.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_4.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_5.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_6.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_7.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_8.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_9.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_10.out
./cov_time 1 4 2>results/pthreads/4-threads/cov_time_pthread4t_11.out

printf "PThreads - 8-threads\n"
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_1.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_2.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_3.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_4.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_5.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_6.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_7.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_8.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_9.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_10.out
./cov_time 1 8 2>results/pthreads/8-threads/cov_time_pthread8t_11.out

printf "PThreads - 16-threads\n"
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_1.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_2.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_3.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_4.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_5.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_6.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_7.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_8.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_9.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_10.out
./cov_time 1 16 2>results/pthreads/16-threads/cov_time_pthread16t_11.out

printf "PThreads - 32-threads\n"
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_1.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_2.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_3.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_4.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_5.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_6.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_7.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_8.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_9.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_10.out
./cov_time 1 32 2>results/pthreads/32-threads/cov_time_pthread32t_11.out
