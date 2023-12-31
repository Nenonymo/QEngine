#include "circuit.h"

QuantumCircuit::QuantumCircuit(unsigned int n_qubit, unsigned int n_clbit, double global_phase)
{
    this->n_qubit = n_qubit;
    this->n_clbit = n_clbit;
    qb** qubits = new qb*[n_qubit];
    cb** clbits = new cb*[n_clbit];
    for (unsigned int i = 0; i<n_qubit; i++)
    {qubits[i] = new qb(); }
    for (unsigned int i = 0; i<n_clbit; i++)
    {clbits[i] = new cb(); }
}

QuantumCircuit::QuantumCircuit(QuantumRegister qr, ClassicalRegister cr, double global_phase)
{
    this->n_qubit = qr.get_size();
    this->n_clbit = cr.get_size();
    qb** qubits = new qb*[n_qubit];
    cb** clbits = new cb*[n_clbit];
    for (unsigned short i = 0; i<n_qubit; i++)
    {qubits[i] = qr.get_bit_address(i); }
    for (unsigned short i = 0; i<n_clbit; i++)
    {clbits[i] = cr.get_bit_address(i); }
}

QuantumCircuit::~QuantumCircuit()
{
    for (unsigned int i=0; i<n_qubit; i++)
    {
        if (qubits[i]!=nullptr)
        {delete qubits[i]; }
    }
    if (qubits!=nullptr) {delete[] qubits; }
    for (unsigned int i=0; i<n_clbit; i++)
    {
        if (clbits[i]!=nullptr)
        {delete qubits[i]; }
    }
    if (clbits!=nullptr) {delete[] clbits; }
}