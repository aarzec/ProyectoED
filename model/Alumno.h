#ifndef ALUMNO_H
#define ALUMNO_H

#include <string>
#include "Dato.h"

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
        int cedula;

        Alumno();
        Alumno(
            int cedula,
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
        bool compMenorQue(Alumno other, int criterio);
        bool compMayorQue(Alumno other, int criterio);
        bool compIgualQue(Alumno other, int criterio);
};

std::wostream& operator << (std::wostream& outs, const Alumno& al);

#endif
