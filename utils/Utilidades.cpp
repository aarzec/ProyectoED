#include <iostream>
#include <string>
#include <stddef.h>
#include <limits>
#include "Utilidades.h"

void Utilidades::consolePause() {
    std::wcout << L"Presione enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Utilidades::clearConsole() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

