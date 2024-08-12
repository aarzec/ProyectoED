#ifndef REGISTROS_H
#define REGISTROS_H

#include <iostream>
#include "../model/Alumno.h"
#include "../model/ArbolRB.h"

ArbolRB leerArchivoAlumnos();
void guardarArchivoAlumnos(ArbolRB& arbolAlumnos);
Alumno ingresarAlumno(ArbolRB& arbolAlumnos);
std::string obtenerJsonAlumnos(ArbolRB& arbolAlumnos);

#endif
