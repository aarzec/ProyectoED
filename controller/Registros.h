#ifndef REGISTROS_H
#define REGISTROS_H

#include "../model/Alumno.h"
#include "../model/ArbolRB.h"

ArbolRB leerArchivoAlumnos();
void guardarArchivoAlumnos(ArbolRB& arbolAlumnos);
Alumno ingresarAlumno(ArbolRB& arbolAlumnos);

#endif
