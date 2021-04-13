#include <stdio.h>

typedef int TD;

typedef struct Nodo {
    struct Nodo* siguiente;
    struct Nodo* anterior;
    TD dato;
}Nodo;

typedef struct Lista {
    Nodo* cabeza;
    int longitud;
}Lista;

void crearLista(Lista* lista);
Nodo* crearNodo(TD dato);

void insertarInicio(Lista* lista, TD dato);
void insertarFinal(Lista* lista, TD dato);
void insertarIndice(Lista* lista, int indice, TD dato);

void eliminarInicio(Lista* lista);
void eliminarFinal(Lista* lista);
void eliminarIndice(Lista* lista, int indice);

void mostrarLista(Lista* lista);
bool estaEnRango(Lista* lista, int indice);

int main() {
    Lista* lista = new(struct Lista);
    crearLista(lista);
    insertarInicio(lista, 10);
    insertarInicio(lista, 20);
    insertarInicio(lista, 30);
    insertarFinal(lista, 40);
    mostrarLista(lista);
    eliminarInicio(lista);
    mostrarLista(lista);
    eliminarFinal(lista);
    mostrarLista(lista);
    insertarIndice(lista, 1, 100);
    mostrarLista(lista);
    eliminarIndice(lista, 3);
    mostrarLista(lista);
}

void crearLista(Lista* lista) {
    lista->cabeza = NULL;
    lista->longitud = 0;
}

Nodo* crearNodo(TD dato) {
    Nodo* nodo = new(struct Nodo);
    nodo->dato = dato;
    nodo->anterior = NULL;
    nodo->siguiente = NULL;
    return nodo;
}

void insertarInicio(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (!lista->cabeza) {
        lista->cabeza = nodo;
    } else {
        nodo->siguiente = lista->cabeza;
        lista->cabeza->anterior = nodo;
        lista->cabeza = nodo;
    }
    lista->longitud++;
}

void insertarFinal(Lista* lista, TD dato) {
    Nodo* nodo = crearNodo(dato);
    if (!lista->cabeza) {
        lista->cabeza = nodo;
    } else {
        Nodo* puntero = lista->cabeza;
        while (puntero->siguiente) {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodo;
        nodo->anterior = puntero;
    }
    lista->longitud++;
}

void insertarIndice(Lista* lista, int indice, TD dato) {
    if (indice == 1) {
        insertarInicio(lista, dato);
    } else {
        Nodo* nodo = crearNodo(dato);
        Nodo* puntero = lista->cabeza;
        int posicion = 1;
        while (puntero->siguiente && posicion < indice - 1) {
            puntero = puntero->siguiente;
            posicion++;
        }
        nodo->siguiente = puntero->siguiente;
        nodo->anterior = puntero;
        puntero->siguiente = nodo;
        lista->longitud++;
    }
}

void mostrarLista(Lista* lista) {
    if (!lista->cabeza) {
        printf("Lista vacia!\n");
    } else {
        Nodo* puntero = lista->cabeza;
        printf("Lista = <");
        while (puntero) {
            printf("%d, ", puntero->dato);
            puntero = puntero->siguiente;
        }
        printf(">>\n");
    }
}

void eliminarInicio(Lista* lista) {
    if (lista->cabeza) {
        Nodo* eliminado = lista->cabeza;
        if (!lista->cabeza->siguiente) {
            lista->cabeza = NULL;
        } else {
            lista->cabeza = lista->cabeza->siguiente;
            lista->cabeza->anterior = NULL;
        }
        delete eliminado;
        lista->longitud--;
    }
}

void eliminarFinal(Lista* lista) {
    if (lista->cabeza) {
        Nodo* eliminado;
        if (lista->cabeza->siguiente) {
            Nodo* puntero = lista->cabeza;
            while (puntero->siguiente->siguiente) {
                puntero = puntero->siguiente;
            }
            eliminado = puntero->siguiente;
            puntero->siguiente = NULL;
        } else {
            eliminado = lista->cabeza;
            lista->cabeza = NULL;
        }
        delete eliminado;
        lista->longitud--;
    }
}

void eliminarIndice(Lista* lista, int indice) {
    Nodo* puntero = lista->cabeza;
    if (estaEnRango(lista, indice)) {
        Nodo* eliminado;
        if (indice == 1) {
            eliminarInicio(lista);
        } else {
            int posicion = 1;
            while (posicion < (indice - 1) && puntero->siguiente) {
                puntero = puntero->siguiente;
                posicion++;
            }
            eliminado = puntero->siguiente;
            puntero->siguiente = eliminado->siguiente;
            eliminado->siguiente = NULL;
            eliminado->anterior = NULL;
            delete eliminado;
            lista->longitud--;
        }
    } else {
        printf("Fuera de rango!\n");
    }
}

bool estaEnRango(Lista* lista, int indice) {
    bool p = indice < 0;
    bool q = indice > lista->longitud;
    return !(p || q);
}