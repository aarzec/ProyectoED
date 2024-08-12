#ifndef NODO_LISTA_H
#define NODO_LISTA_H

#include "Dato.h"

class NodoLista {
    public:
        Dato* valor;
        NodoLista* siguiente;

        NodoLista(Dato* val) : valor(val), siguiente(nullptr) {}
};

#endif