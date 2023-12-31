#include "register.h"


/********************
 * QUANTUM REGISTER *
 ********************/
QuantumRegister::QuantumRegister()
{
    qb** qubits = nullptr;
    this->n = 0;
}

QuantumRegister::QuantumRegister(unsigned short nb)
{
    qb** qubits = new qb*[nb];
    for (unsigned short i = 0; i < nb; i++)
    {qubits[i] = new qb; }
    this->n = nb;
}

QuantumRegister::~QuantumRegister()
{
    for (unsigned short i=0; i<this->n; i++)
    {
        if (qubits[i]!=nullptr)
        {delete qubits[i]; }
    }
    if (qubits!=nullptr)
    {delete[] qubits;}
}

unsigned short QuantumRegister::get_size() const
{return this->n; }

qb* QuantumRegister::get_bit_address(unsigned short id) const
{return qubits[id]; }



/**********************
 * CLASSICAL REGISTER *
 **********************/
ClassicalRegister::ClassicalRegister()
{
    cb** clbits = nullptr;
    this->n = 0;
}

ClassicalRegister::ClassicalRegister(unsigned short nb)
{
    cb** clbits = new cb*[nb];
    this->n = nb;
}

ClassicalRegister::~ClassicalRegister()
{
    for (unsigned short i=0; i<this->n; i++)
    {
        if (clbits[i]!=nullptr)
        {delete clbits[i]; }
    }
    if (clbits != nullptr)
    {delete[] clbits;}
}

unsigned short ClassicalRegister::get_size() const
{return this->n; }

cb* ClassicalRegister::get_bit_address(unsigned short id) const
{return clbits[id]; }