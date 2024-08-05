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
        ColorNodo getColor();
        void setValor(Dato val);
        void setIzquierda(Nodo* nodo);
        void setDerecha(Nodo* nodo);
        void setPadre(Nodo* nodo);
        void setColor(ColorNodo col);

        Nodo* buscar(const Dato& otro, int criterio);

        // template <typename T>
        static void recorrerInOrden(Nodo* nodo, auto& fn);
        static void recorrerPreOrden(Nodo* nodo, auto& fn);
        static void recorrerPostOrden(Nodo* nodo, auto& fn);

        static Nodo* insertar(Nodo* nodo, Nodo* nodoInsertar, int criterio);
};

#endif