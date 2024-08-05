#ifndef REGISTROS_H
#define REGISTROS_H

#include "../model/Alumno.h"
#include "../model/ArbolRB.h"
#include "../model/ListasDoble.h"

ListaDoble<Alumno> leerArchivoAlumnos();
void guardarArchivoAlumnos(ArbolRB& arbolAlumnos);
int obtenerIndiceMasAlto(ArbolRB& arbolAlumnos);
Alumno ingresarAlumno(ArbolRB& arbolAlumnos);

#endif
