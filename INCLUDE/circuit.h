#pragma once

#include "register.h"
#include <vector>

class Operation
{
    private:
        char gate_number;
        

    public:
        qb** target_qubit;
        qb** target_qubit_2;
        qb** control_qubit;
        qb** control_qubit_2;
        double parameter;

        Operation(char gate_number, unsigned short tq_s, unsigned short tq2_s, 
                                    unsigned short cq_s, unsigned short cq2_s);
        ~Operation();
};


class QuantumCircuit
{
    private:
        qb** qubits;
        cb** clbits;
        unsigned int n_qubit, n_clbit;

        std::vector<Operation> circuit;

    public:
        //Constructors
        QuantumCircuit(unsigned int qubit, unsigned int clbit = 0, double global_phase = 0.5f);
        QuantumCircuit(QuantumRegister qr, ClassicalRegister cr = ClassicalRegister(0), double global_phase = 0.5f);

        //Destructor
        ~QuantumCircuit();

        //Gates
        //Pauli gates
        void x(unsigned short  target_qubit);
        void x(QuantumRegister target_qureg);
        void y(unsigned short  target_qubit);
        void y(QuantumRegister target_qureg);
        void z(unsigned short  target_qubit);
        void z(QuantumRegister target_qureg);

        //Controlled Pauli gates
        void cx(unsigned short  control_qubit, unsigned short  target_qubit);
        void cx(QuantumRegister control_qureg, QuantumRegister target_qureg);
        void cy(unsigned short  control_qubit, unsigned short  target_qubit);
        void cy(QuantumRegister control_qureg, QuantumRegister target_qureg);
        void cz(unsigned short  control_qubit, unsigned short  target_qubit);
        void cz(QuantumRegister control_qureg, QuantumRegister target_qureg);
        
        //Hammard gates
        void h(unsigned short  target_qubit);
        void h(QuantumRegister target_qureg);
        //Controlled Hammard gates
        void ch(unsigned short  control_qubit, unsigned short  target_qubit);
        void ch(QuantumRegister control_qureg, QuantumRegister target_qureg);

        //S&T gates
        void s(unsigned short  qubit);
        void s(QuantumRegister qureg);
        void t(unsigned short  qubit);
        void t(QuantumRegister qureg);

        //Rotation gates
        void rx(double angle, unsigned short  qubit);
        void rx(double angle, QuantumRegister qureg);
        void ry(double angle, unsigned short  qubit);
        void ry(double angle, QuantumRegister qureg);
        void rz(double angle, unsigned short  qubit);
        void rz(double angle, QuantumRegister qureg);

        //Swap gates
        void swap (unsigned short target_qubit_1, unsigned short target_qubit_2);
        void cswap(unsigned short control_qubit, unsigned short target_qubit_1, unsigned short target_qubit_2);

        //Controlled phase gate
        void cp(double theta, unsigned short control_qubit, unsigned short target_qubit);
        
        //Toffoli gate
        void ccx(unsigned short control_qubit_1, unsigned short control_qubit_2, unsigned short qubit);
};