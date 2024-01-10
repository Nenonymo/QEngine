#pragma once

#include <cmath>
#include "complex.h"


class QuBit
{
    private:

    public:
        //Constructor
        QuBit(double alpha, double beta);
        QuBit();
        ~QuBit();

        //Values
        comp value;

        //Internal functions
        void normalize();

        //QuBit operations
        char measure() const;
};

typedef QuBit qb;


class ClBit
{
    private:
        char value;

    public:
        ClBit();
        ~ClBit();

        char measure() const;

};

typedef ClBit cb;