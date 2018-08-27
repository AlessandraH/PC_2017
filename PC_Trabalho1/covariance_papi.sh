#! /bin/bash

gcc -O0 -I utilities -I datamining/covariance -I usr/local/include/ utilities/polybench.c datamining/covariance/covariance_papi.c /usr/local/lib/libpapi.a -o cov_papi -std=gnu99 -DLARGE_DATASET -fopenmp -pthread

printf "Sequencial\n"
./cov_papi 0 2 
./cov_papi 0 2
./cov_papi 0 2
./cov_papi 0 2
./cov_papi 0 2
./cov_papi 0 2
./cov_papi 0 2
./cov_papi 0 2
./cov_papi 0 2
./cov_papi 0 2
./cov_papi 0 2

printf "OpenMP - 8-threads\n"
./cov_papi 2 8
./cov_papi 2 8
./cov_papi 2 8
./cov_papi 2 8
./cov_papi 2 8
./cov_papi 2 8
./cov_papi 2 8
./cov_papi 2 8
./cov_papi 2 8
./cov_papi 2 8
./cov_papi 2 8

printf "PThreads - 8-threads\n"
./cov_papi 1 8
./cov_papi 1 8
./cov_papi 1 8
./cov_papi 1 8
./cov_papi 1 8
./cov_papi 1 8
./cov_papi 1 8
./cov_papi 1 8
./cov_papi 1 8
./cov_papi 1 8
./cov_papi 1 8
