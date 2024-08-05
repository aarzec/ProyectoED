#include <iostream>
#include <functional>
#include "../utils/PrettyPrinter.h"
#include "../utils/Utilidades.h"
#include "Dato.h"
#include "Nodo.h"

Nodo::Nodo() {}

Nodo::Nodo(Dato* val) {
    valor = val;
    izquierda = nullptr;
    derecha = nullptr;
}

Dato* Nodo::getValor() {
    return valor;
}

void Nodo::setValor(Dato* val) {
    valor = val;
}

Nodo* Nodo::getIzquierda() {
    return izquierda;
}

void Nodo::setIzquierda(Nodo* nodo) {
    izquierda = nodo;
}

Nodo* Nodo::getDerecha() {
    return derecha;
}

void Nodo::setDerecha(Nodo* nodo) {
    derecha = nodo;
}

Nodo* Nodo::getPadre() {
    return padre;
}

void Nodo::setPadre(Nodo* nodo) {
    padre = nodo;
}

ColorNodo Nodo::getColor() {
    return color;
}

void Nodo::setColor(ColorNodo col) {
    color = col;
}

Nodo* Nodo::buscar(const Dato& otro, int criterio) {
    if (valor->compIgualQue(otro, criterio))
        return this;
    if (valor->compMenorQue(otro, criterio) && izquierda != nullptr)
        return izquierda->buscar(otro, criterio);
    if (valor->compMayorQue(otro, criterio) && derecha != nullptr)
        return derecha->buscar(otro, criterio);
    return nullptr;
}

void Nodo::recorrerInOrden(Nodo* nodo, std::function<void(Nodo*)> fn) {
    if (nodo == nullptr) {
        return;
    }

    recorrerInOrden(nodo->getIzquierda(), fn);
    fn(nodo);
    recorrerInOrden(nodo->getDerecha(), fn);
}

void Nodo::recorrerPreOrden(Nodo* nodo, std::function<void(Nodo*)> fn) {
    if (nodo == nullptr) {
        return;
    }

    fn(nodo);
    recorrerPreOrden(nodo->getIzquierda(), fn);
    recorrerPreOrden(nodo->getDerecha(), fn);
}

void Nodo::recorrerPostOrden(Nodo* nodo, std::function<void(Nodo*)> fn) {
    if (nodo == nullptr) {
        return;
    }

    recorrerPostOrden(nodo->getIzquierda(), fn);
    recorrerPostOrden(nodo->getDerecha(), fn);
    fn(nodo);
}

Nodo* Nodo::insertar(Nodo* nodo, Nodo* nodoInsertar, int criterio) {
    PrettyPrinter::print(L"[NODO] Insertando dato: " + Utilidades::toWString(nodoInsertar->getValor()->toString()), PrettyPrinter::PPDEBUG);
    if (nodo == nullptr) {
        PrettyPrinter::print(L"[NODO] Nodo es nulo, insertando en nodo nuevo", PrettyPrinter::PPDEBUG);
        return nodoInsertar;
    }

    if ((*nodoInsertar->getValor()).compMenorQue(*nodo->getValor(), criterio)) {
        PrettyPrinter::print(L"[NODO] Insertando en izquierda", PrettyPrinter::PPDEBUG);
        nodo->setIzquierda(insertar(nodo->getIzquierda(), nodoInsertar, criterio));
        nodo->getIzquierda()->setPadre(nodo);
    } else if ((*nodoInsertar->getValor()).compMayorQue(*nodo->getValor(), criterio)) {
        PrettyPrinter::print(L"[NODO] Insertando en derecha", PrettyPrinter::PPDEBUG);
        nodo->setDerecha(insertar(nodo->getDerecha(), nodoInsertar, criterio));
        nodo->getDerecha()->setPadre(nodo);
    }

    return nodo;
}
