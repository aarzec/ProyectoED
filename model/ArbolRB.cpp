#include <iostream>
#include <functional>
#include "Dato.h"
#include "Nodo.h"
#include "Alumno.h"
#include "ArbolRB.h"
#include "../utils/PrettyPrinter.h"
#include "../utils/Utilidades.h"
#include "../utils/ConsoleColor.h"

ArbolRB::ArbolRB() {
    root = nullptr;
    criterioOrdenacion = 0;
}

ArbolRB::ArbolRB(int criterio) {
    root = nullptr;
    criterioOrdenacion = criterio;
}

void ArbolRB::rotarIzquierda(Nodo* x) {
    if (x == nullptr || x->derecha == nullptr)
        return;

    Nodo* y = x->derecha;
    x->derecha = y->izquierda;
    if (y->izquierda != nullptr)
        y->izquierda->padre = x;
    y->padre = x->padre;
    if (x->padre == nullptr)
        root = y;
    else if (x == x->padre->izquierda)
        x->padre->izquierda = y;
    else
        x->padre->derecha = y;
    y->izquierda = x;
    x->padre = y;
}

void ArbolRB::rotarDerecha(Nodo* y) {
    if (y == nullptr || y->izquierda == nullptr)
        return;

    Nodo* x = y->izquierda;
    y->izquierda = x->derecha;
    if (x->derecha != nullptr)
        x->derecha->padre = y;
    x->padre = y->padre;
    if (y->padre == nullptr)
        root = x;
    else if (y == y->padre->izquierda)
        y->padre->izquierda = x;
    else
        y->padre->derecha = x;
    x->derecha = y;
    y->padre = x;
}

void ArbolRB::balancear(Nodo* z) {
    while (z != root && z->padre->color == ColorNodo::NodoRojo) {
        if (z->padre == z->padre->padre->izquierda) {
            Nodo* y = z->padre->padre->derecha;
            if (y != nullptr && y->color == ColorNodo::NodoRojo) {
                z->padre->color = ColorNodo::NodoNegro;
                y->color = ColorNodo::NodoNegro;
                z->padre->padre->color = ColorNodo::NodoRojo;
                z = z->padre->padre;
            } else {
                if (z == z->padre->derecha) {
                    z = z->padre;
                    rotarIzquierda(z);
                }
                z->padre->color = ColorNodo::NodoNegro;
                z->padre->padre->color = ColorNodo::NodoRojo;
                rotarDerecha(z->padre->padre);
            }
        } else {
            Nodo* y = z->padre->padre->izquierda;
            if (y != nullptr && y->color == ColorNodo::NodoRojo) {
                z->padre->color = ColorNodo::NodoNegro;
                y->color = ColorNodo::NodoNegro;
                z->padre->padre->color = ColorNodo::NodoRojo;
                z = z->padre->padre;
            } else {
                if (z == z->padre->izquierda) {
                    z = z->padre;
                    rotarDerecha(z);
                }
                z->padre->color = ColorNodo::NodoNegro;
                z->padre->padre->color = ColorNodo::NodoRojo;
                rotarIzquierda(z->padre->padre);
            }
        }
    }
    root->color = ColorNodo::NodoNegro;
}

void ArbolRB::trasponer(Nodo* u, Nodo* v) {
    if (u->padre == nullptr)
        root = v;
    else if (u == u->padre->izquierda)
        u->padre->izquierda = v;
    else
        u->padre->derecha = v;
    if (v != nullptr)
        v->padre = u->padre;
}

Nodo* ArbolRB::minimo(Nodo* nodo) {
    while (nodo->izquierda != nullptr)
        nodo = nodo->izquierda;
    return nodo;
}

void ArbolRB::eliminar(Nodo* z) {
    if (z == nullptr)
    return;

    Nodo* y = z;
    Nodo* x = nullptr;
    ColorNodo y_original_color = y->color;

    if (z->izquierda == nullptr) {
        x = z->derecha;
        trasponer(z, z->derecha);
    } else if (z->derecha == nullptr) {
        x = z->izquierda;
        trasponer(z, z->izquierda);
    } else {
        y = minimo(z->derecha);
        y_original_color = y->color;
        x = y->derecha;

        if (y->padre == z) {
            if (x != nullptr)
                x->padre = y; // Check if x is not nullptr before assigning parent
        } else {
            if (x != nullptr)
                x->padre = y->padre; // Check if x and y->padre are not nullptr before assigning parent
            trasponer(y, y->derecha);
            if (y->derecha != nullptr)
                y->derecha->padre = y; // Check if y->derecha is not nullptr before assigning parent
            y->derecha = z->derecha;
            if (y->derecha != nullptr)
                y->derecha->padre = y; // Check if y->derecha is not nullptr before assigning parent
        }
        trasponer(z, y);
        y->izquierda = z->izquierda;
        if (y->izquierda != nullptr)
            y->izquierda->padre = y; // Check if y->izquierda is not nullptr before assigning parent
        y->color = z->color;
    }

    if (y_original_color == ColorNodo::NodoNegro && x != nullptr) // Check if x is not nullptr
        balancearEliminar(x);

    delete z; // Free memory allocated for the deleted nodo
}

