#ifndef DATO_H
#define DATO_H

#include <iostream>

class Dato {
    public:
        virtual std::string toString() = 0;
        virtual bool compMenorQue(const Dato& other, int criterio) const = 0;
        virtual bool compMayorQue(const Dato& other, int criterio) const = 0;
        virtual bool compIgualQue(const Dato& other, int criterio) const = 0;
    private:
};

#endif