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
Nodo* crearNodo(TD dato);

void insertarInicio(Lista* lista, TD dato);
void insertarFinal(Lista* lista, TD dato);

void eliminarInicio(Lista* lista);
void eliminarFinal(Lista* lista);

void mostrarEstructura(Lista* lista);

int main() {
    Lista* lista = new(struct Lista);
    crearLista(lista);
    insertarFinal(lista, 20);
    insertarFinal(lista, 30);
    insertarFinal(lista, 40);
    insertarFinal(lista, 50);
    eliminarFinal(lista);
    mostrarEstructura(lista);
}

void crearLista(Lista* lista) {
    lista->cabeza = NULL;
    lista->longitud = 0;
}

Nodo* crearNodo(TD dato) {
    Nodo* nodo = new(struct Nodo);
    nodo->dato = dato;
    nodo->siguiente = NULL;
    return nodo;
}

//Super ineficiente :C
void insertarInicio(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (!lista->cabeza) {
        lista->cabeza = nodo;
        lista->cabeza->siguiente = lista->cabeza;
    } else {
        Nodo* puntero = lista->cabeza;
        nodo->siguiente = lista->cabeza;
        while (puntero->siguiente != lista->cabeza) {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodo;
        lista->cabeza = nodo;
    }
}

void insertarFinal(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (!lista->cabeza) {
        lista->cabeza = nodo;
        lista->cabeza->siguiente = lista->cabeza;
    } else {
        Nodo *puntero = lista->cabeza;
        while (puntero->siguiente != lista->cabeza){
            puntero = puntero->siguiente;
        }
        nodo->siguiente = lista->cabeza;
        puntero->siguiente = nodo;
    }
}

void eliminarInicio(Lista* lista) {
    Nodo* eliminado;
    if (lista->cabeza->siguiente == lista->cabeza) {
        eliminado = lista->cabeza;
        lista->cabeza = NULL;
        delete eliminado;
    } else {
        Nodo* puntero = lista->cabeza;
        while (puntero->siguiente != lista->cabeza) {
            puntero = puntero->siguiente;
        }
        eliminado = puntero->siguiente;
        lista->cabeza = lista->cabeza->siguiente;
        puntero->siguiente = lista->cabeza;
        delete eliminado;
    }
}

void eliminarFinal(Lista* lista) {
    if (lista->cabeza->siguiente == lista->cabeza) {
        Nodo* eliminado = lista->cabeza;
        lista->cabeza = NULL;
        delete eliminado;
    } else {
        Nodo* puntero = lista->cabeza;
        Nodo* temporal;
        while (puntero->siguiente != lista->cabeza) {
            temporal = puntero;
            puntero = puntero->siguiente;
        }
        temporal->siguiente = lista->cabeza;
        delete puntero;
    }
}

void mostrarEstructura(Lista* lista) {
    if (lista->cabeza) {
        Nodo *puntero = lista->cabeza;
        do {
            printf("%d -> ", puntero->dato);
            puntero = puntero->siguiente;
        } while (puntero != lista->cabeza);
        printf("\n");
    } else {
        printf("No hay elementos en la lista");
    }
}