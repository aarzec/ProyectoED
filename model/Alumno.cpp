#include "Alumno.h"
#include "../lib/StrLib.h"
#include <fstream>
#include <iostream>

Alumno::Alumno(){}

Alumno::Alumno(int cedula, std::string primerNombre, std::string segundoNombre, std::string apellidoPaterno, std::string apellidoMaterno)
    : primerNombre(primerNombre), segundoNombre(segundoNombre), apellidoPaterno(apellidoPaterno), cedula(cedula) {}

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
    archivo << "Nombre: " << primerNombre << " " << segundoNombre << " " << apellidoPaterno << std::endl;
    archivo << "Número único: " << cedula << std::endl;
    archivo << "Notas: " << nota1 << ", " << nota2 << ", " << nota3 << std::endl;
    archivo << "Promedio: " << promedio << std::endl;
    archivo << "Aprobado: " << (aprobado ? "Sí" : "No") << std::endl << std::endl;
}

std::string Alumno::toString() {
    return "Alumno{" +
    std::to_string(cedula) + ", " +
    primerNombre + ", " +
    segundoNombre + ", " +
    apellidoPaterno +
    "}";
}

bool Alumno::compMenorQue(Alumno other, int criterio) {
    return false;
}

bool Alumno::compMayorQue(Alumno other, int criterio) {
    return false;
}

bool Alumno::compIgualQue(Alumno other, int criterio) {
    return false;
}

std::wostream& operator << ( std::wostream& outs, const Alumno& al ) {
    return outs <<
    "Alumno{" <<
    al.cedula << ", " <<
    al.primerNombre << ", " <<
    al.segundoNombre << ", " <<
    al.apellidoPaterno <<
    "}";
}