#! /bin/bash

g++ pthread_knn.cc -o pthread_knn -lpthread

printf "Sequencial\n"
for (( i = 0; i < 11; i++ )); do
  ./pthread_knn 0 154 1
done

printf "Paralelo 2 threads\n"
for (( i = 0; i < 11; i++ )); do
  ./pthread_knn 1 154 2
done

printf "Paralelo 4 threads\n"
for (( i = 0; i < 11; i++ )); do
  ./pthread_knn 1 154 4
done

printf "Paralelo 8 threads\n"
for (( i = 0; i < 11; i++ )); do
  ./pthread_knn 1 154 8
done
