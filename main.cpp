#include <locale>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "./model/ListasDoble.h"
#include "./model/Alumno.h"
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
    ListaDoble<Alumno> listaAlumnos = leerArchivoAlumnos();

    std::vector<std::wstring> opcionesMenuPrincipal({
        L"Registrar estudiante",
        L"Salir"
    });

    bool continuarMenuPrincipal = true;
    MenuSelector menuPrincipal = MenuSelector(L"Menú Principal", opcionesMenuPrincipal);

    while (continuarMenuPrincipal) {
        Utilidades::clearConsole();
        unsigned long opcionMenuPrincipal = menuPrincipal.showMenu();
        switch (opcionMenuPrincipal) {
            case 0: {
                Alumno alumno = ingresarAlumno(listaAlumnos);
                listaAlumnos.Insertar(alumno);
                printer.print(L"Alumno registrado con éxito", PrettyPrinter::SUCCESS);
            } ; break;
            default: {
                continuarMenuPrincipal = false;
            }; break;
        }
    }

    guardarArchivoAlumnos(listaAlumnos);

    return 1;
}