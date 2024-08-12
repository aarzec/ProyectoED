#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

#include <iostream>
#include <stdexcept>
#include "NodoLista.h"
#include "Dato.h"

class Lista {
    private:
        NodoLista* cabeza;

    public:
        Lista();
        void agregar(Dato* val);
        Dato* obtener(int index) const;
        int longitud() const;
        void imprimir() const;
        int busquedaFibonacci(Dato* valor, int criterio) const;
};

#endif