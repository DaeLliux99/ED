/*
* ALUMNO: CARLOS JOYO, Esteban Adrian
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<math.h>

#define MAX 20

typedef int TD;

typedef struct Nodo {
    TD numero;
    struct Nodo* siguiente;
}Nodo;

void initVector(int arreglo[MAX]);
Nodo* crearNodo(TD dato);
void insertarInicio(Nodo** cabeza, TD dato);
void mostrarLista (Nodo* cabeza);
void crearLista(Nodo **cabeza);
void parImpar(Nodo** cabPar, Nodo** cabImpar, int arreglo[]);
void convertir(Nodo* cabeza);
void promedio(Nodo** cabeza);
void insertarFinal(Nodo** cabeza, TD dato);
void unirListas(Nodo** cab1, Nodo** cab2);

int main(){
    int arreglo[MAX];
    Nodo par, impar;
    Nodo* lp = &par;
    Nodo* li = &impar;
    crearLista(&lp);
    crearLista(&li);
    initVector(arreglo);
    //Mostrando Vector
    printf("//Mostrando Vector:\n");
    for (int i = 0; i < MAX; i++) {
      printf("%d ", arreglo[i]); 
    }
    printf("\n\n");
    //Asignando valores del arreglo a la lista
    printf("Asignando valores del arreglo a la lista:\n");
    parImpar(&lp, &li, arreglo);
    mostrarLista(lp);
    mostrarLista(li);
    printf("\n");
    //Convirtiendo par - impar / impar - par
    printf("Convirtiendo par - impar / impar - par:\n");
    convertir(lp);
    convertir(li);
    mostrarLista(lp);
    mostrarLista(li);
    printf("\n");
    //Sacando promedios
    printf("Sacando promedios y agredando al final de la lista:\n");
    promedio(&lp);
    promedio(&li);
    printf("\n");
    //Uniendo listas
    printf("Uniendo listas:");
    unirListas(&lp, &li);
    mostrarLista(lp);
    printf("\n");
    system("pause");
    return 0;
}

void crearLista(Nodo **cabeza) {
    *cabeza = NULL;
}

void initVector(int arreglo[MAX]) {
    for (int i = 0; i < MAX; i++) {
      arreglo[i] = 0 + rand()%(200 + 1); 
    }
}

Nodo* crearNodo(TD dato) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->numero = dato;
    nodo->siguiente = NULL;
    return nodo;
}

void insertarInicio(Nodo** cabeza, TD dato) {
    Nodo* nodo = crearNodo(dato);
    nodo->siguiente = (*cabeza);
    (*cabeza) = nodo;
}

void mostrarLista (Nodo* cabeza) {
    Nodo* puntero = cabeza;
    printf("Lista: ");
    int longitud = 0;
    while(puntero != NULL) {
        printf("%d ->", puntero->numero);
        puntero = puntero->siguiente;
        longitud++;
    }
    printf("\n");
    printf("Numero de elementos: %d \n", longitud);
}

void parImpar(Nodo** cabPar, Nodo** cabImpar, int arreglo[]) {
    for (int i = 0; i < MAX; i++) {
        if (arreglo[i]%2 == 0) {
            insertarInicio(cabPar, arreglo[i]);
        } else {
            insertarInicio(cabImpar, arreglo[i]);
        }
    }
}

void convertir(Nodo* cabeza) {
    Nodo* puntero = cabeza;
    while(puntero != NULL) {
        puntero->numero++;
        puntero = puntero->siguiente;
    }
}

void insertarFinal(Nodo** cabeza, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (nodo == NULL) {
        printf("No hay espacio de memoria! ");
        system("pause");
        exit(0);
    } else {
        if (*cabeza == NULL) {
            *cabeza = nodo;
        } else {
            Nodo* puntero = *cabeza;
            while (puntero->siguiente) {
                puntero = puntero->siguiente;
            }
            puntero->siguiente = nodo;
        }
    }
}

void promedio(Nodo** cabeza) {
    Nodo* puntero = (*cabeza);
    int suma = 0,longitud = 0, promedio = 0;
    while(puntero != NULL) {
        suma = suma + puntero->numero++;
        puntero = puntero->siguiente;
        longitud++;
    }
    promedio = round (suma/longitud) ;
    insertarFinal(cabeza, promedio);
    printf("El promedio es: %d \n", promedio);
}

void unirListas(Nodo** cab1, Nodo** cab2) {
    Nodo* puntero = *cab1;
    Nodo* nodo = *cab2;
    while (puntero->siguiente) {
        puntero = puntero->siguiente;
    }
    puntero->siguiente = nodo;
}