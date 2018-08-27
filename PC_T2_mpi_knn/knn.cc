#include <iostream>
#include <cstdlib>
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

int main(int argc, char const *argv[]) {

  // VARIAVEIS
  FILE *treino, *teste;
  char nome_treino[2000], nome_teste[2000];
  const char *tamanho = argv[1];
  int i, atributos = atoi(argv[1]);
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

  TIME(); // INICIANDO CONTAGEM DE TEMPO
  knn_sequencial(atributos);
  ENDTIME(); // FINALIZANDO CONTAGEM DE TEMPO

  // CALCULANDO TEMPO DE EXECUCAO
  elapsed = (finish.tv_sec - start.tv_sec);
  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
  std::cout << elapsed << '\n';

  return 0;
}
