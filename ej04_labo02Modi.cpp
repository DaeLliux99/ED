/*
* ALUMNO: CARLOS JOYO, Esteban Adrian
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define MAX 20

typedef int TD;

typedef struct Nodo {
    TD numero;
    struct Nodo* siguiente;
}Nodo;

typedef struct Lista {
    Nodo* cabeza;
    int elementos;
}Lista;

void initVector(int arreglo[MAX]);
Nodo* crearNodo(TD dato);
void insertarInicio(Lista* lista, TD dato);
void mostrarLista (Lista* lista);
void crearLista(Lista* lista);
void parImpar(Lista* listPar, Lista* listImpar, int arreglo[]);
void convertir(Lista* lista);
void promedio(Lista* lista);
void insertarFinal(Lista* lista, TD dato);
void unirListas(Lista* lista1, Lista* lista2);

int main() {
    int arreglo[MAX];
    Lista par, impar;
    Lista* lp = &par;
    Lista* li = &impar;

    //Inicializando la lista y el arreglo
    crearLista(lp);
    crearLista(li);
    initVector(arreglo);

    //Mostrando Vector
    printf("//Mostrando Vector:\n");
    for (int i = 0; i < MAX; i++) {
      printf("%d ", arreglo[i]); 
    }
    printf("\n\n"); 

    //Asignando valores del arreglo a la lista
    printf("Asignando valores del arreglo a la lista:\n");
    parImpar(lp, li, arreglo);
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
    promedio(lp);
    promedio(li);
    printf("\n");

    //Uniendo listas
    printf("Uniendo listas:\n");
    unirListas(lp, li);
    mostrarLista(lp);
    printf("\n");
    system("pause");
    return 0;
}

void crearLista(Lista* lista) {
    lista->cabeza = NULL;
    lista->elementos = 0;
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

void insertarInicio(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
    lista->elementos++;
}

void mostrarLista (Lista* lista) {
    Nodo* puntero = lista->cabeza;
    printf("Lista: ");
    while(puntero != NULL) {
        printf("%d ->", puntero->numero);
        puntero = puntero->siguiente;
    }
    printf("\n");
    printf("Numero de elementos: %d \n", lista->elementos);
}

void parImpar(Lista* listPar, Lista* listImpar, int arreglo[]) {
    for (int i = 0; i < MAX; i++) {
        if (arreglo[i]%2 == 0) {
            insertarInicio(listPar, arreglo[i]);
        } else {
            insertarInicio(listImpar, arreglo[i]);
        }
    }
}

void convertir(Lista* lista) {
    Nodo* puntero = lista->cabeza;
    while(puntero != NULL) {
        (puntero->numero)++;
        puntero = puntero->siguiente;
    }
}

void insertarFinal(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (nodo == NULL) {
        printf("No hay espacio de memoria! ");
        system("pause");
        exit(0);
    } else {
        if (lista->cabeza == NULL) {
            lista->cabeza = nodo;
        } else {
            Nodo* puntero = lista->cabeza;
            while (puntero->siguiente) {
                puntero = puntero->siguiente;
            }
            puntero->siguiente = nodo;
        }
        lista->elementos++;
    }
}

void promedio(Lista* lista) {
    Nodo* puntero = lista->cabeza;
    int suma = 0,longitud = 0, promedio = 0;
    while(puntero != NULL) {
        suma = suma + puntero->numero;
        puntero = puntero->siguiente;
        longitud++;
    }
    promedio = round (suma/longitud) ;
    insertarFinal(lista, promedio);
    printf("El promedio es: %d \n", promedio);
}

void unirListas(Lista* lista1, Lista* lista2) {
    Nodo* puntero = lista1->cabeza;
    Nodo* nodo = lista2->cabeza;
    while (puntero->siguiente) {
        puntero = puntero->siguiente;
    }
    puntero->siguiente = nodo;
}