/*
 * ALUMNO: CARLOS JOYO, Esteban Adrian 
 */

#include <stdio.h>
#include <stdlib.h>

typedef int TD;

typedef struct Nodo {
    int piso;
    int entran;
    int salen;
    int quedan;
    struct Nodo* siguiente;
    struct Nodo* anterior;
}Nodo;

typedef struct Lista {
    Nodo* cabeza;
    int longitud;
}Lista;

//Funciones de lista
void crearLista(Lista* lista);
Nodo* crearNodo(TD dato);

void insertarInicio(Lista* lista, int piso, int entran, int salen, int quedan);
void insertarFinal(Lista* lista, int piso, int entran, int salen, int quedan);
void insertarIndice(Lista* lista, int indice, TD dato);

void eliminarInicio(Lista* lista);
void eliminarFinal(Lista* lista);
void eliminarIndice(Lista* lista, int indice);

void mostrarLista(Lista* lista);
bool estaEnRango(Lista* lista, int indice);

//Funciones del problema
void inicializarElevador(Lista* lista);
void ascender(Lista* lista);
void descender(Lista* lista);
void contabilizar(Lista* lista);

int main() {
    Lista* lista = new(struct Lista);
    crearLista(lista);
    inicializarElevador(lista);
    mostrarLista(lista);
    ascender(lista);
    printf("\n");
    printf("Ascendiendo...\n");
    mostrarLista(lista);
    contabilizar(lista);
    descender(lista);
    printf("\n");
    printf("Descendiendo...\n");
    mostrarLista(lista);
    contabilizar(lista);
}

//Funciones del problema

void inicializarElevador(Lista* lista) {
    for (int i = 1; i <= 8; i++) {
        insertarInicio(lista, i, 0, 0, 0);
    }
}

void ascender(Lista* lista) {
    Nodo* puntero = lista->cabeza;
    while (puntero->siguiente) {
        puntero = puntero->siguiente;
    }
    while (puntero) {
        int entrada = rand()% (20 + 1);
        if (!puntero->siguiente) {
            puntero->salen = puntero->anterior->quedan;
            puntero->quedan = 0;
        } else if (!puntero->anterior) {
            puntero->salen = puntero->siguiente->quedan;
            puntero->quedan = 0;
        } else {
            puntero->salen = rand() % (puntero->siguiente->quedan + 1);
            puntero->quedan = puntero->siguiente->quedan - puntero->salen;
        }
        if (puntero->quedan + entrada <= 20) {
            puntero->entran = entrada;
        } else {
            puntero->entran = 20 - puntero->quedan;
        }
        puntero->quedan = puntero->quedan + puntero->entran;
        puntero = puntero->anterior;
    }
}

void descender(Lista* lista) {
    Nodo* puntero = lista->cabeza->siguiente;
    while (puntero) {
        int entrada = rand()% (20 + 1);
        if (!puntero->siguiente) {
            puntero->salen = puntero->anterior->quedan;
            puntero->quedan = 0;
        } else if (!puntero->anterior) {
            puntero->salen = puntero->siguiente->quedan;
            puntero->quedan = 0;
        } else {
            puntero->salen = rand() % (puntero->anterior->quedan + 1);
            puntero->quedan = puntero->anterior->quedan - puntero->salen;
        }
        if (puntero->quedan + entrada <= 20) {
            puntero->entran = entrada;
        } else {
            puntero->entran = 20 - puntero->quedan;
        }
        puntero->quedan = puntero->quedan + puntero->entran;
        puntero = puntero->siguiente;
    }
}

void contabilizar(Lista* lista) {
    Nodo* puntero = lista->cabeza;
    int totalEntran = 0, totalSalen = 0;
    while (puntero) {
        totalEntran = totalEntran + puntero->entran;
        totalSalen = totalSalen + puntero->salen;
        puntero = puntero->siguiente;
    }
    printf("La cantidad de personas que subieron en todo el recorrido: %d\n", totalEntran);
    printf("La cantidad de personas que bajaron en todo el recorrido: %d\n", totalSalen);
}

//Funciones de lista

void crearLista(Lista* lista) {
    lista->cabeza = NULL;
    lista->longitud = 0;
}

Nodo* crearNodo(int piso, int entran, int salen, int quedan) {
    Nodo* nodo = new(struct Nodo);
    nodo->piso = piso;
    nodo->entran = entran;
    nodo->salen = salen;
    nodo->quedan = quedan;
    nodo->anterior = NULL;
    nodo->siguiente = NULL;
    return nodo;
}

void insertarInicio(Lista* lista, int piso, int entran, int salen, int quedan) {
    Nodo* nodo = crearNodo(piso,entran,salen,quedan);
    if (!lista->cabeza) {
        lista->cabeza = nodo;
    } else {
        nodo->siguiente = lista->cabeza;
        lista->cabeza->anterior = nodo;
        lista->cabeza = nodo;
    }
    lista->longitud++;
}

void insertarFinal(Lista* lista, int piso, int entran, int salen, int quedan) {
    Nodo* nodo = crearNodo(piso,entran,salen,quedan);
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


/*
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
*/

void mostrarLista(Lista* lista) {
    if (!lista->cabeza) {
        printf("Lista vacia!\n");
    } else {
        Nodo* puntero = lista->cabeza;
        printf("Lista = <\n");
        while (puntero) {
            printf("Piso: %d| Entran: %2d| Salen: %2d| Quedan: %2d \n", 
            puntero->piso, puntero->entran, puntero->salen, puntero->quedan);
            puntero = puntero->siguiente;
        }
        printf(">>\n");
    }
}

/*
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
*/