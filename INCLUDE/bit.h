#pragma once

#include <math.h>
#include <cstdio>
#include <string>
#include "complex.h"

class Bit
{
    public:
        Bit();
        virtual ~Bit();

        virtual char measure() const;
        virtual std::string to_cstring() const;
        virtual void clear_bit();
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
        std::string to_cstring() const override;
        void clear_bit() override;
};

typedef QuBit qb;


class ClBit : public Bit
{
    public:
        ClBit();
        ~ClBit();

        char value;

        char measure() const override;
        std::string to_cstring() const override;
        void clear_bit() override;

};

typedef ClBit cb;