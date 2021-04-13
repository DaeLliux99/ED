#include <stdio.h>

typedef int TD;

typedef struct Nodo {
    TD dato;
    struct Nodo* siguiente;
}Nodo;

typedef struct Lista {
    Nodo* cabeza;
    int elementos;
}Lista;

void crearLista(Lista* lista);
Nodo* crearNodo(TD dato);
void destruirNodo(Nodo* nodo);

void insertarPrincipio(Lista* lista, TD dato);
void insertarFinal(Lista* lista, TD dato);
void insertarAntes(int n, Lista* lista, TD dato);
void insertarDespues(int n, Lista* lista, TD dato);
void insertarEntreNodos(Lista* lista, int indice, TD dato);

void eliminarPrincipio(Lista* lista);
void eliminarFinal(Lista* lista);
void eliminarAntes(int n, Lista* lista);
void eliminarDespues(int n, Lista* lista);
void eliminarEntreNodos(Lista* lista, int indice);

void mostrarLista(Lista* lista);

bool estaEnRango(Lista* lista, int indice);

void mergeSort(Lista* lista);
void frontBackSplit();
Nodo* sortedMerge();

int main() {
    //Lista l;
    //Lista* lista = &l;
    Lista* lista = new (struct Lista);
    crearLista(lista);
    insertarPrincipio(lista, 10);
    insertarPrincipio(lista, 20);
    insertarPrincipio(lista, 30);
    insertarPrincipio(lista, 40);
    insertarPrincipio(lista, 50);
    insertarPrincipio(lista, 60);
    eliminarEntreNodos(lista, 6);
    mostrarLista(lista);
    return 0;
}

void crearLista(Lista* lista) {
    lista->cabeza = NULL;
    lista->elementos = 0;
}

Nodo* crearNodo(TD dato) {
    Nodo* nodo = new (struct Nodo);
    nodo->dato = dato;
    nodo->siguiente = NULL;
    return nodo;
}

void insertarPrincipio(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
    lista->elementos++;
}

void insertarFinal(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (lista->cabeza) {
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

void insertarEntreNodos(Lista* lista, int indice, TD dato) {
    Nodo* nodo = crearNodo(dato);
    Nodo* puntero = lista->cabeza;
    if (lista->cabeza == NULL) {
        nodo->siguiente = lista->cabeza;
        lista->cabeza = nodo;
        lista->elementos++;
    } else if (indice == 1) {
        insertarPrincipio(lista, dato);
    } else {
        int posicion = 1;
        while (puntero->siguiente && posicion < indice - 1) {
            printf("%d\n", puntero->dato);
            puntero = puntero->siguiente;
            posicion++;
        }
        nodo->siguiente = puntero->siguiente;
        puntero->siguiente = nodo;
        lista->elementos++;
    }
}

void mostrarLista (Lista* lista) {
    Nodo* puntero = lista->cabeza;
    printf("Lista: ");
    while(puntero != NULL) {
        printf("%d ->", puntero->dato);
        puntero = puntero->siguiente;
    }
    printf("\n");
    printf("Numero de elementos: %d \n", lista->elementos);
}

void eliminarEntreNodos(Lista* lista, int indice) {
    Nodo* puntero = lista->cabeza;
    if (estaEnRango(lista, indice)) {
        Nodo* eliminado;
        if (indice == 1) {
            eliminado = lista->cabeza;
            lista->cabeza = lista->cabeza->siguiente;
            //destruirNodo(eliminado);
        } else {
            int posicion = 1;
            while (posicion < (indice-1) && puntero->siguiente) {
                puntero = puntero->siguiente;
                posicion++;
            }
            eliminado = puntero->siguiente;
            puntero->siguiente = eliminado->siguiente;
            //destruirNodo(eliminado);
        }
    } else {
        printf("Fuera de rango \n");
    }
}

bool estaEnRango(Lista* lista, int indice) {
    bool p = indice < 0;
    bool q = indice > lista->elementos;
    return !(p || q);
}

