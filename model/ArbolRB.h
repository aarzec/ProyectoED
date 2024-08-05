#ifndef ARBOLRB_H
#define ARBOLRB_H

#include <string>
#include "Nodo.h"
#include "Dato.h"

class ArbolRB {
public:
    Nodo* root;

    ArbolRB();
    ArbolRB(int criterioOrdenacion);
    void insertar(Dato k);
    Nodo* buscar(const Dato& otro);
    void rotarIzquierda(Nodo*& raiz, Nodo*& pt);
    void rotarDerecha(Nodo*& raiz, Nodo*& pt);
    void balancear(Nodo*& raiz, Nodo*& pt);
    
    void recorrerInOrden();
    void recorrerPreOrden();
    void recorrerPostOrden();

    void setCriterioOrdenacion(int criterio);
private:
    int criterioOrdenacion;
};

#endif