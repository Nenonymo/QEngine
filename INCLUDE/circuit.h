#pragma once

#include "register.h"
#include <vector>

class Operation
{
    private:
        char gate_number;
        

    public:
        qb** target_qubit;
        qb** control_qubit;
        double parameter;
        unsigned short size;

        Operation(char gate_number, unsigned short size);
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
        void x(unsigned short  target_qubit); //    0
        void x(QuantumRegister target_qureg); //    0
        void y(unsigned short  target_qubit); //    10
        void y(QuantumRegister target_qureg); //    10
        void z(unsigned short  target_qubit); //    20
        void z(QuantumRegister target_qureg); //    20

        //Controlled Pauli gates
        void cx(unsigned short  control_qubit, unsigned short  target_qubit); //    1
        void cx(QuantumRegister control_qureg, QuantumRegister target_qureg); //    1
        void cy(unsigned short  control_qubit, unsigned short  target_qubit); //    11
        void cy(QuantumRegister control_qureg, QuantumRegister target_qureg); //    11
        void cz(unsigned short  control_qubit, unsigned short  target_qubit); //    21
        void cz(QuantumRegister control_qureg, QuantumRegister target_qureg); //    21

        //Toffoli gate
        void ccx(unsigned short  control_qubit_1, unsigned short  control_qubit_2, unsigned short  target_qubit); //    2
        void ccx(QuantumRegister control_qureg_1, QuantumRegister control_qureg_2, QuantumRegister target_qureg); //    2
        
        //Hammard gates
        void h(unsigned short  target_qubit); //    30
        void h(QuantumRegister target_qureg); //    30
        //Controlled Hammard gates
        void ch(unsigned short  control_qubit, unsigned short  target_qubit); //    31
        void ch(QuantumRegister control_qureg, QuantumRegister target_qureg); //    31

        //S&T gates
        void s(unsigned short  target_qubit); //    40
        void s(QuantumRegister target_qureg); //    40
        void t(unsigned short  target_qubit); //    41
        void t(QuantumRegister target_qureg); //    41

        //Rotation gates
        void rx(double angle, unsigned short  target_qubit); // 5
        void rx(double angle, QuantumRegister target_qureg); // 5
        void ry(double angle, unsigned short  target_qubit); // 15
        void ry(double angle, QuantumRegister target_qureg); // 15
        void rz(double angle, unsigned short  target_qubit); // 25
        void rz(double angle, QuantumRegister target_qureg); // 25

        //Swap gates
        void swap (unsigned short  target_qubit_1, unsigned short  target_qubit_2); //  50
        void swap (QuantumRegister target_qureg_1, QuantumRegister target_qureg_2); //  50
        void cswap(unsigned short  control_qubit, unsigned short  target_qubit_1, unsigned short  target_qubit_2); //   51
        void cswap(QuantumRegister control_qureg, QuantumRegister target_qureg_1, QuantumRegister target_qureg_2); //   51

        //Controlled phase gate
        void cp(double theta, unsigned short  control_qubit, unsigned short  target_qubit); //  60
        void cp(double theta, QuantumRegister control_qureg, QuantumRegister target_qureg); //  60

        //Circuit management
        void barrier(); //  100
        void measure(unsigned short  target_qubit); //  101
        void measure(QuantumRegister target_qureg); //  101
        
};