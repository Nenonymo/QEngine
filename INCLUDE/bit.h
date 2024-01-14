#pragma once

#include <math.h>
#include <cstdio>
#include <string>
#include <iostream>
#include "complex.h"

class Bit
{
    public:
        Bit();
        virtual ~Bit();

        virtual char measure();
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
        comp amp0;
        comp amp1;

        //Internal functions
        void normalize();

        //QuBit operations
        char measure() override;
        std::string to_cstring() const override;
        void clear_bit() override;

        friend std::ostream& operator<<(std::ostream& os, const QuBit& obj);
        void print_amplitudes();

        void set_amp0(comp number);
        void set_amp1(comp number);
};

typedef QuBit qb;


class ClBit : public Bit
{
    public:
        ClBit();
        ~ClBit();

        char value;

        char measure() override;
        std::string to_cstring() const override;
        void clear_bit() override;

};

typedef ClBit cb;