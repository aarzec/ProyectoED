#include <locale>
#include <vector>
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/filereadstream.h"
#include "../lib/rapidjson/writer.h"
#include "../lib/rapidjson/stringbuffer.h"
#include "../lib/rapidjson/istreamwrapper.h"
#include "../lib/rapidjson/filewritestream.h"
#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "../model/Alumno.h"
#include "../model/Validaciones.h"
#include "../utils/PrettyPrinter.h"
#include "../utils/MenuSelector.h"
#include "../utils/TermInput.h"
#include "Registros.h"

using namespace rapidjson;

std::string archivoAlumnos = "data/alumnos.json";

ArbolRB leerArchivoAlumnos() {
    std::ifstream file{archivoAlumnos}; 
    if (!file.is_open()) {
        std::ofstream newFile{archivoAlumnos};
        newFile << "[]";
        newFile.close();
        file.open(archivoAlumnos);
    }
    rapidjson::IStreamWrapper isw{file};
    rapidjson::Document d {};
    d.ParseStream(isw);

    ArbolRB arbolAlumnos = ArbolRB(CriterioOrdenacionAlumno::OrdenarCedula);
    Value& listaDoc = d.GetArray();
    for (unsigned int i = 0; i < listaDoc.Size(); i++) {
        Value& objAlumno = listaDoc[i];
        arbolAlumnos.insertar(
            new Alumno(
                objAlumno["cedula"].GetString(),
                objAlumno["primerNombre"].GetString(),
                objAlumno["segundoNombre"].GetString(),
                objAlumno["apellidoPaterno"].GetString(),
                objAlumno["apellidoMaterno"].GetString()
            )
        );
    }

    return arbolAlumnos;
}

void guardarArchivoAlumnos(ArbolRB& arbolAlumnos) {
    rapidjson::Document d;
    d.SetArray();
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

    try {
    arbolAlumnos.recorrer([&allocator, &d](Nodo* nodo) {
        Dato* dato = nodo->getValor();
        Alumno al = dynamic_cast<Alumno&>(*dato);
        rapidjson::Value objAlumno(rapidjson::kObjectType);
        objAlumno.AddMember("cedula", rapidjson::Value(al.cedula.c_str(), allocator), allocator);
        objAlumno.AddMember("primerNombre", rapidjson::Value(al.primerNombre.c_str(), allocator), allocator);
        objAlumno.AddMember("segundoNombre", rapidjson::Value(al.segundoNombre.c_str(), allocator), allocator);
        objAlumno.AddMember("apellidoPaterno", rapidjson::Value(al.apellidoPaterno.c_str(), allocator), allocator);
        objAlumno.AddMember("apellidoMaterno", rapidjson::Value(al.apellidoMaterno.c_str(), allocator), allocator);

        d.PushBack(objAlumno, allocator);
    }, TipoRecorrido::IN_ORDEN);
    } catch (std::exception& e) {
        std::wcout << L"Error: " << e.what() << std::endl;
    }

    std::wcout << L"Guardando archivo de alumnos..." << std::endl;

    std::ofstream file(archivoAlumnos);
    std::string json;
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    json = buffer.GetString();
    file << json;
    file.close();
}

Alumno ingresarAlumno(ArbolRB& arbolAlumnos) {
    std::string cedula, nombre1, nombre2, apellidoPaterno, apellidoMaterno;

    bool cedulaValida = false;
    while (!cedulaValida) {
        std::wcout << L"Ingrese la cédula: ";
        cedula = ingresarNumero();

        Alumno alumnoBusqueda = Alumno();
        alumnoBusqueda.cedula = cedula;
        Nodo* alumno = arbolAlumnos.buscar(alumnoBusqueda);

        cedulaValida = true;

        if (!validarCedula(cedula)) {
            PrettyPrinter::print(L"Cédula inválida por favor intenta de nuevo", PrettyPrinter::PPERROR, true);
            cedulaValida = false;
        }
        
        if (alumno != nullptr) { 
            PrettyPrinter::print(L"Cédula ya está registrada", PrettyPrinter::PPERROR, true);
            cedulaValida = false;
        }
    }
    std::wcout << L"Ingrese el primer nombre: ";
    nombre1 = ingresarCadena(true);
    std::wcout << L"Ingrese el segundo nombre: ";
    nombre2 = ingresarCadena(true);
    std::wcout << L"Ingrese el apellido paterno: ";
    apellidoPaterno = ingresarCadena(true);
    std::wcout << L"Ingrese el apellido materno: ";
    apellidoMaterno = ingresarCadena(true);

    Alumno alumno = Alumno(cedula, nombre1, nombre2, apellidoPaterno, apellidoMaterno);

    return alumno;
}
