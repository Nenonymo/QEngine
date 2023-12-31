#pragma once

#include "bit.h"

class QuantumRegister
{
    private:
        qb** qubits;
        unsigned short n;

    public:
        QuantumRegister();
        QuantumRegister(unsigned short nb);

        ~QuantumRegister();

        unsigned short get_size() const;
        qb* get_bit_address(unsigned short id) const;
};


class ClassicalRegister
{
    private:
        cb** clbits;
        unsigned short n;

    public:
        ClassicalRegister();
        ClassicalRegister(unsigned short nb);

        ~ClassicalRegister();

        unsigned short get_size() const;
        cb* get_bit_address(unsigned short id) const;
};