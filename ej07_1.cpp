/*
 * ALUMNO: CARLOS JOYO, Esteban Adrian
 * Notas: Se utiliza la forma eficiente / practica de las pilas
*/

#include <stdio.h>

typedef int TD;

typedef struct Nodo {
    TD dato;
    struct Nodo* siguiente;
}Nodo;

typedef struct Lista {
    Nodo* cabeza;
    int longitud;
}Lista;

void crearLista(Lista* lista);
Nodo* crearNodo(TD peso);
void push(Lista* lista, TD dato);
void pushCola(Lista* lista, TD dato);
Nodo* pop(Lista* lista);
void mostrarLista (Lista* lista);

int main() {
    Lista* cola = new (struct Lista);
    crearLista(cola);
    pushCola(cola, 10);
    pushCola(cola, 20);
    pushCola(cola, 30);
    pushCola(cola, 40);
    pushCola(cola, 50);
    pop(cola);
    mostrarLista(cola);
    Lista* pila = new (struct Lista);
    crearLista(pila);
    push(pila, 10);
    push(pila, 20);
    push(pila, 30);
    push(pila, 40);
    push(pila, 50);
    pop(pila);
    mostrarLista(pila);
    return 0;
}

void crearLista(Lista* lista) {
    lista->cabeza = NULL;
    lista->longitud = 0;
}

Nodo* crearNodo(TD dato) {
    Nodo* nodo = new (struct Nodo);
    nodo->dato = dato;
    nodo->siguiente = NULL;
    return nodo;
}

void push(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
    lista->longitud++;
}

void pushCola(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (!lista->cabeza) {
        lista->cabeza = nodo;
    } else {
        Nodo* puntero = lista->cabeza;
        while (puntero->siguiente) {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodo;
    }
    lista->longitud++;
}

Nodo* pop(Lista* lista) {
    Nodo* nodo = lista->cabeza;
    lista->cabeza = lista->cabeza->siguiente;
    lista->longitud--;
    return nodo;
}

void mostrarLista (Lista* lista) {
    Nodo* puntero = lista->cabeza;
    printf("Lista: \n");
    while(puntero != NULL) {
        printf("%d ->", puntero->dato);
        puntero = puntero->siguiente;
    }
    printf("\n");
    printf("Numero de elementos: %d \n", lista->longitud);
}
