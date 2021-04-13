/*
 * ALUMNO: CARLOS JOYO, Esteban Adrian
*/

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
void insertarEntreNodos(Lista* lista, int indice, TD dato);

void eliminarPrincipio(Lista* lista);
void eliminarFinal(Lista* lista);
void eliminarEntreNodos(Lista* listaA, Lista* listaB, int indice);

void mostrarLista(Lista* lista);

bool estaEnRango(Lista* lista, int indice);

void insertarSuma(Lista* lista);
void insertarPromedio(Lista* listaA, Lista* listaB);
void mostrarListas(Lista* listaA, Lista* listaB);
void transferir(Lista* listaA, Lista* listaB);
int sacarPromedio(Lista* lista);

int main() {
    //Lista l;
    //Lista* lista = &l;
    Lista* listaA = new (struct Lista);
    crearLista(listaA);

    printf("Ejercicio 1: Creando lista ...\n");
    insertarPrincipio(listaA, 10);
    insertarPrincipio(listaA, 20);
    mostrarLista(listaA);
    printf("\n");

    printf("Ejercicio 2: Agregando suma al final de la lista ...\n");
    insertarSuma(listaA);
    mostrarLista(listaA);
    printf("\n");

    printf("Ejercicio 3: Agregando promedio en la lista B ...\n");
    Lista* listaB = new (struct Lista);
    crearLista(listaB);
    insertarPromedio(listaA, listaB);
    mostrarLista(listaA);
    mostrarLista(listaB);
    printf("\n");

    printf("Ejercicio 4.1: Mostrando ambas listas ...\n");
    mostrarListas(listaA, listaB);
    printf("\n");

    printf("Ejercicio 4.2: Transfiriendo ...\n");
    transferir(listaA, listaB);
    mostrarListas(listaA, listaB);
    printf("\n");

    printf("Ejercicio 5: Sacando promedios ...\n");
    printf("Promedio: %d\n",sacarPromedio(listaA));
    printf("Promedio: %d\n",sacarPromedio(listaB));
    printf("\n");
    return 0;
}

//FUNCIONES DEL EJERCICIO

void insertarSuma(Lista* lista) {
    int suma = 0, promedio;
    Nodo* puntero = lista->cabeza;
    while (puntero->siguiente->siguiente) {
        puntero = puntero->siguiente;
    }
    suma = suma + puntero->dato;
    suma = suma + puntero->siguiente->dato;
    insertarFinal(lista, suma);
}

void insertarPromedio(Lista* listaA, Lista* listaB) {
    int suma = 0, promedio = sacarPromedio(listaA);
    insertarFinal(listaB, promedio);
}

int sacarPromedio(Lista* lista) {
    int suma = 0, promedio;
    Nodo* puntero = lista->cabeza;
    while (puntero) {
        suma = suma + puntero->dato;
        puntero = puntero->siguiente;
    }
    promedio = suma / lista->elementos;
    return promedio;
}

void mostrarListas(Lista* listaA, Lista* listaB) {
    printf("A:\n");
    mostrarLista(listaA);
    printf("B:\n");
    mostrarLista(listaB);
}

void transferir(Lista* listaA, Lista* listaB) {
    Lista* indices = new (struct Lista);
    crearLista(indices);
    Nodo* puntero = listaA->cabeza;
    int posicion = 1;
    while (puntero) {
        if (puntero->dato < listaB->cabeza->dato) {
            insertarFinal(indices, posicion);
        };
        posicion++;
        puntero = puntero->siguiente;
    }
    puntero = indices->cabeza;
    while(puntero) {
        eliminarEntreNodos(listaA, listaB, puntero->dato);
        puntero = puntero->siguiente;
    }
}

//FUNCIONES DE LISTA

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

void eliminarEntreNodos(Lista* listaA, Lista* listaB, int indice) {
    Nodo* puntero = listaA->cabeza;
    if (estaEnRango(listaA, indice)) {
        Nodo* eliminado;
        if (indice == 1) {
            eliminado = listaA->cabeza;
            listaA->cabeza = listaA->cabeza->siguiente;
            //destruirNodo(eliminado);
            insertarFinal(listaB, eliminado->dato);
            listaA->elementos--;
        } else {
            int posicion = 1;
            while (posicion < (indice-1) && puntero->siguiente) {
                puntero = puntero->siguiente;
                posicion++;
            }
            eliminado = puntero->siguiente;
            puntero->siguiente = eliminado->siguiente;
            //destruirNodo(eliminado);
            insertarFinal(listaB, eliminado->dato);
            listaA->elementos--;
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