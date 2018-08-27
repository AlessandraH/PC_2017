#### Universidade Estadual de Maringa <br />
#### Programacao Concorrente - Trabalho 1<br />
Neste trabalho deverá ser implementada uma versão simplificada do algoritmo K-NN, fazendo a paralelização dos cálculos realizados sobre os dados da base de conhecimento, onde a classe será dada somente pelo vizinho mais próximo, ou seja, deverá ser implementado o algoritmo K-NN para K=1. Além disso, não é necessário fazer a retenção do novo conhecimento obtido. Serão disponibilizadas 5 bases de conhecimento, todas elas contendo exemplos no contexto de reconhecimento de gêneros musicais. <br />
<br />
#### COMPILAR <br />
$ g++ pthread_knn.cc -o pthread_knn -lpthread <br />
#### EXECUTAR <br />
$ ./pthread_knn OP ARQ NTH<br />
OP (Operação): [0] Sequencial; [1] Pthread; <br />
ARQ (Arquivo/Tamanho da base a ser utilizada): [59]; [154]; [256]; ... <br />
NTH (Nro de Threads) <br />
#### SHELL SCRIPT <br />
$ ./pthread_knn.sh <br />
Serão executadas 11 vezes para sequencial e paralelo com 2, 4, e 8 threads
