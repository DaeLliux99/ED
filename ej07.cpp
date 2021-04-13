/*
 * ALUMNO: CARLOS JOYO, Esteban Adrian
 * Notas: Se utiliza la forma eficiente / practica de las pilas
*/

#include <stdio.h>

typedef int TD;

typedef struct Nodo {
    TD peso;
    bool perecible;
    struct Nodo* siguiente;
}Nodo;

typedef struct Lista {
    Nodo* cabeza;
    int longitud;
    int pesoTotal;
}Lista;

void crearLista(Lista* lista);
Nodo* crearNodo(bool perecible, TD peso);
void push(Lista* lista, bool perecible, TD peso);
void pushCola(Lista* lista, bool perecible, TD peso);
Nodo* pop(Lista* lista);
void trasladar(Lista* listaA, Lista* listaB);
void trasladarColaPila(Lista* cola, Lista* contPerecible,  Lista* contNoPerecible);
void insertarContenedor(Lista* lista, int tipo, bool perecible, TD peso);
void mostrarLista (Lista* lista);

int main() {
    //Pregunta 1
    Lista* cola = new (struct Lista);
    crearLista(cola);
    printf("Pregunta 1: Creando cola...\n");
    insertarContenedor(cola, 3, false, 10);
    insertarContenedor(cola, 3, true, 15);
    insertarContenedor(cola, 3, false, 25);
    insertarContenedor(cola, 3, false, 40);
    insertarContenedor(cola, 3, true, 20);
    insertarContenedor(cola, 3, true, 30);
    insertarContenedor(cola, 3, false, 50);
    insertarContenedor(cola, 3, false, 10);
    printf("- Cola:\n");
    mostrarLista(cola);

    //Pregunta 2
    printf("Pregunta 2: Creando contenedores y transfiriendo de la cola...\n");
    Lista* contPerecible = new (struct Lista);
    Lista* contNoPerecible = new (struct Lista);
    crearLista(contPerecible);
    crearLista(contNoPerecible);
    
    trasladarColaPila(cola, contPerecible, contNoPerecible);
    trasladarColaPila(cola, contPerecible, contNoPerecible);
    trasladarColaPila(cola, contPerecible, contNoPerecible);
    trasladarColaPila(cola, contPerecible, contNoPerecible);
    trasladarColaPila(cola, contPerecible, contNoPerecible);
    printf("- Cola:\n");
    mostrarLista(cola);
    printf("- Contenedor Perecible:\n");
    mostrarLista(contPerecible);
    printf("- Contenedor No Perecible:\n");
    mostrarLista(contNoPerecible);

    //Pregunta 3
    printf("Pregunta 3: Creando camiones y transfiriendo de los contenedores...\n");
    Lista* camionPerecible = new (struct Lista);
    Lista* camionNoPerecible = new (struct Lista);
    crearLista(camionPerecible);
    crearLista(camionNoPerecible);
    trasladar(contPerecible, camionPerecible);
    trasladar(contNoPerecible, camionNoPerecible);
    printf("- Contenedor Perecible:\n");
    mostrarLista(contPerecible);
    printf("- Contenedor No Perecible:\n");
    mostrarLista(contNoPerecible);
    printf("- Camion Perecible:\n");
    mostrarLista(camionPerecible);
    printf("- Camion No Perecible:\n");
    mostrarLista(camionNoPerecible);
    return 0;
}

void crearLista(Lista* lista) {
    lista->cabeza = NULL;
    lista->longitud = 0;
    lista->pesoTotal = 0;
}

Nodo* crearNodo(bool perecible, TD peso) {
    Nodo* nodo = new (struct Nodo);
    nodo->perecible = perecible;
    nodo->peso = peso;
    nodo->siguiente = NULL;
    return nodo;
}

void push(Lista* lista, bool perecible, TD peso) {
    Nodo* nodo = crearNodo(perecible, peso);
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
    lista->longitud++;
    lista->pesoTotal = lista->pesoTotal + peso;
}

void pushCola(Lista* lista, bool perecible, TD peso) {
    Nodo* nodo = crearNodo(perecible, peso);
    if (!lista->cabeza) {
        lista->cabeza = nodo;
    } else {
        Nodo* puntero = lista->cabeza;
        while (puntero->siguiente) {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodo;
    }
    lista->pesoTotal = lista->pesoTotal + peso;
    lista->longitud++;
}

Nodo* pop(Lista* lista) {
    Nodo* nodo = lista->cabeza;
    lista->cabeza = lista->cabeza->siguiente;
    lista->pesoTotal = lista->pesoTotal - nodo->peso;
    lista->longitud--;
    return nodo;
}

void trasladar(Lista* listaA, Lista* listaB) {
    Nodo* nodo = pop(listaA);
    nodo->siguiente = listaB->cabeza;
    listaB->cabeza = nodo;
    listaB->longitud++;
    listaB->pesoTotal = listaB->pesoTotal + nodo->peso;
}

void trasladarColaPila(Lista* cola, Lista* contPerecible,  Lista* contNoPerecible) {
    Nodo* nodo = pop(cola);
    if (nodo->perecible) {
        insertarContenedor(contPerecible, 1, nodo->perecible, nodo->peso);
    } else {
        insertarContenedor(contNoPerecible, 1, nodo->perecible, nodo->peso);
    }
}

void insertarContenedor(Lista* lista, int tipo, bool perecible, TD peso) {
    switch (tipo) {
        case 1: 
        if (lista->pesoTotal + peso <= 500) {
            push(lista, perecible, peso);
        } else {
            printf("Contenedor lleno! ");
        } break;
        case 2:
        if (perecible) {
            if (lista->pesoTotal + peso <= 200) push(lista, perecible, peso);
        } else {
            if (lista->pesoTotal + peso <= 100) push(lista, perecible, peso);
        } break;
        case 3:
            pushCola(lista, perecible, peso);
        break;
    }
}

void mostrarLista (Lista* lista) {
    Nodo* puntero = lista->cabeza;
    printf("Lista: \n");
    while(puntero != NULL) {
        printf("[Peso: %d, %s] ->\n", puntero->peso, (puntero->perecible) ? "perecible" : "no perecible");
        puntero = puntero->siguiente;
    }
    printf("Peso total: %d \n", lista->pesoTotal);
    printf("Numero de elementos: %d \n", lista->longitud);
    printf("\n");
}
