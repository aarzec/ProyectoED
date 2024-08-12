#ifndef ARBOLRB_H
#define ARBOLRB_H

#include <string>
#include <functional>
#include "ListaSimple.h"
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
    void rotarIzquierda(Nodo*);
    void rotarDerecha(Nodo*);
    void balancear(Nodo*);
    void balancearEliminar(Nodo*);
    void trasponer(Nodo*, Nodo*);
    void eliminar(Nodo*);
    void eliminar(Dato*);
    Nodo* minimo(Nodo*);

    void imprimir(TipoRecorrido rec);
    void recorrer(std::function<void(Nodo*)> fn, TipoRecorrido rec);
    Lista transformarLista();

    int getCriterioOrdenacion();
    void setCriterioOrdenacion(int criterio);
private:
    int criterioOrdenacion;
};

#endif