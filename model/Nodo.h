#ifndef NODO_H
#define NODO_H

#include <functional>
#include "Dato.h"

enum ColorNodo { NodoRojo, NodoNegro };

class Nodo {
    private:
        Dato* valor;
        Nodo* izquierda = nullptr;
        Nodo* derecha = nullptr;
        Nodo* padre = nullptr;
        ColorNodo color;
    public:
        Nodo();
        Nodo(Dato* val);
        Dato* getValor();
        Nodo* getIzquierda();
        Nodo* getDerecha();
        Nodo* getPadre();
        ColorNodo getColor();
        void setValor(Dato* val);
        void setIzquierda(Nodo* nodo);
        void setDerecha(Nodo* nodo);
        void setPadre(Nodo* nodo);
        void setColor(ColorNodo col);

        Nodo* buscar(const Dato& otro, int criterio);

        static void recorrerInOrden(Nodo* nodo, std::function<void(Nodo*)> fn);
        static void recorrerPreOrden(Nodo* nodo, std::function<void(Nodo*)> fn);
        static void recorrerPostOrden(Nodo* nodo, std::function<void(Nodo*)> fn);

        static Nodo* insertar(Nodo* nodo, Nodo* nodoInsertar, int criterio);

        static int numeroAbuelos(Nodo* nodo);
};

#endif