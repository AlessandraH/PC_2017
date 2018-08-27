#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <ctime>
#include <cstring>
#include <vector>
#include <cfloat>
#include <cmath>

// VARIAVEIS E MACROS PARA CALCULAR TEMPO DE EXECUCAO
struct timespec start, finish;
double elapsed;
#define TIME() clock_gettime(CLOCK_MONOTONIC, &start)
#define ENDTIME() clock_gettime(CLOCK_MONOTONIC, &finish)

// DEFININDO ESTRUTURA PARA ARMAZENAR UMA LINHA DO ARQUIVO
typedef struct atr_classe {
  std::vector<double> v;
  char classe[20];
} atr_classe;

// MATRIZES PARA ARMAZENAR DADOS DOS ARQUIVOS
std::vector<atr_classe> matriz_treino, matriz_teste;

// VETOR PARA ARMAZENAR PREDIÇÕES
typedef struct pred {
  char *classe;
  double distancia;
} pred;
pred predicao;
std::vector<pred> v_predicoes;

// DECLARAÇÃO DE VARIAVEIS DE BARREIRA E LOCK
pthread_barrier_t barreira;
pthread_mutex_t lock;

// ESTRUTURA DE ARGUMENTOS PARA PTHREAD
typedef struct argumentos {
  int id_thread, inicio, fim, tam;
} argumentos;

// DISTANCIA EUCLIDIDANA
double distancia_euclidiana(atr_classe P, atr_classe Q, int n) {
  double distancia = 0.0;
  int i;
  for (i = 0; i < n; i++)
    distancia += pow(P.v.at(i) - Q.v.at(i), 2);
  distancia = sqrt(distancia);
  return distancia;
}

// ALGORITMO K-NN SEQUENCIAL
void knn_sequencial(int tam) {
  int i, j;
  double distancia;

  for (i = 0; i < matriz_teste.size(); i++) {
    predicao.distancia = DBL_MAX;
    for (j = 0; j < matriz_treino.size(); j++) {
      distancia = distancia_euclidiana(matriz_teste.at(i), matriz_treino.at(j), tam);
      if (distancia < predicao.distancia) {
        predicao.distancia = distancia;
        predicao.classe = matriz_treino.at(j).classe;
      }
    }
    v_predicoes.push_back(predicao);
  }
}

// ALGORITMO K-NN PARALELO
void *knn_pthread(void *args) {
  int i, j, inicio, fim, id, tam;
  char *classe_thread;
  double distancia, menor_distancia;

  argumentos *a;
  a = (argumentos *) args;
  id = (int) a->id_thread;
  inicio = (int) a->inicio;
  fim = (int) a->fim;
  tam = (int) a->tam;

  for (i = 0; i < matriz_teste.size(); i++) {
    menor_distancia = DBL_MAX;
    predicao.distancia = DBL_MAX;
    for (j = inicio; j < fim; j++) {
      distancia = distancia_euclidiana(matriz_teste.at(i), matriz_treino.at(j), tam);
      if (distancia < menor_distancia) {
        menor_distancia = distancia;
        classe_thread = matriz_treino.at(j).classe;
      }
    }
    pthread_mutex_lock(&lock);
    if (menor_distancia < predicao.distancia) {
      predicao.distancia = menor_distancia;
      predicao.classe = classe_thread;
    }
    pthread_mutex_unlock(&lock);
    if (id == 0) { // APENAS UMA THREAD ADICIONA NO VETOR DE PREDICOES
      v_predicoes.push_back(predicao);
    }
    pthread_barrier_wait(&barreira);
  }
}

int main(int argc, char const *argv[]) {

  // VARIAVEIS
  FILE *treino, *teste;
  char nome_treino[1000], nome_teste[1000];
  const char *tamanho = argv[2];
  int i, op = atoi(argv[1]), atributos = atoi(argv[2]), threads = atoi(argv[3]);
  double atr;
  atr_classe atributos_classe;

  // ABRINDO ARQUIVO DE TREINO EM MODO LEITURA
  std::strcpy(nome_treino, "bases/train_");
  std::strcat(nome_treino, tamanho);
  std::strcat(nome_treino, ".data");
  if((treino = fopen(nome_treino, "r")) == NULL) {
    std::cout << "Erro ao abrir o arquivo de treino!" << '\n';
    exit(1);
  }

  // ABRINDO ARQUIVO DE TESTE EM MODO LEITURA
  std::strcpy(nome_teste, "bases/test_");
  std::strcat(nome_teste, tamanho);
  std::strcat(nome_teste, ".data");
  if((teste = fopen(nome_teste, "r")) == NULL) {
    std::cout << "Erro ao abrir o arquivo de teste!" << '\n';
    exit(1);
  }

  // LER DADOS DE TREINO
  while (fgetc(treino) != EOF) {
    atributos_classe.v.clear();
    for (i = 0; i < atributos; i++) {
      fscanf(treino, "%lf,", &atr);
      atributos_classe.v.push_back(atr);
    }
    fscanf(treino, "%s\n", atributos_classe.classe);
    matriz_treino.push_back(atributos_classe);
  }

  fclose(treino);

  // LER DADOS DE TESTE
  while (fgetc(teste) != EOF) {
    atributos_classe.v.clear();
    for (i = 0; i < atributos; i++) {
      fscanf(teste, "%lf,", &atr);
      atributos_classe.v.push_back(atr);
    }
    fscanf(teste, "%s\n", atributos_classe.classe);
    matriz_teste.push_back(atributos_classe);
  }

  fclose(teste);

  // EXECUTANDO OPCAO: [0] SEQUENCIAL; [1] PARALELO COM PTHREAD
  switch (op) {
    case 0:
      TIME(); // INICIANDO CONTAGEM DE TEMPO
      knn_sequencial(atributos);
      ENDTIME(); // FINALIZANDO CONTAGEM DE TEMPO
      break;
    default:
      pthread_t t[threads]; // VETOR DE THREADS
      pthread_barrier_init(&barreira, NULL, threads);
      pthread_mutex_init(&lock, NULL);
      argumentos args[threads]; // VETOR DE ARGUMENTOS
      int salto = floor(matriz_treino.size()/threads); // QTDE DE DISTANCIAS QUE CADA THREAD VAI CALCULAR
      int a, linha = 0;
      TIME(); // INICIANDO CONTAGEM DE TEMPO
      for (a = 0; a < threads-1; a++) { // CRIACAO DE CADA THREAD COM EXCECAO DA ULTIMA
        args[a].id_thread = a;
        args[a].inicio = linha;
        args[a].fim = linha + salto;
        args[a].tam = atributos;
        pthread_create(&t[a], NULL, knn_pthread, (void *) &args[a]);
        linha = args[a].fim;
      }
      // CRIACAO DA ULTIMA THREAD, VAI CALCULAR O RESTANTE DAS DISTANCIAS
      args[a].id_thread = a;
      args[a].inicio = linha;
      args[a].fim = matriz_treino.size();
      args[a].tam = atributos;
      pthread_create(&t[a], NULL, knn_pthread, (void *) &args[a]);
      for(a = 0; a < threads; a++) {
        pthread_join(t[a], NULL);
      }
      ENDTIME(); // FINALIZANDO CONTAGEM DE TEMPO
      pthread_barrier_destroy(&barreira);
      pthread_mutex_destroy(&lock);
  }

  // CALCULANDO TEMPO DE EXECUCAO
  elapsed = (finish.tv_sec - start.tv_sec);
  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
  std::cout << elapsed << '\n';

  return 0;
}
