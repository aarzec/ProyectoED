#include <locale>
#include <vector>
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/filereadstream.h"
#include "../lib/rapidjson/writer.h"
#include "../lib/rapidjson/stringbuffer.h"
#include "../lib/rapidjson/filewritestream.h"
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "../model/Alumno.h"
#include "../model/ListasDoble.h"
#include "../utils/PrettyPrinter.h"
#include "../utils/MenuSelector.h"
#include "../utils/TermInput.h"
#include "Registros.h"

using namespace rapidjson;

const char* archivoAlumnos = "data/alumnos.json";

ListaDoble<Alumno> leerArchivoAlumnos() {
    FILE* fp = fopen(archivoAlumnos, "r"); 

    char readBuffer[65536]; 
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer)); 

    rapidjson::Document d; 
    d.ParseStream(is);

    fclose(fp);

    ListaDoble<Alumno> listaAlumnos = ListaDoble<Alumno>();
    Value& listaDoc = d.GetArray();
    for (unsigned int i = 0; i < listaDoc.Size(); i++) {
        Value& objAlumno = listaDoc[i];
        listaAlumnos.Insertar(
            Alumno(objAlumno["id"].GetInt(), objAlumno["nombre"].GetString(), objAlumno["segundoNombre"].GetString(), objAlumno["apellido"].GetString())
        );
    }

    return listaAlumnos;
}

void guardarArchivoAlumnos(ListaDoble<Alumno>& listaAlumnos) {
    FILE* fp = fopen(archivoAlumnos, "w"); 

    char writeBuffer[65536]; 
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

    rapidjson::Document d;
    d.SetArray();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

    Nodo<Alumno>* nodo = listaAlumnos.primero;
    while (nodo != nullptr) {
        Alumno al = nodo->getDato();
        rapidjson::Value objAlumno(rapidjson::kObjectType);
        objAlumno.AddMember("id", al.numeroUnico, allocator);
        objAlumno.AddMember("nombre", rapidjson::Value(al.nombre.c_str(), allocator), allocator);
        objAlumno.AddMember("segundoNombre", rapidjson::Value(al.segundoNombre.c_str(), allocator), allocator);
        objAlumno.AddMember("apellido", rapidjson::Value(al.apellido.c_str(), allocator), allocator);

        d.PushBack(objAlumno, allocator);
        nodo = nodo->getSiguiente();
    }

    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
    d.Accept(writer);

    fclose(fp);
}

int obtenerIndiceMasAlto(ListaDoble<Alumno>& listaAlumnos) {
    Nodo<Alumno>* nodoActual = listaAlumnos.primero;
    int maxId = -1;

    while (nodoActual != nullptr) {
        Alumno al = nodoActual->getDato();
        if (al.numeroUnico > maxId) {
            maxId = al.numeroUnico;
        }
        nodoActual = nodoActual->getSiguiente();
    }

    return maxId;
}

Alumno ingresarAlumno(ListaDoble<Alumno>& listaAlumnos) {
    std::string nombre1, nombre2, apellidoPaterno, apellidoMaterno;

    std::wcout << "Ingrese el primer nombre: ";
    nombre1 = "";
    nombre1 = ingresarCadena(true);
    std::wcout << "Ingrese el segundo nombre: ";
    nombre2 = ingresarCadena();
    std::wcout << "Ingrese el apellido: ";
    apellidoPaterno = ingresarCadena(true);
    // std::cout << "Ingrese el apellido materno: ";
    // apellidoMaterno = ingresarCadena();

    Alumno alumno = Alumno(obtenerIndiceMasAlto(listaAlumnos) + 1, nombre1, nombre2, apellidoPaterno);

    return alumno;
}
