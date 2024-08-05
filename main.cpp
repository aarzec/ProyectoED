#include <locale>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "./model/Alumno.h"
#include "./model/ArbolRB.h"
#include "./model/Nodo.h"
#include "./utils/PrettyPrinter.h"
#include "./utils/ConsoleColor.h"
#include "./utils/MenuSelector.h"
#include "./utils/TermInput.h"
#include "./utils/Utilidades.h"
#include "./controller/Registros.h"

int main() {
    std::setlocale(LC_ALL, "");
    std::locale::global(std::locale(""));
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);
            }
        }
    #endif

    PrettyPrinter printer;
    ArbolRB arbolAlumnos = leerArchivoAlumnos(); // Por simplicidad, el árbol por defecto estará ordenado por cédula

    std::vector<std::wstring> opcionesMenuPrincipal({
        L"Registrar estudiante",
        L"Buscar datos",
        L"Mostrar datos",
        L"Salir"
    });

    bool continuarMenuPrincipal = true;
    MenuSelector menuPrincipal = MenuSelector(L"Menú Principal", opcionesMenuPrincipal);

    while (continuarMenuPrincipal) {
        // Utilidades::clearConsole();
        unsigned long opcionMenuPrincipal = menuPrincipal.showMenu();
        switch (opcionMenuPrincipal) {
            case 0: {
                Alumno alumno = ingresarAlumno(arbolAlumnos);
                arbolAlumnos.insertar(&alumno);
                printer.print(L"Alumno registrado con éxito", PrettyPrinter::SUCCESS);
            } ; break;
            case 1: {
                std::wcout << L"Ingrese la cédula del estudiante a buscar: ";
                std::string cedula = ingresarNumero();
                Alumno alumnoBusqueda = Alumno();
                alumnoBusqueda.cedula = cedula;
                Nodo* alumno = arbolAlumnos.buscar(alumnoBusqueda);
                if (alumno != nullptr) {
                    std::string mensaje = "Estudiante encontrado: " + alumno->getValor()->toString();
                    printer.print(Utilidades::toWString(mensaje), PrettyPrinter::SUCCESS);
                } else {
                    printer.print(L"Estudiante no encontrado", PrettyPrinter::PPERROR);
                }
            } ; break;
            case 2: {
                bool continuarMenuMostrar = true;
                do {
                    std::vector<std::wstring> opcionesMostrar({
                        L"Recorridos",
                        L"Visualización gráfica",
                        L"Volver"
                    });
                    MenuSelector menuMostrar = MenuSelector(L"Mostrar datos", opcionesMostrar);
                    unsigned long opcionMostrar = menuMostrar.showMenu();
                    switch (opcionMostrar) {
                        case 0: {
                            bool continuarMenuRecorridos = true;
                            do {
                                std::vector<std::wstring> opcionesRecorridos({
                                    L"Pre-orden",
                                    L"In-orden",
                                    L"Post-orden",
                                    L"Volver"
                                });
                                MenuSelector menuRecorridos = MenuSelector(L"Recorridos", opcionesRecorridos);
                                unsigned long opcionRecorrido = menuRecorridos.showMenu();
                                switch (opcionRecorrido) {
                                    case 0: {
                                        arbolAlumnos.imprimir(TipoRecorrido::PRE_ORDEN);
                                        Utilidades::consolePause();
                                    } ; break;
                                    case 1: {
                                        arbolAlumnos.imprimir(TipoRecorrido::IN_ORDEN);
                                        Utilidades::consolePause();
                                    } ; break;
                                    case 2: {
                                        arbolAlumnos.imprimir(TipoRecorrido::POST_ORDEN);
                                        Utilidades::consolePause();
                                    } ; break;
                                    default: {
                                        continuarMenuRecorridos = false;
                                    } ; break;
                                }
                            } while (continuarMenuRecorridos);
                        } ; break;
                        case 1: {
                            Alumno::visualizarArbol(arbolAlumnos);
                        } ; break;
                        default: {
                            continuarMenuMostrar = false;
                        } ; break;
                    }
                } while (continuarMenuMostrar);
            } ; break;
            default: {
                continuarMenuPrincipal = false;
            }; break;
        }
    }

    guardarArchivoAlumnos(arbolAlumnos);

    return 1;
}