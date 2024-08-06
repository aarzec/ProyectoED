#include <iostream>
#include <functional>
#include "../utils/PrettyPrinter.h"
#include "../utils/Utilidades.h"
#include "Dato.h"
#include "Nodo.h"
#include "Alumno.h"

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

int Nodo::numeroAbuelos(Nodo *nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    int abuelos = 0;
    bool abuelosDer = false;
    bool abuelosIZq = false;
    if (
        nodo->getIzquierda() != nullptr &&
        (nodo->getIzquierda()->getIzquierda() != nullptr || nodo->getIzquierda()->getDerecha() != nullptr)
    ) {
        abuelosDer = true;
    }
    if (
        nodo->getDerecha() != nullptr &&
        (nodo->getDerecha()->getIzquierda() != nullptr || nodo->getDerecha()->getDerecha() != nullptr)
    ) {
        abuelosIZq = true;
    }

    if (abuelosDer || abuelosIZq) {
        Dato* dato = nodo->getValor();
        Alumno al = dynamic_cast<Alumno&>(*dato);
        std::wcout <<  L"- " << al.primerNombre.c_str() << L"\n";
        abuelos++;
    }

    return abuelos + numeroAbuelos(nodo->getIzquierda()) + numeroAbuelos(nodo->getDerecha());
}
