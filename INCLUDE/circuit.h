#pragma once

//#include "gates.h"
#include "register.h"
#include "operation.h"
#include <vector>

class QuantumCircuit
{
    private:
        qb** qubits;
        cb** clbits;
        unsigned int n_qubit, n_clbit;

        std::vector<Operation*> circuit;

        //Operations calculations
        //Pauli gates
        void run_x(unsigned short op_index);
        void run_y(unsigned short op_index);
        void run_z(unsigned short op_index);

        //Controlled Pauli gates
        void run_cx(unsigned short op_index);
        void run_cy(unsigned short op_index);
        void run_cz(unsigned short op_index);

        //Toffoli gate
        void run_ccx(unsigned short op_index);
        void run_ccy(unsigned short op_index);
        void run_ccz(unsigned short op_index);

        //Hammard gates
        void run_h (unsigned short op_index);
        void run_ch(unsigned short op_index);

        //S & T gates
        void run_s(unsigned short op_index);
        void run_t(unsigned short op_index);

        //Rotation gates
        void run_rx(unsigned short op_index);
        void run_ry(unsigned short op_index);
        void run_rz(unsigned short op_index);

        //Swap gates
        void run_swap (unsigned short op_index);
        void run_cswap(unsigned short op_index);

        //Controlled phase gate
        void run_cp(unsigned short op_index);

        //circuit operations();
        void run_barrier(unsigned short op_index);
        void run_measure(unsigned short op_index);

        //Classical gates
        void run_not (unsigned short op_index);
        void run_and (unsigned short op_index);
        void run_nand(unsigned short op_index);
        void run_or  (unsigned short op_index);
        void run_nor (unsigned short op_index);
        void run_xor (unsigned short op_index);

        void clear_bits();


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

        //Circuit operations
        void barrier(); //  100
        void measure(unsigned short  target_qubit, unsigned short    target_clbit); //  101
        void measure(QuantumRegister target_qureg, ClassicalRegister target_clreg); //  101

        //Classical gates
        void not_ (unsigned short    target_clbit);
        void not_ (ClassicalRegister target_clreg);
        void and_ (unsigned short    input_clbit1, unsigned short    input_clbit2, unsigned short    output_clbit);
        void and_ (ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg);
        void nand_(unsigned short    input_clbit1, unsigned short    input_clbit2, unsigned short    output_clbit);
        void nand_(ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg);
        void or_  (unsigned short    input_clbit1, unsigned short    input_clbit2, unsigned short    output_clbit);
        void or_  (ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg);
        void nor_ (unsigned short    input_clbit1, unsigned short    input_clbit2, unsigned short    output_clbit);
        void nor_ (ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg);
        void xor_ (unsigned short    input_clbit1, unsigned short    input_clbit2, unsigned short    output_clbit);
        void xor_ (ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg);

        //Circuit cleaning
        void purge_operations();
        void optimize();
        void print();
        void debug_operations();
        void print_circuit();      


        //Circuit emulation
        char* run();
        unsigned short get_ouptut_size() const;
};