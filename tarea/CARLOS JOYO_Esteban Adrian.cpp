/*
    ALUMNO: CARLOS JOYO, Esteban Adrian
    CODIGO: 18200233
*/

#include <stdio.h>
#include <stdlib.h>

typedef int TD;

typedef struct Nodo {
    TD valor;
    struct Nodo* izdo;
    struct Nodo* dcho;
} Nodo;

int acumulado = 1;

Nodo* crearNodo(TD valor) {
    Nodo* nodo = new (struct Nodo);
    nodo->valor = valor;
    nodo->dcho = NULL;
    nodo->izdo = NULL;
    return nodo;
}

void insertar(Nodo* raiz, TD valor) {
    if (acumulado > 7) {
        return;
    }
    Nodo* nodo = crearNodo(valor);
    Nodo* x = raiz;
    Nodo* y = NULL;

    while (x != NULL) {
        y = x;
        if (valor < x->valor) {
            x = x->izdo;
        } else {
            x = x->dcho;
        }
    }
    if (y == NULL) {
        y = nodo;
    } else if (valor < y->valor) {
        y->izdo = nodo;
    } else {
        y->dcho = nodo;
    }
    acumulado++;
}

void preorden(Nodo* raiz) {
    if (raiz == NULL) {
        return;
    }
    printf(" %d ", raiz->valor);
    preorden(raiz->izdo);
    preorden(raiz->dcho);
}

void inorden(Nodo* raiz) {
    if (raiz == NULL) {
        return;
    }
    inorden(raiz->izdo);
    printf(" %d ", raiz->valor);
    inorden(raiz->dcho);
}

void postorden(Nodo* raiz) {
    if (raiz == NULL) {
        return;
    }
    postorden(raiz->izdo);
    postorden(raiz->dcho);
    printf(" %d ", raiz->valor);
}

int main() {
    Nodo* raiz = crearNodo(30);
    insertar(raiz, 20);
    insertar(raiz, 40);
    insertar(raiz, 70);
    insertar(raiz, 60);
    insertar(raiz, 80);
    printf("Recorrido Inorden\n");
    inorden(raiz);
    printf("\n");
    printf("Recorrido Preorden\n");
    preorden(raiz);
    printf("\n");
    printf("Recorrido Postorden\n");
    postorden(raiz);
    printf("\n");
    printf("%d\n", acumulado);
    return 0;
}
