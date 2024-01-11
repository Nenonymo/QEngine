#pragma once

#include <math.h>
#include <cstdio>
#include "complex.h"

class Bit
{
    public:
        Bit();
        virtual ~Bit();

        virtual char measure() const;
        virtual char* to_cstring() const;
};


class QuBit: public Bit
{
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
        char measure() const override;
        char* to_cstring() const override;
};

typedef QuBit qb;


class ClBit : public Bit
{
    public:
        ClBit();
        ~ClBit();

        char value;

        char measure() const override;
        char* to_cstring() const override;

};

typedef ClBit cb;