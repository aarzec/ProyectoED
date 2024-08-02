#ifndef NODO_H
#define NODO_H

#include "Dato.h"

enum ColorNodo { NodoRojo, NodoNegro };

class Nodo {
    private:
        Dato valor;
        Nodo* izquierda = nullptr;
        Nodo* derecha = nullptr;
        ColorNodo color;
    public:
        Nodo();
        Nodo(Dato val);
        Dato getValor();
        Nodo* getIzquierda();
        Nodo* getDerecha();
        Nodo* getPadre();
        void setValor(Dato val);
        void setIzquierda(Nodo* nodo);
        void setDerecha(Nodo* nodo);
        void setPadre(Nodo* nodo);

        static void recorrerInOrden(Nodo* nodo);
        static void recorrerPreOrden(Nodo* nodo);
        static void recorrerPostOrden(Nodo* nodo);

        static Nodo* insertar(Nodo* nodo, Nodo* nodoInsertar, int criterio);
};

#endif