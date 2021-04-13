/*
 * Alumno: CARLOS JOYO, Esteban Adrian
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define columnas 2
#define filas 6
#define MAX 20


int **inicializarMatriz();
void mostrarMatriz(int** matriz);
void mostrarVector(char mensaje[], int vector[], int indice);


int main(){
  int **matriz = inicializarMatriz();
  mostrarMatriz(matriz);
  int indice1 = 0, indice2 = 0, indice3 = 0, indice4 = 0;
  int vectorParesPosi[MAX];
  int vectorImparesPosi[MAX];
  int vectorParesNega[MAX];
  int vectorImparesNega[MAX];

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++){
      int numero = matriz[i][j];
      if (numero%2 == 0){
	      if (numero > 0){
	        vectorParesPosi[indice1] = numero;
	        indice1++;
	      } else {
	        vectorParesNega[indice2] = numero;
	        indice2++;
	      }
      } else {
	      if (numero > 0) {
	        vectorImparesPosi[indice3] = numero;
	        indice3++;
	      } else {
	        vectorImparesNega[indice4] = numero;
	        indice4++;
	      }	
      }
    }
  }
  mostrarVector("Vector de pares positivos: ",vectorParesPosi, indice1);
  mostrarVector("Vector de impares positivos: ",vectorImparesPosi, indice3);
  mostrarVector("Vector de pares negativos: ",vectorParesNega, indice2);
  mostrarVector("Vector de impares negativos: ",vectorImparesNega, indice4);
  return 0;
}

int **inicializarMatriz(){
  int **matriz = (int **)malloc(filas*sizeof(int *));
  for (int i = 0; i < filas; i++) {
    matriz[i] = (int *)malloc(columnas*sizeof(int));
  }
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++){
      matriz[i][j] = -200 + rand()%(200 + 1 +200); 
    }
  }
  return matriz;
}

void mostrarMatriz(int** matriz) {
  printf("Mostrando Matriz: \n");
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++){
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
  printf("____________________________\n");
}

void mostrarVector(char mensaje[], int vector[], int indice){
  printf("%s", mensaje);
  for (int i = 0; i < indice; i++) {
    printf("%d ", vector[i]);
  }
  printf("	Primero: %d", vector[0]);
  printf("	Ultimo: %d", vector[indice - 1]);
  printf("	Medio: %d", vector [indice/2]);
  printf("\n");
}
