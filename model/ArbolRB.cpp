#include <iostream>
#include <functional>
#include "Dato.h"
#include "Nodo.h"
#include "Alumno.h"
#include "ArbolRB.h"
#include "../utils/PrettyPrinter.h"
#include "../utils/Utilidades.h"

ArbolRB::ArbolRB() {
    root = nullptr;
    criterioOrdenacion = 0;
}

ArbolRB::ArbolRB(int criterio) {
    root = nullptr;
    criterioOrdenacion = criterio;
}

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

void ArbolRB::setCriterioOrdenacion(int criterio) {
    criterioOrdenacion = criterio;
    // Aquí deberíamos reordenar los elementos
}

void ArbolRB::insertar(Dato* k) {
    PrettyPrinter::print(L"[ARBOLRB] Insertando dato: " + Utilidades::toWString(k->toString()), PrettyPrinter::PPDEBUG);
    Nodo* pt = new Nodo(k);

    root = Nodo::insertar(root, pt, criterioOrdenacion);
    std::string izq = (root->getIzquierda() == nullptr ? "nullptr" : root->getIzquierda()->getValor()->toString());
    std::string der = (root->getDerecha() == nullptr ? "nullptr" : root->getDerecha()->getValor()->toString());
    PrettyPrinter::print(L"[ARBOLRB] Luego de insertar, la raíz es: " + Utilidades::toWString(root->getValor()->toString().c_str()) + L", a su izquierda: " + Utilidades::toWString(izq.c_str()) + L", a su derecha: " + Utilidades::toWString(der.c_str()), PrettyPrinter::PPDEBUG);

    if (root->getIzquierda() != nullptr) {
        std::string izq_izq = (root->getIzquierda()->getIzquierda() == nullptr ? "nullptr" : root->getIzquierda()->getIzquierda()->getValor()->toString());
        std::string izq_der = (root->getIzquierda()->getDerecha() == nullptr ? "nullptr" : root->getIzquierda()->getDerecha()->getValor()->toString());
        PrettyPrinter::print(L"[ARBOLRB] a su vez, el nodo izq de la raíz es: " + Utilidades::toWString(root->getIzquierda()->getValor()->toString().c_str()) + L", a su izquierda: " + Utilidades::toWString(izq_izq.c_str()) + L", a su derecha: " + Utilidades::toWString(izq_der.c_str()), PrettyPrinter::PPDEBUG);
    }

    if (root->getDerecha() != nullptr) {
        std::string der_izq = (root->getDerecha()->getIzquierda() == nullptr ? "nullptr" : root->getDerecha()->getIzquierda()->getValor()->toString());
        std::string der_der = (root->getDerecha()->getDerecha() == nullptr ? "nullptr" : root->getDerecha()->getDerecha()->getValor()->toString());
        PrettyPrinter::print(L"[ARBOLRB] a su vez, el nodo der de la raíz es: " + Utilidades::toWString(root->getDerecha()->getValor()->toString().c_str()) + L", a su izquierda: " + Utilidades::toWString(der_izq.c_str()) + L", a su derecha: " + Utilidades::toWString(der_der.c_str()), PrettyPrinter::PPDEBUG);
    }

    balancear(root, pt);
}

Nodo* ArbolRB::buscar(const Dato& otro) {
    Nodo* result = nullptr;
    Nodo::recorrerInOrden(root, [&result, &otro](Nodo* nodo){
        Dato* dato = nodo->getValor();
        Alumno al = dynamic_cast<Alumno&>(*dato);
        if (al.cedula == dynamic_cast<const Alumno&>(otro).cedula) {
            result = nodo;
        }
    });
    return result;
}

void ArbolRB::imprimir(TipoRecorrido rec) {
    recorrer([](Nodo* nodo){
        Dato* dato = nodo->getValor();
        std::wcout << L" -> " << dato->toString().c_str();
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