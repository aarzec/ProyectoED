/*************************
 * UFA-ESPE
 * ALUMNOS:  Leonardo Obando, William Leon
 * FECHA CREACION: Miercoles, 21 de noviembre de 2022
 * FECHA MODIFICACION: Miercoles, 23 de noviembre de 2022
 * Enunciado del problema: Crear los m�todos Insertar, Buscar
 y Eliminar elementos de una lista Simple, Doble y Circular
 * Nivel: TERCERO     NRC: 7999
 *************************/
#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "Nodo.h"

using namespace std;

template<typename T>
class ListaDoble {
public:
    Nodo<T>* primero;
    Nodo<T>* ultimo;
    ListaDoble();
    void Insertar(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
};

template<typename T>
ListaDoble<T>::ListaDoble() {
    primero = NULL;
    ultimo = NULL;
}

template<typename T>
void ListaDoble<T>::Insertar(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (primero == NULL) {
        primero = nuevo;
        ultimo = nuevo;
    }
    else {
        ultimo->setSiguiente(nuevo);
        nuevo->setAnterior(ultimo);
        ultimo = nuevo;
    }
}

template<typename T>
void ListaDoble<T>::Buscar(T _dato) {
    Nodo<T>* aux = primero;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            cout << "El dato " << _dato << " se encuentra en la lista" << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template<typename T>
void ListaDoble<T>::Eliminar(T _dato) {
    Nodo<T>* aux = primero;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            if (aux == primero) {
                primero = primero->getSiguiente();
                primero->setAnterior(NULL);
            }
            else if (aux == ultimo) {
                ultimo = ultimo->getAnterior();
                ultimo->setSiguiente(NULL);
            }
            else {
                aux->getAnterior()->setSiguiente(aux->getSiguiente());
                aux->getSiguiente()->setAnterior(aux->getAnterior());
            }
            delete aux;
            cout << "El dato " << _dato << " se ha eliminado de la lista" << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template<typename T>
void ListaDoble<T>::Mostrar() {
    Nodo<T>* aux = primero;
    while (aux != NULL) {
        wcout << aux->getDato() << " -> ";
        aux = aux->getSiguiente();
    }
    wcout << endl;
}

#endif
