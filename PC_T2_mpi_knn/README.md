# PC_T2_mpi_knn
#### Universidade Estadual de Maringa <br />
#### Programacao Concorrente - Trabalho 2<br />
Neste trabalho deverá ser implementada uma versão simplificada do algoritmo K-NN, fazendo a paralelização dos cálculos realizados sobre os dados da base de conhecimento, onde a classe será dada somente pelo vizinho mais próximo, ou seja, deverá ser implementado o algoritmo K-NN para K=1. Além disso, não é necessário fazer a retenção do novo conhecimento obtido. Serão disponibilizadas 5 bases de conhecimento, todas elas contendo exemplos no contexto de reconhecimento de gêneros musicais. <br />
<br />
Objetivo:
O trabalho tem como objetivo a implementação de uma aplicação paralela, utilizando
troca de mensagens e a elaboração de um relatório, fazendo análises de desempenho da aplicação
implementada.<br />
#### COMPILAR (knn: sequencial e mpi_knn: K-NN com MPI)<br />
$ g++ -lm knn.cc -o knn <br />
$ mpiCC mpi_knn.cc -o mpi_knn <br />
#### EXECUTAR (knn: sequencial e mpi_knn: K-NN com MPI)<br />
$ ./knn ARQ <br />
$ mpirun -np NP mpi_knn ARQ<br />
ARQ (Arquivo/Tamanho da base a ser utilizada): [59]; [161]; [256]; [1380]; [1601].<br />
