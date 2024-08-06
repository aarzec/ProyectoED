#ifndef NODO_H
#define NODO_H

#include <functional>
#include "Dato.h"

enum ColorNodo { NodoRojo, NodoNegro };

class Nodo {
    private:
        
    public:
        Dato* valor;
        Nodo* izquierda = nullptr;
        Nodo* derecha = nullptr;
        Nodo* padre = nullptr;
        ColorNodo color;

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

        static void recorrerInOrden(Nodo* nodo, std::function<void(Nodo*)> fn);
        static void recorrerPreOrden(Nodo* nodo, std::function<void(Nodo*)> fn);
        static void recorrerPostOrden(Nodo* nodo, std::function<void(Nodo*)> fn);

        static int numeroAbuelos(Nodo* nodo);
};

#endif