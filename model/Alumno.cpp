#include <fstream>
#include <iostream>
#include "gnuplot-iostream.h"
#include "../lib/StrLib.h"
#include "../utils/PrettyPrinter.h"
#include "Alumno.h"

Alumno::Alumno(){}

Alumno::Alumno(std::string cedula, std::string primerNombre, std::string segundoNombre, std::string apellidoPaterno, std::string apellidoMaterno)
    : primerNombre(primerNombre), segundoNombre(segundoNombre), apellidoPaterno(apellidoPaterno), apellidoMaterno(apellidoMaterno), cedula(cedula) {}
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
    cedula + ", " +
    primerNombre + ", " +
    segundoNombre + ", " +
    apellidoPaterno + ", " +
    apellidoMaterno +
    "}";
}

bool Alumno::compMenorQue(const Dato& otherDato, int criterio) {
    const Alumno& other = dynamic_cast<const Alumno&>(otherDato);
    switch (criterio) {
        case OrdenarCedula:
            PrettyPrinter::print(cedula + L" < " + other.cedula + L" -> " + (cedula < other.cedula ? "1" : "0"), PrettyPrinter::PPDEBUG);
            return cedula < other.cedula;
        case OrdenarNombre:
            return primerNombre < other.primerNombre;
        case OrdenarNombre2:
            return segundoNombre < other.segundoNombre;
        case OrdenarApellido:
            return apellidoPaterno < other.apellidoPaterno;
        case OrdenarApellido2:
            return apellidoMaterno < other.apellidoMaterno;
        default:
            return false;
    }
}

bool Alumno::compMayorQue(const Dato& otherDato, int criterio) {
    const Alumno& other = dynamic_cast<const Alumno&>(otherDato);
    switch (criterio) {
        case OrdenarCedula:
            PrettyPrinter::print(cedula + L" > " + other.cedula + L" -> " + (cedula > other.cedula ? "1" : "0"), PrettyPrinter::PPDEBUG);
            return cedula > other.cedula;
        case OrdenarNombre:
            return primerNombre > other.primerNombre;
        case OrdenarNombre2:
            return segundoNombre > other.segundoNombre;
        case OrdenarApellido:
            return apellidoPaterno > other.apellidoPaterno;
        case OrdenarApellido2:
            return apellidoMaterno > other.apellidoMaterno;
        default:
            return false;
    }
}

bool Alumno::compIgualQue(const Dato& otherDato, int criterio) {
    const Alumno& other = dynamic_cast<const Alumno&>(otherDato);
    switch (criterio) {
        case OrdenarCedula:
            PrettyPrinter::print(cedula + L" == " + other.cedula + L" -> " + (cedula == other.cedula ? "1" : "0"), PrettyPrinter::PPDEBUG);
            return cedula == other.cedula;
        case OrdenarNombre:
            return primerNombre == other.primerNombre;
        case OrdenarNombre2:
            return segundoNombre == other.segundoNombre;
        case OrdenarApellido:
            return apellidoPaterno == other.apellidoPaterno;
        case OrdenarApellido2:
            return apellidoMaterno == other.apellidoMaterno;
        default:
            return false;
    }
}

void Alumno::visualizarArbol(ArbolRB &arbol) {
    Gnuplot gp;
	std::string script = R"(
### tree diagram with gnuplot
reset session

#ID  Parent   Name   Color
$Data <<EOD
)";
    arbol.recorrer([&script](Nodo* nodo) {
        Dato* dato = nodo->getValor();
        Alumno al = dynamic_cast<Alumno&>(*dato);
        script += al.cedula + " " + (nodo->getPadre() == nullptr ? "NaN" : dynamic_cast<Alumno&>(*nodo->getPadre()->getValor()).cedula) + " " + al.primerNombre + " " + (nodo->getColor() == ColorNodo::NodoRojo ? "red" : "black") + "\n";
    }, TipoRecorrido::IN_ORDEN);
    script += R"(EOD

# put datablock into strings
IDs = Parents = Names = Colors = ''
set table $Dummy
    plot $Data u (IDs = IDs.strcol(1).' '): \
                (Parents = Parents.strcol(2).' '): \
                (Names = Names.strcol(3).' '): \
                (Colors = Colors.strcol(4).' ') w table
unset table

# Top node has no parent ID 'NaN'
Start(n) = int(sum [i=1:words(Parents)] (word(Parents,i) eq 'NaN' ? int(word(IDs,i)) : 0))

# get list index by ID
ItemIdx(s,n) = n == n ? (tmp=NaN, sum [i=1:words(s)] ((word(s,i)) == n ? (tmp=i,0) : 0), tmp) : NaN

# get parent of ID n
Parent(n) = word(Parents,ItemIdx(IDs,n))

# get level of ID n, recursive function
Level(n) = n == n ? Parent(n)>0 ? Level(Parent(n))-1 : 0 : NaN

# get number of children of ID n
ChildCount(n) = int(sum [i=1:words(Parents)] (word(Parents,i)==n))

# Create child list of ID n
ChildList(n) = (Ch = ' ', sum [i=1:words(IDs)] (word(Parents,i)==n ? (Ch = Ch.word(IDs,i).' ',1) : (Ch,0) ), Ch )

# m-th child of ID n
Child(n,m) = word(ChildList(n),m)

# List of leaves, recursive function
LeafList(n) = (LL='', ChildCount(n)==0 ? LL=LL.n.' ' : sum [i=1:ChildCount(n)] (LL=LL.LeafList(Child(n,i)), 0),LL)

# create list of all leaves
LeafAll = LeafList(Start(0))

# get x-position of ID n, recursive function
XPos(n) = ChildCount(n) == 0 ? ItemIdx(LeafAll,n) : (sum [i=1:ChildCount(n)] (XPos(Child(n,i))))/(ChildCount(n))

# create the tree datablock for plotting
set print $Tree
    do for [j=1:words(IDs)] {
        n = int(word(IDs,j))
        print sprintf("% 3d % 7.2f % 4d % 5s %s", n, XPos(n), Level(n), word(Names,j), word(Colors,j))
    }
set print
print $Tree

# get x and y distance from ID n to its parent
dx(n) = XPos(Parent(int(n))) - XPos(int(n))
dy(n) = Level(Parent(int(n))) - Level(int(n))

unset border
unset tics
set offsets 0.25, 0.25, 0.25, 0.25

plot $Tree u 2:3:(dx($1)):(dy($1)):(strcol(5)) w vec nohead ls -1 not,\
        '' u 2:3:(strcol(4)) w p pt 7 ps 6 lc rgb var not, \
        '' u 2:3 w p pt 6 ps 6 lw 1.5 lc rgb "white" not, \
        '' u 2:3:4 w labels tc rgb "black" offset 0.05,0.05 center notitle, \
        '' u 2:3:4 w labels tc rgb "white" offset 0,0.1 center notitle, \
        '' u 2:3:5 w labels tc rgb "black" offset 0.05,2.55 center notitle, \
        '' u 2:3:5 w labels tc rgb "white" offset 0,2.5 center notitle
### end of code)";
    gp << script;
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