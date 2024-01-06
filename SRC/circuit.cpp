#include "circuit.h"

#include <iostream>
/****************************
 * QUANTUM CIRCUIT    CLASS *
 ****************************/

//Constructors and destructor
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



//Gates

//Pauli gates
void QuantumCircuit::x(unsigned short target_qubit)
{
    Operation tmp(0, 1, 0, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::x(QuantumRegister target_qureg)
{
    Operation tmp(0, target_qureg.get_size(), 0, 0, 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
void QuantumCircuit::y(unsigned short target_qubit)
{
    Operation tmp(10, 1, 0, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::y(QuantumRegister target_qureg)
{
    Operation tmp(10, target_qureg.get_size(), 0, 0, 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
void QuantumCircuit::z(unsigned short target_qubit)
{
    Operation tmp(20, 1, 0, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::z(QuantumRegister target_qureg)
{
    Operation tmp(20, target_qureg.get_size(), 0, 0, 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}

//Controlled Pauli gates
void QuantumCircuit::cx(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(1, 1, 0, 1, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.control_qubit[0] = this->qubits[control_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::cx(QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (target_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl; 
        return;
    }
    Operation tmp(1, target_qureg.get_size(), 0, control_qureg.get_size(), 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp.target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp.control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::cy(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(11, 1, 0, 1, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.control_qubit[0] = this->qubits[control_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::cy(QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (target_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl; 
        return;
    }
    Operation tmp(11, target_qureg.get_size(), 0, control_qureg.get_size(), 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp.target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp.control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::cz(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(21, 1, 0, 1, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.control_qubit[0] = this->qubits[control_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::cz(QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (target_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl; 
        return;
    }
    Operation tmp(21, target_qureg.get_size(), 0, control_qureg.get_size(), 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp.target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp.control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}

//Toffoli gate
void QuantumCircuit::ccx(unsigned short control_qubit_1, unsigned short control_qubit_2, unsigned short target_qubit)
{
    Operation tmp(2, 1, 0, 1, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.control_qubit[0] = this->qubits[control_qubit_1];
    tmp.control_qubit_2[0] = this->qubits[control_qubit_2];
    circuit.push_back(tmp);
}

//Hammard gates
void QuantumCircuit::h(unsigned short target_qubit)
{
    Operation tmp(30, 1, 0, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::h(QuantumRegister target_qureg)
{
    Operation tmp(30, target_qureg.get_size(), 0, 0, 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
//Controlled Hammard gates
void QuantumCircuit::ch(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(31, 1, 0, 1, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.control_qubit[0] = this->qubits[control_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::ch(QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (target_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl; 
        return;
    }
    Operation tmp(31, target_qureg.get_size(), 0, control_qureg.get_size(), 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp.target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp.control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}

//S&T gates
void QuantumCircuit::s(unsigned short target_qubit)
{
    Operation tmp(40, 1, 0, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::s(QuantumRegister target_qureg)
{
    Operation tmp(40, target_qureg.get_size(), 0, 0, 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[0] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
void QuantumCircuit::t(unsigned short target_qubit)
{
    Operation tmp(41, 1, 0, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::t(QuantumRegister target_qureg)
{
    Operation tmp(41, target_qureg.get_size(), 0, 0, 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[0] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}

//Rotation gates
void QuantumCircuit::rx(double angle, unsigned short target_qubit)
{
    Operation tmp(5, 1, 0, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::rx(double angle, QuantumRegister target_qureg)
{
    Operation tmp(5, target_qureg.get_size(), 0, 0, 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::ry(double angle, unsigned short target_qubit)
{
    Operation tmp(15, 1, 0, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::ry(double angle, QuantumRegister target_qureg)
{
    Operation tmp(15, target_qureg.get_size(), 0, 0, 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::rz(double angle, unsigned short target_qubit)
{
    Operation tmp(25, 1, 0, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::rz(double angle, QuantumRegister target_qureg)
{
    Operation tmp(25, target_qureg.get_size(), 0, 0, 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    tmp.parameter = angle;
    circuit.push_back(tmp);
}

//Swap gates
void QuantumCircuit::swap(unsigned short target_qubit_1, unsigned short target_qubit_2)
{
    Operation tmp(50, 1, 1, 0, 0);
    tmp.target_qubit[0] = this->qubits[target_qubit_1];
    tmp.target_qubit_2[0] = this->qubits[target_qubit_2];
    circuit.push_back(tmp);
}
void QuantumCircuit::swap(QuantumRegister target_qureg_1, QuantumRegister target_qureg_2)
{
    if (target_qureg_1.get_size() != target_qureg_2.get_size())
    {
        std::cerr<<"Quantum Registers must be of same dimension"<<std::endl;
        return;
    }
    Operation tmp(50, target_qureg_1.get_size(), target_qureg_2.get_size(), 0, 0);
    for (unsigned short i=0; i<target_qureg_1.get_size(); i++)
    {
        tmp.target_qubit[i] = target_qureg_1.get_bit_address(i);
        tmp.target_qubit_2[i] = target_qureg_2.get_bit_address(i);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::cswap(unsigned short control_qubit, unsigned short target_qubit_1, unsigned short target_qubit_2)
{
    Operation tmp(51, 1, 1, 1, 0);
    tmp.control_qubit[0] = this->qubits[control_qubit];
    tmp.target_qubit[0] = this->qubits[target_qubit_1];
    tmp.target_qubit_2[0] = this->qubits[target_qubit_2];
    circuit.push_back(tmp);
}
void QuantumCircuit::cswap(QuantumRegister control_qureg, QuantumRegister target_qureg_1, QuantumRegister target_qureg_2)
{
    if (control_qureg.get_size() != target_qureg_1.get_size() or control_qureg.get_size() != target_qureg_2.get_size())
    {

    }
}

//Controlled phase gate
void QuantumCircuit::cp(double theta, unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(60, 1, 0, 1, 0);
    tmp.control_qubit[0] = this->qubits[control_qubit];
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.parameter = theta;
    circuit.push_back(tmp);
}
void QuantumCircuit::cp(double theta, QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (control_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Quantum registers must be of same dimensions"<<std::endl;
        return;
    }
    Operation tmp(60, target_qureg.get_size(), 0, control_qureg.get_size(), 0);
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp.control_qubit[i] = control_qureg.get_bit_address(i);
        tmp.target_qubit[i] = target_qureg.get_bit_address(i);
    }
    tmp.parameter = theta;
    circuit.push_back(tmp);
}



/*************
 * OPERATION *
 *************/
Operation::Operation(char gate_number, unsigned short tq_s, unsigned short tq2_s, unsigned short cq_s, unsigned short cq2_s)
{
    this->gate_number = gate_number;
    this->target_qubit = new qb*[tq_s];
    this->target_qubit_2 = new qb*[tq2_s];
    this->control_qubit = new qb*[cq_s];
    this->control_qubit_2 = new qb*[cq2_s];
}