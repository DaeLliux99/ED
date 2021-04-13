#include <stdio.h>

typedef int TD;

typedef struct Nodo {
    TD dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
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
    insertarInicio(lista, 20);
    insertarInicio(lista, 30);
    insertarInicio(lista, 40);
    insertarInicio(lista, 50);
    //eliminarFinal(lista);
    mostrarEstructura(lista);
    int i = 2;
    int* pi = &i;
    int* pj = pi;
    (*pi) = 5;
    printf("\n");
    printf("%d\n", *pi);
    printf("%d\n", *pj);
}

void crearLista(Lista* lista) {
    lista->cabeza = NULL;
    lista->longitud = 0;
}

Nodo* crearNodo(TD dato) {
    Nodo* nodo = new(struct Nodo);
    nodo->dato = dato;
    nodo->siguiente = NULL;
    nodo->anterior = NULL;
    return nodo;
}

//Super ineficiente :C
void insertarInicio(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (!lista->cabeza) {
        lista->cabeza = nodo;
        lista->cabeza->siguiente = lista->cabeza;
        lista->cabeza->anterior = lista->cabeza;
    } else {
        lista->cabeza->anterior->siguiente = nodo;
        nodo->anterior = lista->cabeza->anterior;
        nodo->siguiente = lista->cabeza;
        lista->cabeza = nodo;
    }
}

void insertarFinal(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (!lista->cabeza) {
        lista->cabeza = nodo;
        lista->cabeza->siguiente = lista->cabeza;
        lista->cabeza->anterior = lista->cabeza;
    } else {
        lista->cabeza->anterior->siguiente = nodo;
        nodo->anterior = lista->cabeza->anterior;
        nodo->siguiente = lista->cabeza;
        lista->cabeza->anterior = nodo;
    }
}

void eliminarInicio(Lista* lista) {
    if (!lista->cabeza) {
        return;
    }
    Nodo* eliminado;
    if (lista->cabeza->siguiente == lista->cabeza) {
        eliminado = lista->cabeza;
        lista->cabeza = NULL;
        delete eliminado;
    } else {
        eliminado = lista->cabeza;
        lista->cabeza->anterior->siguiente = lista->cabeza->siguiente;
        lista->cabeza->siguiente->anterior = lista->cabeza->anterior;
        lista->cabeza = lista->cabeza->siguiente;
        delete eliminado;
    }
}

void eliminarFinal(Lista* lista) {
    if (!lista->cabeza) {
        return;
    }
    Nodo* eliminado;
    if (lista->cabeza->siguiente == lista->cabeza) {
        eliminado = lista->cabeza;
        lista->cabeza = NULL;
        delete eliminado;
    } else {
        eliminado = lista->cabeza->anterior;
        lista->cabeza->anterior->anterior->siguiente = lista->cabeza;
        lista->cabeza->anterior = lista->cabeza->anterior->anterior;
        delete eliminado;
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
        printf("%d -> ", lista->cabeza->anterior->dato);
    } else {
        printf("No hay elementos en la lista");
    }
}