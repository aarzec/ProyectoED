#include "Alumno.h"
#include "../lib/StrLib.h"
#include <fstream>
#include <iostream>

Alumno::Alumno(){}

Alumno::Alumno(int numeroUnico, std::string nombre, std::string segundoNombre, std::string apellido)
    : nombre(nombre), segundoNombre(segundoNombre), apellido(apellido), numeroUnico(numeroUnico) {}

void Alumno::ingresarNotas(float nota1, float nota2, float nota3) {
    this->nota1 = nota1;
    this->nota2 = nota2;
    this->nota3 = nota3;
}

void Alumno::calcularPromedio() {
    promedio = (nota1 + nota2 + nota3) / 3.0;
}

void Alumno::verificarAprobacion() {
    aprobado = promedio >= 14.0;
}

void Alumno::guardarDatosEnArchivo(std::ofstream& archivo) {
    archivo << "Nombre: " << nombre << " " << segundoNombre << " " << apellido << std::endl;
    archivo << "Número único: " << numeroUnico << std::endl;
    archivo << "Notas: " << nota1 << ", " << nota2 << ", " << nota3 << std::endl;
    archivo << "Promedio: " << promedio << std::endl;
    archivo << "Aprobado: " << (aprobado ? "Sí" : "No") << std::endl << std::endl;
}

std::string Alumno::toString() {
    return "Alumno{" +
    std::to_string(numeroUnico) + ", " +
    nombre + ", " +
    segundoNombre + ", " +
    apellido +
    "}";
}

bool Alumno::compMenorQue(Alumno other, int criterio) {
    return false;
}

std::wostream& operator << ( std::wostream& outs, const Alumno& al ) {
    return outs <<
    "Alumno{" <<
    al.numeroUnico << ", " <<
    al.nombre << ", " <<
    al.segundoNombre << ", " <<
    al.apellido <<
    "}";
}