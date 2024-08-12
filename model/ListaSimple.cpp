#include <iostream>
#include <stdexcept>
#include "ListaSimple.h"
#include "NodoLista.h"
#include "Dato.h"


Lista::Lista() : cabeza(nullptr) {}

void Lista::agregar(Dato* val) {
    NodoLista* nuevoNodo = new NodoLista(val);
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        NodoLista* temp = cabeza;
        while (temp->siguiente) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

Dato* Lista::obtener(int index) const {
    NodoLista* temp = cabeza;
    int count = 0;
    while (temp) {
        if (count == index) {
            return temp->valor;
        }
        temp = temp->siguiente;
        count++;
    }
    throw std::out_of_range("Índice fuera de rango");
}

int Lista::longitud() const {
    int count = 0;
    NodoLista* temp = cabeza;
    while (temp) {
        count++;
        temp = temp->siguiente;
    }
    return count;
}

void Lista::imprimir() const {
    NodoLista* temp = cabeza;
    while (temp) {
        std::cout << temp->valor << " ";
        temp = temp->siguiente;
    }
    std::cout << std::endl;
}

int Lista::busquedaFibonacci(Dato* valor, int criterio) const {
    int n = longitud();
    int fib2 = 0;
    int fib1 = 1;
    int fibM = fib2 + fib1;

    while (fibM < n) {
        fib2 = fib1;
        fib1 = fibM;
        fibM = fib2 + fib1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = std::min(offset + fib2, n - 1);

        if (obtener(i)->compMenorQue(*valor, criterio)) {
            fibM = fib1;
            fib1 = fib2;
            fib2 = fibM - fib1;
            offset = i;
        } else if (obtener(i)->compMayorQue(*valor, criterio)) {
            fibM = fib2;
            fib1 = fib1 - fib2;
            fib2 = fibM - fib1;
        } else {
            return i;
        }
    }

    if (fib1 && obtener(offset + 1) == valor) {
        return offset + 1;
    }

    return -1;
}