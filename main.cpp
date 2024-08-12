#include <locale>
#include <vector>
#include <string.h>
#include <dlfcn.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "./model/Alumno.h"
#include "./model/ArbolRB.h"
#include "./model/Nodo.h"
#include "./model/NodoLista.h"
#include "./model/ListaSimple.h"
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

    // Cargar librerías
    void* handleHashLib = dlopen("./lib/libsha1.so", RTLD_LAZY);
    typedef void (*sha1_hash_t)(const char *input, char *output);
    sha1_hash_t sha1_hash = (sha1_hash_t) dlsym(handleHashLib, "sha1_hash");

    PrettyPrinter printer;
    ArbolRB arbolAlumnos = leerArchivoAlumnos(); // Por simplicidad, el árbol por defecto estará ordenado por cédula

    std::vector<std::wstring> opcionesMenuPrincipal({
        L"Registrar estudiante",
        L"Buscar datos",
        L"Mostrar datos",
        L"Ver número de abuelos",
        L"Hashing de datos usando SHA-1",
        L"Salir"
    });

    bool continuarMenuPrincipal = true;
    MenuSelector menuPrincipal = MenuSelector(L"Menú Principal", opcionesMenuPrincipal);

    while (continuarMenuPrincipal) {
        Utilidades::clearConsole();
        unsigned long opcionMenuPrincipal = menuPrincipal.showMenu();
        switch (opcionMenuPrincipal) {
            case 0: {
                Utilidades::clearConsole();
                Alumno alumno = ingresarAlumno(arbolAlumnos);
                arbolAlumnos.insertar(&alumno);
                guardarArchivoAlumnos(arbolAlumnos);
                arbolAlumnos = leerArchivoAlumnos();
                printer.print(L"Alumno registrado con éxito", PrettyPrinter::SUCCESS);
            } ; break;
            case 1: {
                bool continuarMenuBusqueda = true;
                do {
                    Utilidades::clearConsole();
                    std::vector<std::wstring> opcionesBusqueda({
                        L"Búsqueda binaria",
                        L"Búsqueda de Fibonacci",
                        L"Volver"
                    });
                    MenuSelector menuBusqueda = MenuSelector(L"Buscar datos", opcionesBusqueda);
                    unsigned long opcionBusqueda = menuBusqueda.showMenu();
                    switch (opcionBusqueda) {
                        case 0: {
                            Utilidades::clearConsole();
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
                        case 1: {
                            Utilidades::clearConsole();
                            std::wcout << L"Ingrese la cédula del estudiante a buscar: ";
                            std::string cedula = ingresarNumero();
                            Alumno alumnoBusqueda = Alumno();
                            alumnoBusqueda.cedula = cedula;

                            Lista listaAlumnos = arbolAlumnos.transformarLista();
                            int alumnoIndice = listaAlumnos.busquedaFibonacci(&alumnoBusqueda, arbolAlumnos.getCriterioOrdenacion());
                            if (alumnoIndice != -1) {
                                Alumno* alumno = static_cast<Alumno*>(listaAlumnos.obtener(alumnoIndice));
                                std::string mensaje = "Estudiante encontrado: " + alumno->toString();
                                printer.print(Utilidades::toWString(mensaje), PrettyPrinter::SUCCESS);
                            } else {
                                printer.print(L"Estudiante no encontrado", PrettyPrinter::PPERROR);
                            }
                        } ; break;
                        default: {
                            Utilidades::clearConsole();
                            continuarMenuBusqueda = false;
                        } ; break;
                    }
                } while (continuarMenuBusqueda);
            } ; break;
            case 2: {
                Utilidades::clearConsole();
                bool continuarMenuMostrar = true;
                do {
                    Utilidades::clearConsole();
                    std::vector<std::wstring> opcionesMostrar({
                        L"Recorridos",
                        L"Visualización gráfica",
                        L"Volver"
                    });
                    MenuSelector menuMostrar = MenuSelector(L"Mostrar datos", opcionesMostrar);
                    Utilidades::clearConsole();
                    unsigned long opcionMostrar = menuMostrar.showMenu();
                    switch (opcionMostrar) {
                        case 0: {
                            Utilidades::clearConsole();
                            bool continuarMenuRecorridos = true;
                            do {
                                std::vector<std::wstring> opcionesRecorridos({
                                    L"Pre-orden",
                                    L"In-orden",
                                    L"Post-orden",
                                    L"Volver"
                                });
                                MenuSelector menuRecorridos = MenuSelector(L"Recorridos", opcionesRecorridos);
                                Utilidades::clearConsole();
                                unsigned long opcionRecorrido = menuRecorridos.showMenu();
                                switch (opcionRecorrido) {
                                    case 0: {
                                        Utilidades::clearConsole();
                                        arbolAlumnos.imprimir(TipoRecorrido::PRE_ORDEN);
                                        Utilidades::consolePause();
                                    } ; break;
                                    case 1: {
                                        Utilidades::clearConsole();
                                        arbolAlumnos.imprimir(TipoRecorrido::IN_ORDEN);
                                        Utilidades::consolePause();
                                    } ; break;
                                    case 2: {
                                        Utilidades::clearConsole();
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
                            Utilidades::clearConsole();
                            Alumno::visualizarArbol(arbolAlumnos);
                        } ; break;
                        default: {
                            Utilidades::clearConsole();
                            continuarMenuMostrar = false;
                        } ; break;
                    }
                } while (continuarMenuMostrar);
            } ; break;
            case 3: {
                Utilidades::clearConsole();
                std::wcout << ConsoleColor::BG_BLUE << ConsoleColor::BLACK << L"  Abuelos del árbol  \n" << ConsoleColor::RESET << ConsoleColor::YELLOW << std::endl;
                int nAbuelos = Nodo::numeroAbuelos(arbolAlumnos.root);
                std::wcout << ConsoleColor::GREEN  << L"= " << nAbuelos << L" abuelos" << ConsoleColor::RESET << L"\n\n";
                Utilidades::consolePause();
            } ; break;
            case 4: {
                Utilidades::clearConsole();
                std::wcout << ConsoleColor::BG_BLUE << ConsoleColor::BLACK << L"  Hashing usando SHA-1  \n" << ConsoleColor::RESET << ConsoleColor::YELLOW << std::endl;

                std::string input = obtenerJsonAlumnos(arbolAlumnos);
                char inputCStr[input.length() + 1];
                char outputCStr[40 + 1];

                strcpy(inputCStr, input.c_str());
                sha1_hash(inputCStr, outputCStr);
                std::string output = outputCStr;

                std::wcout << ConsoleColor::GREEN << L"= " << Utilidades::toWString(output) << ConsoleColor::RESET << L"\n\n";
                Utilidades::consolePause();
            } ; break;
            default: {
                Utilidades::clearConsole();
                continuarMenuPrincipal = false;
            }; break;
        }
    }

    guardarArchivoAlumnos(arbolAlumnos);

    return 1;
}
