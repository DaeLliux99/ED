/*
    Alumno: CARLOS JOYO, Esteban Adrian
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

Lista* crearLista();
Nodo* crearNodo(TD dato);
void destruirNodo(Nodo* nodo);

void insertarPrincipio(Lista* lista, TD dato);
void insertarFinal(Lista* lista, TD dato);
void insertarPorIndice(Lista* lista, int indice, TD dato);

void eliminarPrincipio(Lista* lista);
void eliminarFinal(Lista* lista);
void eliminarPorIndice(Lista* lista, int indice);

void mostrarLista(Lista* lista);

bool estaEnRango(Lista* lista, int indice);

//Ejercicios funciones

void dividirEnteros(Lista* listaM, Lista* listaP, Lista* listaN);
void trasladar(Lista* listaA, Lista* listaB);
void trasladarAFin(Lista* listaA, Lista* listaB);

void ordenBurbuja(Lista* lista);
void intercambiar(Nodo* nodoA, Nodo* nodoB);
void ordenSeleccion(Lista* lista);

//Busqueda Binaria
Nodo* busquedaBinaria(Lista* lista, TD dato);
Nodo* sacarMedio(Nodo* inicio, Nodo* fin);
void busqueda(Lista* lista, TD dato);

//Radix Sort

TD obtenerMaximo(Lista* lista);
int obtenerDigito(int numero, int cifra);
int obtenerTotalDigito(int numero);
void radixSort(Lista* lista);

//QuickSort
void quickSort(Lista* lista);
Nodo* quickSortRecursivo(Nodo* cabeza, Nodo* fin);
Nodo* obtenerFinal(Nodo* puntero);
Nodo* particion(Nodo* cabeza, Nodo* fin, Nodo** nuevaCabeza, Nodo**nuevoFin);

int main() {
    //Lista l;
    //Lista* lista = &l;
    Lista* lista = crearLista();
    insertarPrincipio(lista,  1);
    insertarPrincipio(lista,  20);
    insertarPrincipio(lista,  10);
    insertarPrincipio(lista,  30);
    insertarPrincipio(lista,  60);
    insertarPrincipio(lista,  120);
    insertarPrincipio(lista,  200);
    insertarPrincipio(lista,  134);
    printf("Pregunta 1: \n");
    printf("Lista Entera: \n");
    mostrarLista(lista);
    quickSort(lista);
    mostrarLista(lista);
    return 0;
}

Lista* crearLista() {
    Lista* lista = new (struct Lista);
    lista->cabeza = NULL;
    lista->elementos = 0;
    return lista;
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
    if (!lista->cabeza) {
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

void insertarPorIndice(Lista* lista, int indice, TD dato) {
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
        printf("[%d] ->", puntero->dato);
        puntero = puntero->siguiente;
    }
    printf("\n");
    printf("Numero de elementos: %d \n", lista->elementos);
}

void eliminarPorIndice(Lista* lista, int indice) {
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

//Dividir

void dividirEnteros(Lista* listaM, Lista* listaP, Lista* listaN) {
    Nodo* puntero = listaM->cabeza;
    while (puntero) {
        if (puntero->dato < 0) {
            puntero = puntero->siguiente;
            trasladar(listaM, listaN);
        } else {
            puntero = puntero->siguiente;
            trasladar(listaM, listaP);
        }
    }
}

void trasladar(Lista* listaA, Lista* listaB) {
    Nodo* nodo = listaA->cabeza;
    listaA->cabeza = listaA->cabeza->siguiente;
    listaA->elementos--;
    nodo->siguiente = listaB->cabeza;
    listaB->cabeza = nodo;
    listaB->elementos++;
}

void trasladarAFin(Lista* listaA, Lista* listaB) {
    Nodo* nodo = listaA->cabeza;
    listaA->cabeza = listaA->cabeza->siguiente;
    listaA->elementos--;

    nodo->siguiente = NULL;
    if (!listaB->cabeza) {
        listaB->cabeza = nodo;
    } else {
        Nodo* puntero = listaB->cabeza;
        while (puntero->siguiente) {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodo;
    }
    listaB->elementos++;
}

//BubbleSort

void ordenBurbuja(Lista* lista) {
    bool intercambiado;
    Nodo* puntero;
    if (!lista->cabeza) {
        return;
    }
    do {
        intercambiado = false;
        puntero = lista->cabeza;
        while (puntero->siguiente) {
            if (puntero->dato > puntero->siguiente->dato) {
                intercambiar(puntero, puntero->siguiente);
                intercambiado = true;
            }
            puntero = puntero->siguiente;
        }
    } while (intercambiado);
}

void intercambiar(Nodo* nodoA, Nodo* nodoB) {
    TD temporal = nodoA->dato;
    nodoA->dato = nodoB->dato;
    nodoB->dato = temporal;
}

//Selection Sort

void ordenSeleccion(Lista* lista) {
    Nodo* puntero = lista->cabeza;
    while (puntero) {
        Nodo* minimo = puntero;
        Nodo* temporal = puntero->siguiente;
        while (temporal) {
            if (minimo->dato > temporal->dato) {
                minimo = temporal;
            }
            temporal = temporal->siguiente;
        }
        intercambiar(puntero, minimo);
        puntero = puntero->siguiente;
    }
}

Nodo* sacarMedio(Nodo* inicio, Nodo* fin) {
    if (!inicio) {
        return NULL;
    }
    Nodo* lento = inicio;
    Nodo* rapido = inicio->siguiente;

    while (rapido != fin) {
        rapido = rapido->siguiente;
        if (rapido != fin) {
            lento = lento->siguiente;
            rapido = rapido->siguiente;
        }
    }

    return lento;   
}

Nodo* busquedaBinaria(Lista* lista, TD dato) {
    Nodo* inicio = lista->cabeza;
    Nodo* fin = NULL;
    do {
        Nodo* medio = sacarMedio(inicio, fin);
        if (medio == NULL) {
            return NULL;
        }

        if (medio->dato == dato) {
            return medio;
        } else if (medio->dato < dato) {
            inicio = medio->siguiente;
        } else {
            fin = medio;
        }
    } while (fin == NULL || fin != inicio);
    return NULL;
}

void busqueda(Lista* lista, TD dato) {
    if (busquedaBinaria(lista, 30)) {
        printf("Encontrado\n");
    } else {
        printf("No se encontro el valor\n");
    }
}

//Radix Sort

TD obtenerMaximo(Lista* lista) {
    Nodo* puntero = lista->cabeza;
    TD maximo = lista->cabeza->dato;
    while (puntero) {
        if (maximo < puntero->dato) {
            maximo = puntero->dato;
        }
        puntero = puntero->siguiente;
    }
    return maximo;
}

int obtenerTotalDigito(int numero) {
    int total = 0;
    while (numero != 0) {
        numero = numero/10;
        total++;
    }
    return total;
}

int obtenerDigito(int numero, int cifra) {
    int digito = 0, i = 1;
    while (i <= cifra) {
        digito = numero % 10;
        numero = numero/10;
        i++;
    }
    return digito;
}

void radixSort(Lista* lista) {
    if (!lista->cabeza) {
        return;
    }
    Lista* arregloListas[10];
    for (int i=0; i<10; i++) {
        arregloListas[i] = crearLista();
    }
    TD maximo = obtenerMaximo(lista);
    int totalDigitoMaximo = obtenerTotalDigito(maximo);
    int i = 1;
    while (i <= totalDigitoMaximo) {
        Nodo* puntero = lista->cabeza;
        while (puntero) {
            int digitoPuntero = obtenerDigito(puntero->dato, i);
            puntero = puntero->siguiente;
            trasladarAFin(lista, arregloListas[digitoPuntero]);
        }
        int j = 0;
        while (j < 10) {
            while (arregloListas[j]->cabeza) {
                trasladarAFin(arregloListas[j], lista);
            }
            j++;
        }
        i++;
    }
}

Nodo* particion(Nodo* cabeza, Nodo* fin, Nodo** nuevaCabeza, Nodo**nuevoFin) {
    Nodo* pivote = fin;
    Nodo *previo = NULL, *puntero = cabeza, *cola = pivote;

    while (puntero != pivote) {
        if (puntero->dato < pivote->dato) {
            if ((*nuevaCabeza) == NULL) {
                (*nuevaCabeza) = puntero;
            }
            previo = puntero;
            puntero = puntero->siguiente;
        } else {
            if (previo) {
                previo->siguiente = puntero->siguiente;
            }
            Nodo* temporal = puntero->siguiente;
            puntero->siguiente = NULL;
            cola->siguiente = puntero;
            cola = puntero;
            puntero = temporal;
        }
    }

    if ((*nuevaCabeza) == NULL) {
        (*nuevaCabeza) = pivote;
    }

    (*nuevoFin) = cola;
    return pivote;
}

Nodo* quickSortRecursivo(Nodo* cabeza, Nodo* fin) {
    if (!cabeza || cabeza == fin) {
        return cabeza;
    }
    Nodo* nuevaCabeza = NULL, *nuevoFin = NULL;
    
    Nodo* pivote = particion(cabeza, fin, &nuevaCabeza, &nuevoFin);

    if (nuevaCabeza != pivote) {
        Nodo* temporal = nuevaCabeza;
        while (temporal->siguiente != pivote) {
            temporal = temporal->siguiente;
        }
        temporal->siguiente = NULL;

        nuevaCabeza = quickSortRecursivo(nuevaCabeza, temporal);

        temporal = obtenerFinal(nuevaCabeza);
        temporal->siguiente = pivote;
    }
    pivote->siguiente = quickSortRecursivo(pivote->siguiente, nuevoFin);
    return nuevaCabeza;
}

Nodo* obtenerFinal(Nodo* puntero) {
    while (puntero != NULL && puntero->siguiente != NULL) {
        puntero = puntero->siguiente;
    }
    return puntero;
}

void quickSort(Lista* lista) {
    lista->cabeza = quickSortRecursivo(lista->cabeza, obtenerFinal(lista->cabeza));
}