#ifndef REGISTROS_H
#define REGISTROS_H

#include "../model/Alumno.h"
#include "../model/ListasDoble.h"

ListaDoble<Alumno> leerArchivoAlumnos();
void guardarArchivoAlumnos(ListaDoble<Alumno>& listaAlumnos);
int obtenerIndiceMasAlto(ListaDoble<Alumno>& listaAlumnos);
Alumno ingresarAlumno(ListaDoble<Alumno>& listaAlumnos);

#endif
