#include <iostream>
#include "Dato.h"
#include "Nodo.h"
#include "ArbolRB.h"

void ArbolRB::rotarIzquierda(Nodo*& raiz, Nodo*& pt) {
    Nodo* pt_right = pt->getDerecha();
    pt->setDerecha(pt_right->getIzquierda());

    if (pt->getDerecha() != nullptr)
        pt->getDerecha()->setPadre(pt);

    pt_right->setPadre(pt->getPadre());

    if (pt->getPadre() == nullptr)
        raiz = pt_right;
    else if (pt == pt->getPadre()->getIzquierda())
        pt->getPadre()->setIzquierda(pt_right);
    else
        pt->getPadre()->setDerecha(pt_right);

    pt_right->setIzquierda(pt);
    pt->setPadre(pt_right);
}

void ArbolRB::rotarDerecha(Nodo*& raiz, Nodo*& pt) {
    Nodo* pt_left = pt->getIzquierda();
    pt->setIzquierda(pt_left->getDerecha());

    if (pt->getIzquierda() != nullptr)
        pt->getIzquierda()->setPadre(pt);

    pt_left->setPadre(pt->getPadre());

    if (pt->getPadre() == nullptr)
        raiz = pt_left;
    else if (pt == pt->getPadre()->getIzquierda())
        pt->getPadre()->setIzquierda(pt_left);
    else
        pt->getPadre()->setDerecha(pt_left);

    pt_left->setDerecha(pt);
    pt->setPadre(pt_left);
}

void ArbolRB::balancear(Nodo*& raiz, Nodo*& pt) {
    Nodo* padre_pt = nullptr;
    Nodo* abuelo_pt = nullptr;

    while ((pt != raiz) && (pt->getColor() != ColorNodo::NodoNegro) &&
        (pt->getPadre()->getColor() == ColorNodo::NodoRojo)) {
        
        padre_pt = pt->getPadre();
        abuelo_pt = pt->getPadre()->getPadre();

        if (padre_pt == abuelo_pt->getIzquierda()) {

            Nodo* tio_pt = abuelo_pt->getDerecha();

            if (tio_pt != nullptr && tio_pt->getColor() == ColorNodo::NodoRojo) {
                abuelo_pt->setColor(ColorNodo::NodoRojo);
                padre_pt->setColor(ColorNodo::NodoNegro);
                tio_pt->setColor(ColorNodo::NodoNegro);
                pt = abuelo_pt;
            } else {
                if (pt == padre_pt->getDerecha()) {
                    rotarIzquierda(raiz, padre_pt);
                    pt = padre_pt;
                    padre_pt = pt->getPadre();
                }

                rotarDerecha(raiz, abuelo_pt);
                ColorNodo aux = padre_pt->getColor();
                padre_pt->setColor(abuelo_pt->getColor());
                abuelo_pt->setColor(aux);
                pt = padre_pt;
            }
        } else {
            Nodo* tio_pt = abuelo_pt->getIzquierda();

            if (tio_pt != nullptr && tio_pt->getColor() == ColorNodo::NodoRojo) {
                abuelo_pt->setColor(ColorNodo::NodoRojo);
                padre_pt->setColor(ColorNodo::NodoNegro);
                tio_pt->setColor(ColorNodo::NodoNegro);
                pt = abuelo_pt;
            } else {
                if (pt == padre_pt->getIzquierda()) {
                    rotarDerecha(raiz, padre_pt);
                    pt = padre_pt;
                    padre_pt = pt->getPadre();
                }

                rotarIzquierda(raiz, abuelo_pt);
                ColorNodo aux = padre_pt->getColor();
                padre_pt->setColor(abuelo_pt->getColor());
                abuelo_pt->setColor(aux);
                pt = padre_pt;
            }
        }
    }

    raiz->setColor(ColorNodo::NodoNegro);
}

void ArbolRB::insertar(Dato k, int criterio) {
    Nodo* pt = new Nodo(k);

    root = Nodo::insertar(root, pt, criterio);

    balancear(root, pt);
}

Nodo* ArbolRB::buscar(const Dato& otro, int criterio) {
    return root == nullptr ? nullptr : root->buscar(otro, criterio);
}
