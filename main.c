/*
FCI
Projeto 2 - Projeto e Análise de Algoritmos II
Grupo:
Lucas Trebacchetti Eiras - 10401973
Joaquim Rafael Mariano Prieto - 10408805
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Predio {
  char nome[100];
  int distancia[12];
  bool selecionado;
};

int main(void) {
  
  FILE *arquivo;
  FILE *resultado;
  int kCentros;
  int numPredios;
  int totalDist;
  char buffer[100];
  arquivo = fopen("entrada.txt", "r");

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  fscanf(arquivo, "%d %d\n", &numPredios, &kCentros);

  struct Predio predios[numPredios];

  for (int i = 0; i < numPredios; i++) {
      fgets(predios[i].nome, sizeof(predios[i].nome), arquivo);
      predios[i].nome[strcspn(predios[i].nome, "\n")] = '\0';
  }


  fscanf(arquivo, "%d\n", &totalDist);

  for(int i=0;i<numPredios;i++){
    for(int j=0;j<numPredios;j++){
      predios[i].distancia[j] = -1;
    }
  }

  int count = 0;
  int distancia;
  int partida;
  int destino;
  for (int i = 0; i < totalDist; i++) {
    fscanf(arquivo, "%d %d %d\n", &partida, &destino, &distancia);
    predios[partida - 1].distancia[destino - 1] = distancia;
    if(partida!=destino){
      predios[destino - 1].distancia[partida - 1] = distancia;
    }
  }

  for(int i=0;i<numPredios;i++){
    predios[i].selecionado = false;
  }


  int centros[kCentros];
  int distancias[numPredios];
  int idxDistancia[numPredios];
  int countDistancias = 0;
  int countCentros = 0;
  centros[0] = 0;
  countCentros++;
  predios[0].selecionado = true;

  for(int i=0;i<kCentros;i++){
    for(int j=0;j<numPredios;j++){
      if(predios[j].selecionado==false){
        int menorDistancia = 900000;
        for(int k=0;k<countCentros;k++){
          if(predios[j].distancia[centros[k]] < menorDistancia){
            menorDistancia = predios[j].distancia[centros[k]];
          }
        }
        idxDistancia[countDistancias] = j;
        distancias[countDistancias] = menorDistancia;
        countDistancias++;
        menorDistancia = 900000;
      }
    }
    int idxMaior = -1;
    int maiorDistancia = -1;
    for(int j=0;j<countDistancias;j++){
      if(distancias[j] > maiorDistancia){
        maiorDistancia = distancias[j];
        idxMaior = idxDistancia[j];
      }
    }
    centros[countCentros] = idxMaior;
    countCentros++;
    predios[idxMaior].selecionado = true;
    countDistancias=0;
  }

  for(int i = 0; i < kCentros; i++){
    printf("Centro %d: %s\n", i+1, predios[centros[i]].nome);
  }

  resultado = fopen("resultado.txt", "w");

  if(resultado == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  for(int i = 0; i<kCentros;i++){
    fprintf(resultado, "Centro %d: %s\n", i+1, predios[centros[i]].nome);
  }
  
  fclose(resultado);
  fclose(arquivo);
  
  return 0;
}