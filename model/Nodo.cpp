#include <iostream>
#include "Dato.h"
#include "Nodo.h"

Nodo::Nodo() {}

Nodo::Nodo(Dato val) {
    valor = val;
}

Dato Nodo::getValor() {
    return valor;
}

void Nodo::setValor(Dato val) {
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
    return derecha;
}

void Nodo::setPadre(Nodo* nodo) {
    derecha = nodo;
}

ColorNodo Nodo::getColor() {
    return color;
}

void Nodo::setColor(ColorNodo col) {
    color = col;
}

Nodo* Nodo::buscar(const Dato& otro, int criterio) {
    if (valor.compIgualQue(otro, criterio))
        return this;
    if (valor.compMenorQue(otro, criterio) && izquierda != nullptr)
        return izquierda->buscar(otro, criterio);
    if (valor.compMayorQue(otro, criterio) && derecha != nullptr)
        return derecha->buscar(otro, criterio);
    return nullptr;
}

void Nodo::recorrerInOrden(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    recorrerInOrden(nodo->getIzquierda());
    std::cout << nodo->getValor().toString() << " ";
    recorrerInOrden(nodo->getDerecha());
}

void Nodo::recorrerPreOrden(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    std::cout << nodo->getValor().toString() << " ";
    recorrerPreOrden(nodo->getIzquierda());
    recorrerPreOrden(nodo->getDerecha());
}

void Nodo::recorrerPostOrden(Nodo* nodo) {
    if (nodo == nullptr) {
        return;
    }

    recorrerPostOrden(nodo->getIzquierda());
    recorrerPostOrden(nodo->getDerecha());
    std::cout << nodo->getValor().toString() << " ";
}

Nodo* Nodo::insertar(Nodo* nodo, Nodo* nodoInsertar, int criterio) {
    Nodo* nodoInsertar;
    if (nodo == nullptr)
        return nodoInsertar;

    if (nodoInsertar->getValor().compMenorQue(nodo->getValor(), criterio)) {
        nodo->setIzquierda(Nodo::insertar(nodo->getIzquierda(), nodoInsertar, criterio));
        nodo->getIzquierda()->setPadre(nodo);
    } else {
        nodo->setDerecha(Nodo::insertar(nodo->getDerecha(), nodoInsertar, criterio));
        nodo->getDerecha()->setPadre(nodo);
    }
    return nodo;
}
