#pragma once

#include "register.h"
#include <vector>

struct operation
{
    unsigned short gate_number;
    qb** target_qubit;
    qb** target_qubit_2;
    qb** control_qubit;
    qb** control_qubit_2;
    double parameter;
};


class QuantumCircuit
{
    private:
        qb** qubits;
        cb** clbits;
        unsigned int n_qubit, n_clbit;

    public:
        //Constructors
        QuantumCircuit(unsigned int qubit, unsigned int clbit = 0, double global_phase = 0.5f);
        QuantumCircuit(QuantumRegister qr, ClassicalRegister cr = ClassicalRegister(0), double global_phase = 0.5f);

        //Destructor
        ~QuantumCircuit();

        //Gates
        //Pauli gates
        void x(unsigned short qubit);
        void x(QuantumRegister qureg);
        void y(unsigned short qubit);
        void y(QuantumRegister qureg);
        void z(unsigned short qubit);
        void z(QuantumRegister qureg);

        //Controlled Pauli gates
        void cx(unsigned short control_qubit, unsigned short target_qubit);
        void cx(QuantumRegister control_qureg, QuantumRegister target_qureg);
        void cy(unsigned short control_qubit, unsigned short target_qubit);
        void cy(QuantumRegister control_qureg, QuantumRegister target_qureg);
        void cz(unsigned short control_qubit, unsigned short target_qubit);
        void cz(QuantumRegister control_qureg, QuantumRegister target_qureg);
        
        //Hammard gates
        void h(unsigned short qubit);
        void h(QuantumRegister qureg);
        //Controlled Hammard gates
        void ch(unsigned short control_qubit, unsigned short target_qubit);
        void ch(QuantumRegister control_qureg, QuantumRegister target_qureg);

        //S&T gates
        void s(unsigned short qubit);
        void s(QuantumRegister qureg);
        void t(unsigned short qubit);
        void t(QuantumRegister qureg);

        //Rotation gates
        void rx(double angle, unsigned short qubit);
        void rx(double angle, QuantumRegister qureg);
        void ry(double angle, unsigned short qubit);
        void ry(double angle, QuantumRegister qureg);
        void rz(double angle, unsigned short qubit);
        void rz(double angle, QuantumRegister qureg);

        //Swap gates
        void swap(unsigned short target_qubit_1, unsigned short target_qubit_2);
        void cswap(unsigned short control_qubit, unsigned short target_qubit_1, unsigned short target_qubit_2);

        //Controlled phase gate
        void cp(double theta, unsigned short control_qubit, unsigned short target_qubit);
        
        //Toffoli gate
        void ccx(unsigned short control_qubit_1, unsigned short control_qubit_2, unsigned short qubit);
};