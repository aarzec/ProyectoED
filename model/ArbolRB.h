#ifndef ARBOLRB_H
#define ARBOLRB_H

#include <string>
#include <functional>
#include "Nodo.h"
#include "Dato.h"

enum TipoRecorrido { PRE_ORDEN, IN_ORDEN, POST_ORDEN };

class ArbolRB {
public:
    Nodo* root;

    ArbolRB();
    ArbolRB(int criterioOrdenacion);
    void insertar(Dato* k);
    Nodo* buscar(const Dato& otro);
    void rotarIzquierda(Nodo*& raiz, Nodo*& pt);
    void rotarDerecha(Nodo*& raiz, Nodo*& pt);
    void balancear(Nodo*& raiz, Nodo*& pt);
    
    void imprimir(TipoRecorrido rec);
    void recorrer(std::function<void(Nodo*)> fn, TipoRecorrido rec);

    void setCriterioOrdenacion(int criterio);
private:
    int criterioOrdenacion;
};

#endif