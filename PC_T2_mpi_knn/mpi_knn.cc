#include <iostream>
#include <cstdlib>
#include <mpi.h>
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

// ESTRUTURA DE ARGUMENTOS PARA MPI
// argumentos[0]->inicio;
// argumentos[1]->fim;
// argumentos[2]->tamanho;
int argumentos[3];
int world_rank, world_size, name_len;
char processor_name[MPI_MAX_PROCESSOR_NAME];

// DISTANCIA EUCLIDIDANA
double distancia_euclidiana(std::vector<double> vec, atr_classe Q, int n) {
  double distancia = 0.0;
  int i;
  for (i = 0; i < n; i++)
    distancia += pow(vec.at(i) - Q.v.at(i), 2);
  distancia = sqrt(distancia);
  return distancia;
}

int main(int argc, char const **argv) {

  // VARIAVEIS
  FILE *treino, *teste;
  char nome_treino[2000], nome_teste[2000];
  const char *tamanho = argv[1];
  int i, j, atributos = atoi(argv[1]);
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

  // INICIALIZANDO MPI
  MPI_Init(NULL, NULL);

  // NUMERO DE PROCESSOS
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  // RANK DOS PROCESSOS
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // NOME DO PROCESSADOR
  MPI_Get_processor_name(processor_name, &name_len);
  MPI_Status status;

  TIME(); // INICIANDO CONTAGEM DE TEMPO
  int salto = floor(matriz_treino.size()/world_size);
  for(i = 0; i < matriz_teste.size(); i++) {
    if(world_rank == 0) {
      argumentos[2] = atributos;

      argumentos[0] = 0;
      argumentos[1] = argumentos[0] + salto;

      for(j = 1; j < world_size; j++) {
        MPI_Send(argumentos, 3, MPI_INT, j, 0, MPI_COMM_WORLD);
        MPI_Send(&matriz_teste.at(i).v.front(), atributos, MPI_DOUBLE, j, 0, MPI_COMM_WORLD);
        MPI_Send(matriz_teste.at(i).classe, 20, MPI_BYTE, j, 0, MPI_COMM_WORLD);
        argumentos[0] = argumentos[1];
        argumentos[1] = argumentos[0] + salto;
      }
      argumentos[1] = atributos;
    } // END IF WORLD_RANK = 0
    else {
      MPI_Recv(argumentos, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
      MPI_Recv(&matriz_teste.at(i).v.front(), atributos, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
      MPI_Recv(matriz_teste.at(i).classe, 20, MPI_BYTE, 0, 0, MPI_COMM_WORLD, &status);
    }

    // K-NN
    int k;
    char classe_processo[20];
    double distancia, menor_distancia_processo = DBL_MAX;
    for(k = argumentos[0]; k < argumentos[1]; k++) {
      distancia = distancia_euclidiana(matriz_teste.at(i).v, matriz_treino.at(k), argumentos[2]);
      if (distancia < menor_distancia_processo) {
        menor_distancia_processo = distancia;
        std::strcpy(classe_processo, matriz_teste.at(i).classe);
      }
    }
    // FIM DO K-NN

    if(world_rank == 0) {
      double menor_distancia;
      char classe[20];
      menor_distancia = menor_distancia_processo;
      std::strcpy(classe, classe_processo);
      for(j = 1; j < world_size; j++) {
        MPI_Recv(&menor_distancia_processo, 1, MPI_DOUBLE, j, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(classe_processo, 20, MPI_BYTE, j, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(menor_distancia_processo < menor_distancia) {
          menor_distancia = menor_distancia_processo;
          std::strcpy(classe, classe_processo);
        }
      }
      predicao.classe = classe;
      predicao.distancia = menor_distancia;
      v_predicoes.push_back(predicao);
    }
    else {
      MPI_Send(&menor_distancia_processo, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
      MPI_Send(classe_processo, 20, MPI_BYTE, 0, 1, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();
  ENDTIME(); // FINALIZANDO CONTAGEM DE TEMPO

  // CALCULANDO TEMPO DE EXECUCAO
  printf("PROCESSOR NAME: %s\n", processor_name);
  elapsed = (finish.tv_sec - start.tv_sec);
  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
  std::cout << elapsed << '\n';

  return 0;
}
