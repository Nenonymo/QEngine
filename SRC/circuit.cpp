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
    Operation tmp(0, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::x(QuantumRegister target_qureg)
{
    Operation tmp(0, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
void QuantumCircuit::y(unsigned short target_qubit)
{
    Operation tmp(10, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::y(QuantumRegister target_qureg)
{
    Operation tmp(10, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
void QuantumCircuit::z(unsigned short target_qubit)
{
    Operation tmp(20, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::z(QuantumRegister target_qureg)
{
    Operation tmp(20, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}

//Controlled Pauli gates
void QuantumCircuit::cx(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(1, 1);
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
    Operation tmp(1, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp.target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp.control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::cy(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(11, 1);
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
    Operation tmp(11, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp.target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp.control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::cz(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(21, 1);
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
    Operation tmp(21, target_qureg.get_size());
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
    Operation tmp(2, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.control_qubit[0] = this->qubits[control_qubit_1];
    tmp.control_qubit[1] = this->qubits[control_qubit_2];
    circuit.push_back(tmp);
}
void QuantumCircuit::ccx(QuantumRegister control_qureg_1, QuantumRegister control_qureg_2, QuantumRegister target_qureg)
{
    if (control_qureg_1.get_size() != control_qureg_2.get_size() or control_qureg_1.get_size() != target_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl;
        return;
    }
    Operation tmp(2, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp.target_qubit[i] = target_qureg.get_bit_address(i);
        tmp.control_qubit[i] = control_qureg_1.get_bit_address(i);
        tmp.control_qubit[i+1] = control_qureg_2.get_bit_address(i);
    }
    circuit.push_back(tmp);
}

//Hammard gates
void QuantumCircuit::h(unsigned short target_qubit)
{
    Operation tmp(30, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::h(QuantumRegister target_qureg)
{
    Operation tmp(30, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
//Controlled Hammard gates
void QuantumCircuit::ch(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(31, 1);
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
    Operation tmp(31, target_qureg.get_size());
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
    Operation tmp(40, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::s(QuantumRegister target_qureg)
{
    Operation tmp(40, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[0] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
void QuantumCircuit::t(unsigned short target_qubit)
{
    Operation tmp(41, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::t(QuantumRegister target_qureg)
{
    Operation tmp(41, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[0] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}

//Rotation gates
void QuantumCircuit::rx(double angle, unsigned short target_qubit)
{
    Operation tmp(5, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::rx(double angle, QuantumRegister target_qureg)
{
    Operation tmp(5, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::ry(double angle, unsigned short target_qubit)
{
    Operation tmp(15, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::ry(double angle, QuantumRegister target_qureg)
{
    Operation tmp(15, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::rz(double angle, unsigned short target_qubit)
{
    Operation tmp(25, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    tmp.parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::rz(double angle, QuantumRegister target_qureg)
{
    Operation tmp(25, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    tmp.parameter = angle;
    circuit.push_back(tmp);
}

//Swap gates
void QuantumCircuit::swap(unsigned short target_qubit_1, unsigned short target_qubit_2)
{
    Operation tmp(50, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit_1];
    tmp.target_qubit[1] = this->qubits[target_qubit_2];
    circuit.push_back(tmp);
}
void QuantumCircuit::swap(QuantumRegister target_qureg_1, QuantumRegister target_qureg_2)
{
    if (target_qureg_1.get_size() != target_qureg_2.get_size())
    {
        std::cerr<<"Quantum Registers must be of same dimension"<<std::endl;
        return;
    }
    Operation tmp(50, target_qureg_1.get_size()*2);
    for (unsigned short i=0; i<target_qureg_1.get_size(); i++)
    {
        tmp.target_qubit[i] = target_qureg_1.get_bit_address(i);
        tmp.target_qubit[i+1] = target_qureg_2.get_bit_address(i);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::cswap(unsigned short control_qubit, unsigned short target_qubit_1, unsigned short target_qubit_2)
{
    Operation tmp(51, 1);
    tmp.control_qubit[0] = this->qubits[control_qubit];
    tmp.target_qubit[0] = this->qubits[target_qubit_1];
    tmp.target_qubit[1] = this->qubits[target_qubit_2];
    circuit.push_back(tmp);
}
void QuantumCircuit::cswap(QuantumRegister control_qureg, QuantumRegister target_qureg_1, QuantumRegister target_qureg_2)
{
    if (control_qureg.get_size() != target_qureg_1.get_size() or control_qureg.get_size() != target_qureg_2.get_size())
    {
        std::cerr<<"Registers must be of the same size"<<std::endl;
        return;
    }
    Operation tmp(51, control_qureg.get_size());
    for (unsigned short i=0; i<control_qureg.get_size(); i++)
    {
        tmp.control_qubit[i] = control_qureg.get_bit_address(i);
        tmp.target_qubit[i] = target_qureg_1.get_bit_address(i);
        tmp.target_qubit[i+1] = target_qureg_2.get_bit_address(i);
    }
    circuit.push_back(tmp);
}

//Controlled phase gate
void QuantumCircuit::cp(double theta, unsigned short control_qubit, unsigned short target_qubit)
{
    Operation tmp(60, 1);
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
    Operation tmp(60, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp.control_qubit[i] = control_qureg.get_bit_address(i);
        tmp.target_qubit[i] = target_qureg.get_bit_address(i);
    }
    tmp.parameter = theta;
    circuit.push_back(tmp);
}

//Barrier
void QuantumCircuit::barrier()
{
    Operation tmp(100, 0);
    circuit.push_back(tmp);
}

//Measurement
void QuantumCircuit::measure(unsigned short target_qubit)
{
    Operation tmp(101, 1);
    tmp.target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::measure(QuantumRegister target_qureg)
{
    Operation tmp(101, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp.target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}



/*************
 * OPERATION *
 *************/
Operation::Operation(char gate_number, unsigned short size)
{
    this->gate_number = gate_number;
    this->size = size;
    switch(gate_number)
    {
        // x Gates
        case 0: //  x   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            break;
        case 1: //  cx  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            break;
        case 2: //  ccx 1t  2c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size*2];
            break;
        case 5: //  rx  1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            break;

        // y Gates
        case 10: // y   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            break;
        case 11: // cy  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            break;
        case 12: // ccy 1t  2c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size*2];
            break;
        case 15: // ry  1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            break;

        // z Gates
        case 20: // z   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            break;
        case 21: // cz  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            break;
        case 22: // ccz 1t  2c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size*2];
            break;
        case 25: // rz  1t  0t
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            break;

        // Hammard Gates
        case 30: // h   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            break;
        case 31: // ch  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            break;

        // S & T
        case 40: // s   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            break;
        case 41: // t   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            break;

        // Swap
        case 50: // Swap    2t  0c
            this->target_qubit = new qb*[2*size];
            this->control_qubit = nullptr;
            break;
        case 51: // cSwap   2t  1c
            this->target_qubit = new qb*[2*size];
            this->control_qubit = new qb*[size];
            break;


        case 60: // cp  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            break;

        // Circuit management
        case 100: // barrier
            this->target_qubit = nullptr;
            this->control_qubit = nullptr;
            break;
        case 101: // measuring
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;

        // Non listed gate number
        default:
            std::cerr<<"Invalid gate number, check documentation for more informations"<<std::endl;
            break;
        
        
    }
}