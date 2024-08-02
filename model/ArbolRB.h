#ifndef ARBOLRB_H
#define ARBOLRB_H

#include <string>
#include "Nodo.h"
#include "Dato.h"

class ArbolRB {
public:
    Nodo* root;

    ArbolRB() : root(nullptr) {}
    void insertar(Dato k, int criterio);
    Nodo* buscar(const Dato& otro, int criterio);
    void rotarIzquierda(Nodo*& raiz, Nodo*& pt);
    void rotarDerecha(Nodo*& raiz, Nodo*& pt);
    void balancear(Nodo*& raiz, Nodo*& pt);
};

#endif