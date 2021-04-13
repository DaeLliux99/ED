/*
    ALUMNO: CARLOS JOYO, Esteban Adrian
*/

#include <stdio.h>

typedef struct Camion {
    char posicion;
    int totalRecorrido;
    int totalKilo;
}Camion;

typedef struct Dato {
    char nombre;
    int distAnterior;
    int distPosterior;
    int kilo;
}Dato;

typedef Dato* TD;

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

Dato* crearDato(char nombre, int distAnterior, int distPosterior, int kilo);
void recorrerIda(Lista* lista, Camion* camion, char inicio, char destino);
void resetearCamion(Camion* camion);
Nodo* buscarNodo(Lista* lista, char nodo);
void recorrerVuelta(Lista* lista, Camion* camion, char inicio, char destino);
void eliminarPorValor(Lista* lista, char nodo);

void mostrarEstructura(Lista* lista);

int main() {
    Lista* lista = new(struct Lista);
    Camion* camion = new(struct Camion);
    crearLista(lista);
    insertarFinal(lista, crearDato('A',16, 7,10));
    insertarFinal(lista, crearDato('B', 7,10,30));
    insertarFinal(lista, crearDato('C',10, 3,20));
    insertarFinal(lista, crearDato('D', 3, 5, 5));
    insertarFinal(lista, crearDato('E', 5,16,50));

    printf("Pregunta 1: Recorriendo de A hasta A: \n");
    recorrerIda(lista, camion, 'A', 'A');
    printf("Total recorrido: %d\n", camion->totalRecorrido);
    printf("Total kilos: %d\n", camion->totalKilo);
    printf("\n");

    printf("Pregunta 2: Recorriendo de C hasta D: \n");
    recorrerIda(lista, camion, 'C', 'D');
    printf("Total recorrido: %d\n", camion->totalRecorrido);
    printf("Total kilos: %d\n", camion->totalKilo);
    printf("\n");

    printf("Pregunta 3: Eliminando C : \n");
    eliminarPorValor(lista, 'C');
    mostrarEstructura(lista);

    printf("Pregunta 4: Creando Nodo F : \n");
    insertarFinal(lista, crearDato('F', lista->cabeza->anterior->dato->distPosterior/2, lista->cabeza->anterior->dato->distPosterior/2, 16));
    mostrarEstructura(lista);

    printf("Pregunta 5: Recorriendo ida y vuelta : \n");
    recorrerIda(lista, camion, 'A', 'E');
    recorrerVuelta(lista, camion, 'E', 'A');
    printf("Total recorrido: %d\n", camion->totalRecorrido);
    printf("Total kilos: %d\n", camion->totalKilo);
    printf("\n");

}

Dato* crearDato(char nombre, int distAnterior, int distPosterior, int kilo) {
    Dato* dato = new(struct Dato);
    dato->nombre = nombre;
    dato->distAnterior = distAnterior;
    dato->distPosterior = distPosterior;
    dato->kilo = kilo;
    return dato;
}

void resetearCamion(Camion* camion) {
    camion->totalRecorrido = 0;
    camion->totalKilo = 0;
}

void recorrerIda(Lista* lista, Camion* camion, char inicio, char destino) {
    resetearCamion(camion);
    Nodo* nodoIni = buscarNodo(lista, inicio);
    Nodo* nodoFin = buscarNodo(lista, destino);
    if (lista->cabeza) {
        if (inicio && destino) {
            Nodo* puntero = nodoIni;
            do {
                printf("Nodo: %c ->", puntero->dato->nombre);
                puntero = puntero->siguiente;
                camion->totalRecorrido = camion->totalRecorrido + puntero->dato->distAnterior;
                camion->totalKilo = camion->totalKilo + puntero->anterior->dato->kilo;
            } while (puntero->dato->nombre != destino);
            printf("Nodo: %c ->", puntero->dato->nombre);
            printf("\n");
        } else {
            printf("No existe un nodo seleccionado\n");
        }
    } else {
        printf("No hay elementos en la lista\n");
    }
}

void recorrerVuelta(Lista* lista, Camion* camion, char inicio, char destino) {
    Nodo* nodoIni = buscarNodo(lista, inicio);
    Nodo* nodoFin = buscarNodo(lista, destino);
    if (lista->cabeza) {
        if (inicio && destino) {
            Nodo* puntero = nodoIni;
            do {
                printf("Nodo: %c ->", puntero->dato->nombre);
                puntero = puntero->anterior;
                camion->totalRecorrido = camion->totalRecorrido + puntero->dato->distPosterior;
                camion->totalKilo = camion->totalKilo + puntero->siguiente->dato->kilo;
            } while (puntero->dato->nombre != destino);
            printf("Nodo: %c ->", puntero->dato->nombre);
            printf("\n");
        } else {
            printf("No existe un nodo seleccionado\n");
        }
    } else {
        printf("No hay elementos en la lista\n");
    }
}

Nodo* buscarNodo(Lista* lista, char nodo) {
    Nodo *puntero = lista->cabeza;
    do {
        if (puntero->dato->nombre == nodo) {
            return puntero;
        }
        puntero = puntero->siguiente;
    } while (puntero != lista->cabeza);
    return NULL;
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
        lista->cabeza->anterior->dato->distPosterior = dato->distAnterior;
        lista->cabeza->dato->distAnterior = dato->distPosterior;
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
            printf("Nodo: %c :\n", puntero->dato->nombre);
            printf("Dist Anterior -> %2d km\n", puntero->dato->distAnterior);
            printf("Dist Posterior-> %2d km\n", puntero->dato->distPosterior);
            printf("Peso          -> %2d Kg\n", puntero->dato->kilo);
            printf("->\n");
            puntero = puntero->siguiente;
        } while (puntero != lista->cabeza);
        printf("\n");
    } else {
        printf("No hay elementos en la lista");
    }
}

void eliminarPorValor(Lista* lista, char nodo) {
    if (!lista->cabeza) {
        return;
    }
    Nodo* eliminado = buscarNodo(lista, nodo);
    if (eliminado) {
        Nodo* eliAnterior = eliminado->anterior;
        Nodo* eliPosterior= eliminado->siguiente;
        eliAnterior->siguiente = eliPosterior;
        eliPosterior->anterior = eliAnterior;
        eliAnterior->dato->distPosterior = eliminado->dato->distPosterior + eliminado->dato->distAnterior;
        eliPosterior->dato->distAnterior = eliAnterior->dato->distPosterior;
        delete eliminado;
    }
}