void ArbolRB::balancearEliminar(Nodo* x) {
    while (x != root && x != nullptr && x->color == ColorNodo::NodoNegro) {
        if (x == x->padre->izquierda) {
            Nodo* w = x->padre->derecha;
            if (w->color == ColorNodo::NodoRojo) {
                w->color = ColorNodo::NodoNegro;
                x->padre->color = ColorNodo::NodoRojo;
                rotarIzquierda(x->padre);
                w = x->padre->derecha;
            }
            if ((w->izquierda == nullptr || w->izquierda->color == ColorNodo::NodoNegro) &&
                (w->derecha == nullptr || w->derecha->color == ColorNodo::NodoNegro)) {
                w->color = ColorNodo::NodoRojo;
                x = x->padre;
            } else {
                if (w->derecha == nullptr || w->derecha->color == ColorNodo::NodoNegro) {
                    if (w->izquierda != nullptr)
                        w->izquierda->color = ColorNodo::NodoNegro;
                    w->color = ColorNodo::NodoRojo;
                    rotarDerecha(w);
                    w = x->padre->derecha;
                }
                w->color = x->padre->color;
                x->padre->color = ColorNodo::NodoNegro;
                if (w->derecha != nullptr)
                    w->derecha->color = ColorNodo::NodoNegro;
                rotarIzquierda(x->padre);
                x = root;
            }
        } else {
            Nodo* w = x->padre->izquierda;
            if (w->color == ColorNodo::NodoRojo) {
                w->color = ColorNodo::NodoNegro;
                x->padre->color = ColorNodo::NodoRojo;
                rotarDerecha(x->padre);
                w = x->padre->izquierda;
            }
            if ((w->derecha == nullptr || w->derecha->color == ColorNodo::NodoNegro) &&
                (w->izquierda == nullptr || w->izquierda->color == ColorNodo::NodoNegro)) {
                w->color = ColorNodo::NodoRojo;
                x = x->padre;
            } else {
                if (w->izquierda == nullptr || w->izquierda->color == ColorNodo::NodoNegro) {
                    if (w->derecha != nullptr)
                        w->derecha->color = ColorNodo::NodoNegro;
                    w->color = ColorNodo::NodoRojo;
                    rotarIzquierda(w);
                    w = x->padre->izquierda;
                }
                w->color = x->padre->color;
                x->padre->color = ColorNodo::NodoNegro;
                if (w->izquierda != nullptr)
                    w->izquierda->color = ColorNodo::NodoNegro;
                rotarDerecha(x->padre);
                x = root;
            }
        }
    }
    if (x != nullptr)
        x->color = ColorNodo::NodoNegro;
}

void ArbolRB::setCriterioOrdenacion(int criterio) {
    criterioOrdenacion = criterio;
    // Aquí deberíamos reordenar los elementos
}

void ArbolRB::insertar(Dato* k) {
    Nodo* newNode = new Nodo(k);
    Nodo* y = nullptr;
    Nodo* x = root;

    while (x != nullptr) {
        y = x;
        if ((*newNode->getValor()).compMenorQue(*x->getValor(), criterioOrdenacion))
            x = x->izquierda;
        else
            x = x->derecha;
    }

    newNode->padre = y;
    if (y == nullptr)
        root = newNode;
    else if ((*newNode->getValor()).compMenorQue(*y->getValor(), criterioOrdenacion))
        y->izquierda = newNode;
    else
        y->derecha = newNode;

    balancear(newNode);
}

void ArbolRB::eliminar(Dato* k) {
    Nodo* z = root;
    while (z != nullptr) {
        if ((*k).compMenorQue(*z->getValor(), criterioOrdenacion))
            z = z->izquierda;
        else if ((*k).compMayorQue(*z->getValor(), criterioOrdenacion))
            z = z->derecha;
        else {
            eliminar(z);
            return;
        }
    }
    std::wcout << L"Nodo con valor " << k->toString().c_str() << L" no encontrado en el árbol." << std::endl;
}

Nodo* ArbolRB::buscar(const Dato& otro) {
    PrettyPrinter::print(L"[ARBOLRB] Buscando nodo", PrettyPrinter::PPDEBUG);
    Nodo* nodo = root;
    while (nodo != nullptr) {
        if (otro.compMenorQue(*nodo->getValor(), criterioOrdenacion))
            nodo = nodo->getIzquierda();
        else if (otro.compMayorQue(*nodo->getValor(), criterioOrdenacion))
            nodo = nodo->getDerecha();
        else
            return nodo;
    }
    return nullptr;
}

void ArbolRB::imprimir(TipoRecorrido rec) {
    recorrer([](Nodo* nodo){
        Dato* dato = nodo->getValor();
        std::wcout <<
        ConsoleColor::GREEN << L" -> " <<
        (nodo->getColor() == ColorNodo::NodoRojo ? (ConsoleColor::RED + L"[R] ") : (ConsoleColor::WHITE + L"[N] ")) <<
        ConsoleColor::GRAY << dato->toString().c_str() <<
        ConsoleColor::WHITE;
    }, rec);
    std::wcout << std::endl;
}

void ArbolRB::recorrer(std::function<void(Nodo*)> fn, TipoRecorrido rec) {
    switch (rec) {
    case TipoRecorrido::PRE_ORDEN:
        Nodo::recorrerPreOrden(root, fn);
        break;
    case TipoRecorrido::IN_ORDEN:
        Nodo::recorrerInOrden(root, fn);
        break;
    case TipoRecorrido::POST_ORDEN:
        Nodo::recorrerPostOrden(root, fn);
        break;
    default:
        break;
    }
}