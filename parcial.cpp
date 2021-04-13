/*
    ALUMNO: CARLOS JOYO, Esteban Adrian
    CODIGO: 18200233
    Notas Importantes: Se esta usando la forma practica para insertar
                        en la pila, no la forma teorica
*/

#include <stdio.h>

typedef struct Contenedor {
    int peso;
    char tipo;
}Contenedor;

typedef Contenedor* TD;

typedef struct Nodo {
    TD dato;
    struct Nodo* siguiente;
}Nodo;

typedef struct Lista {
    Nodo* cabeza;
    int longitud;
}Lista;


//Funciones tipicas de Listas
Lista* crearLista();
Nodo* crearNodo(TD dato);

void insertarFinal(Lista* lista, TD dato);
void trasladar(Lista* listaA, Lista* listaB);
Nodo* pop(Lista* lista);

void mostrarEstructuraCircular(Lista* lista);
void mostrarEstructura (Lista* lista);

//Funciones para los problemas en especifico
Contenedor* crearDato(char tipo, int peso);
void recarga(Lista* cintaT, Lista* pilaA, Lista* pilaB);
void despachar(Lista* pila);

int main() {
    printf("EXAMEN PARCIAL: \n\n");
    //Creando Estructuras e insertando valores
    printf("Pregunta 1: Creando Listas y agregando datos...\n");
    Lista* lista = crearLista();
    Lista* pilaA = crearLista();
    Lista* pilaB = crearLista();
    insertarFinal(lista, crearDato('A', 14));
    insertarFinal(lista, crearDato('B', 9));
    insertarFinal(lista, crearDato('A', 2));
    insertarFinal(lista, crearDato('B', 3));
    insertarFinal(lista, crearDato('B', 4));
    insertarFinal(lista, crearDato('B', 5));
    insertarFinal(lista, crearDato('A', 6));
    insertarFinal(lista, crearDato('A', 7));
    insertarFinal(lista, crearDato('A', 1));
    printf("Cinta transportadora: \n");
    mostrarEstructuraCircular(lista);
    printf("\n");

    printf("Pregunta 2: Recargando hacia las pilas...\n");
    recarga(lista, pilaA, pilaB);
    printf("Cinta transportadora: ");
    mostrarEstructuraCircular(lista);
    printf("Pila A: ");
    mostrarEstructura(pilaA);
    printf("Pila B: ");
    mostrarEstructura(pilaB);
    printf("\n");

    printf("Pregunta 3: Despachando algunos contenedores...\n");
    despachar(pilaA);
    despachar(pilaB);
    return 1;
}

//Funciones tipicas de Listas

Lista* crearLista() {
    Lista* lista = new(struct Lista);
    lista->cabeza = NULL;
    lista->longitud = 0;
    return lista;
}

Nodo* crearNodo(TD dato) {
    Nodo* nodo = new(struct Nodo);
    nodo->dato = dato;
    nodo->siguiente = NULL;
    return nodo;
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

void trasladar(Lista* listaA, Lista* listaB) {
    Nodo* nodo = listaA->cabeza;
    if (listaA->cabeza->siguiente == listaA->cabeza) {
        nodo = listaA->cabeza;
        listaA->cabeza = NULL;
    } else {
        Nodo* puntero = listaA->cabeza;
        while (puntero->siguiente != listaA->cabeza) {
            puntero = puntero->siguiente;
        }
        nodo = puntero->siguiente;
        listaA->cabeza = listaA->cabeza->siguiente;
        puntero->siguiente = listaA->cabeza;
    }
    listaA->longitud--;
    nodo->siguiente = listaB->cabeza;
    listaB->cabeza = nodo;
    listaB->longitud++;
}

Nodo* pop(Lista* lista) {
    Nodo* nodo = lista->cabeza;
    lista->cabeza = lista->cabeza->siguiente;
    lista->longitud--;
    return nodo;
}

void mostrarEstructuraCircular(Lista* lista) {
    if (lista->cabeza) {
        Nodo *puntero = lista->cabeza;
        printf("Lista: ");
        do {
            printf("[%d , %c ]-> ", puntero->dato->peso,puntero->dato->tipo);
            puntero = puntero->siguiente;
        } while (puntero != lista->cabeza);
        printf("\n");
    } else {
        printf("No hay elementos en la lista\n");
    }
}

void mostrarEstructura (Lista* lista) {
    Nodo* puntero = lista->cabeza;
    while(puntero != NULL) {
        printf("[%d , %c ]-> ", puntero->dato->peso,puntero->dato->tipo);
        puntero = puntero->siguiente;
    }
    printf("\n");
}

//Funciones particulares para el problema a resolver

Contenedor* crearDato(char tipo, int peso) {
    Contenedor* cont = new (struct Contenedor);
    cont->tipo = tipo;
    cont->peso = peso;
    return cont;
}

void recarga(Lista* cintaT, Lista* pilaA, Lista* pilaB) {
    if (cintaT->cabeza) {
        Nodo *puntero = cintaT->cabeza;
        bool pilaALlena = false, pilaBLlena = false;
        while (cintaT->cabeza && (!pilaALlena || !pilaBLlena)) {
            if (puntero->dato->tipo == 'A') {
                puntero->dato->peso += 8;
                if (puntero->dato->peso >= 20){
                    puntero = puntero->siguiente;
                    if (pilaA->longitud >= 10) pilaALlena = true;
                    if (!pilaALlena) trasladar(cintaT, pilaA);
                } 
            } else {
                puntero->dato->peso += 4;
                if (puntero->dato->peso >= 30) {
                    puntero = puntero->siguiente;
                    if (pilaA->longitud >= 15) pilaBLlena = true;
                    if (!pilaBLlena) trasladar(cintaT, pilaB);
                }
            }
        }
    }
}

void despachar(Lista* pila) {
    if (pila->cabeza) {
        Nodo* despachado = pop(pila);
        printf("El elemento extraido fue: [%d, %c]\n", despachado->dato->peso, despachado->dato->tipo);
        printf("Pila ahora: \n");
        mostrarEstructura(pila);
    } else {
        printf("No hay elementos! \n");
    }
}