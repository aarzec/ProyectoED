#ifndef DATO_H
#define DATO_H

#include <iostream>

class Dato {
    public:
        virtual std::string toString();
        virtual bool compMenorQue(Dato other, int criterio);
    private:
};

#endif