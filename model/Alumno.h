#ifndef ALUMNO_H
#define ALUMNO_H

#include <string>
#include "Dato.h"
#include "ArbolRB.h"

enum CriterioOrdenacionAlumno { OrdenarCedula, OrdenarNombre, OrdenarNombre2, OrdenarApellido, OrdenarApellido2 };

class Alumno: public Dato {
    private:
        float nota1;
        float nota2;
        float nota3;
        float promedio;
        bool aprobado;

    public:
        std::string primerNombre;
        std::string segundoNombre;
        std::string apellidoPaterno;
        std::string apellidoMaterno;
        std::string cedula;

        Alumno();
        Alumno(
            std::string cedula,
            std::string primerNombre,
            std::string segundoNombre,
            std::string apellidoPaterno,
            std::string apellidoMaterno
        );
        void ingresarNotas(float nota1, float nota2, float nota3);
        void calcularPromedio();
        void verificarAprobacion();
        void guardarDatosEnArchivo(std::ofstream& archivo);

        std::string toString();
        bool compMenorQue(const Dato& other, int criterio) const;
        bool compMayorQue(const Dato& other, int criterio) const;
        bool compIgualQue(const Dato& other, int criterio) const;

        static void visualizarArbol(ArbolRB& arbol);
};

std::wostream& operator << (std::wostream& outs, const Alumno& al);

#endif
