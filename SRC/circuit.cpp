#include "circuit.h"

#include <iostream>
#include <math.h>


double PI = 3.14159265358979323846;

double sq2 = std::sqrt(2.0);

comp c0 = comp(0, 0);
comp c1 = comp(1, 0);
comp c_1 = comp(-1, 0);
comp ci = comp(0, 1);
comp c_i = comp(0, -1);

comp xGate[2][2] = {{c0, c1}, {c1, c0}};
comp yGate[2][2] = {{c0, c_i}, {ci, c0}}; // supposed to be [[0,-i],[i,0]]
comp zGate[2][2] = {{c1, c0}, {c0, c_1}};
comp cxGate[4][4] = {{c1, c0, c0, c0}, {c0, c1, c0, c0}, {c0, c0, c0, c1}, {c0, c0, c1, c0}};
comp cyGate[4][4] = {{c1, c0, c0, c0}, {c0, c1, c0, c0}, {c0, c0, c0, ci}, {c0, c0, c_i, c0}};
comp czGate[4][4] = {{c1, c0, c0, c0}, {c0, c1, c0, c0}, {c0, c0, c1, c0}, {c0, c0, c0, c_1}};

comp hGate[2][2] = {{comp(1.0/sq2,0), comp(1.0/sq2,0)}, {comp(1.0/sq2,0), comp(-1.0/sq2,0)}};
comp chGate[4][4] = {{c1,c0,c0,c0},{c0,comp(1/sq2,0),c0,comp(1/sq2,0)},{c0,comp(1/sq2,0),c0,comp(-1/sq2,0)},{c0,c0,c1,c0}};

comp sGate[2][2] = {{c1, c0}, {c0, c_1}};
comp tGate[2][2] = {{c1, c0}, {c0, comp(std::exp(PI/4),0)}};



/***************************
 * CONSTRUCTORS/DESTRUCTOR *
 ***************************/
QuantumCircuit::QuantumCircuit(unsigned int n_qubit, unsigned int n_clbit, double global_phase)
{
    this->n_qubit = n_qubit;
    this->n_clbit = n_clbit;
    this->qubits = new qb*[n_qubit];
    this->clbits = new cb*[n_clbit];
    for (unsigned int i = 0; i<n_qubit; i++)
    {qubits[i] = new qb; }
    for (unsigned int i = 0; i<n_clbit; i++)
    {clbits[i] = new cb; }
}
QuantumCircuit::QuantumCircuit(QuantumRegister qr, ClassicalRegister cr, double global_phase)
{
    this->n_qubit = qr.get_size();
    this->n_clbit = cr.get_size();
    this->qubits = new qb*[n_qubit];
    this->clbits = new cb*[n_clbit];
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
        {delete clbits[i]; }
    }
    if (clbits!=nullptr) {delete[] clbits; }
    this->purge_operations();
}



//TODO: Add support for calling gates with list of indexes
/*********
 * GATES *
 *********/
//Pauli gates
void QuantumCircuit::x(unsigned short target_qubit)
{
    Operation* tmp = new Operation(0,1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::x(QuantumRegister target_qureg)
{
    Operation* tmp = new Operation(0, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp->target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
void QuantumCircuit::y(unsigned short target_qubit)
{
    Operation* tmp = new Operation(10, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::y(QuantumRegister target_qureg)
{
    Operation* tmp = new Operation(10, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp->target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
void QuantumCircuit::z(unsigned short target_qubit)
{
    Operation* tmp = new Operation(20, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::z(QuantumRegister target_qureg)
{
    Operation* tmp = new Operation(20, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp->target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}

//Controlled Pauli gates
void QuantumCircuit::cx(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation* tmp = new Operation(1, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->control_qubit[0] = this->qubits[control_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::cx(QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (target_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl; 
        return;
    }
    Operation* tmp = new Operation(1, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp->target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp->control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::cy(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation* tmp = new Operation(11, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->control_qubit[0] = this->qubits[control_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::cy(QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (target_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl; 
        return;
    }
    Operation* tmp = new Operation(11, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp->target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp->control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::cz(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation* tmp = new Operation(21, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->control_qubit[0] = this->qubits[control_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::cz(QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (target_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl; 
        return;
    }
    Operation* tmp = new Operation(21, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp->target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp->control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}

//Toffoli gate
void QuantumCircuit::ccx(unsigned short control_qubit_1, unsigned short control_qubit_2, unsigned short target_qubit)
{
    Operation* tmp = new Operation(2, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->control_qubit[0] = this->qubits[control_qubit_1];
    tmp->control_qubit[1] = this->qubits[control_qubit_2];
    circuit.push_back(tmp);
}
void QuantumCircuit::ccx(QuantumRegister control_qureg_1, QuantumRegister control_qureg_2, QuantumRegister target_qureg)
{
    if (control_qureg_1.get_size() != control_qureg_2.get_size() or control_qureg_1.get_size() != target_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl;
        return;
    }
    Operation* tmp = new Operation(2, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp->target_qubit[i] = target_qureg.get_bit_address(i);
        tmp->control_qubit[i] = control_qureg_1.get_bit_address(i);
        tmp->control_qubit[i+1] = control_qureg_2.get_bit_address(i);
    }
    circuit.push_back(tmp);
}

//Hammard gates
void QuantumCircuit::h(unsigned short target_qubit)
{
    Operation* tmp = new Operation(30, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::h(QuantumRegister target_qureg)
{
    Operation* tmp = new Operation(30, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp->target_qubit[i] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}

//Controlled Hammard gates
void QuantumCircuit::ch(unsigned short control_qubit, unsigned short target_qubit)
{
    Operation* tmp = new Operation(31, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->control_qubit[0] = this->qubits[control_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::ch(QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (target_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Registers must be of same dimension"<<std::endl; 
        return;
    }
    Operation* tmp = new Operation(31, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp->target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp->control_qubit[i] = control_qureg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}

//S&T gates
void QuantumCircuit::s(unsigned short target_qubit)
{
    Operation* tmp = new Operation(40, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::s(QuantumRegister target_qureg)
{
    Operation* tmp = new Operation(40, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp->target_qubit[0] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}
void QuantumCircuit::t(unsigned short target_qubit)
{
    Operation* tmp = new Operation(41, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    circuit.push_back(tmp);
}
void QuantumCircuit::t(QuantumRegister target_qureg)
{
    Operation* tmp = new Operation(41, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp->target_qubit[0] = target_qureg.get_bit_address(i); }
    circuit.push_back(tmp);
}

//Rotation gates
void QuantumCircuit::rx(double angle, unsigned short target_qubit)
{
    Operation* tmp = new Operation(5, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::rx(double angle, QuantumRegister target_qureg)
{
    Operation* tmp = new Operation(5, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp->target_qubit[i] = target_qureg.get_bit_address(i); }
    tmp->parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::ry(double angle, unsigned short target_qubit)
{
    Operation* tmp = new Operation(15, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::ry(double angle, QuantumRegister target_qureg)
{
    Operation* tmp = new Operation(15, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp->target_qubit[i] = target_qureg.get_bit_address(i); }
    tmp->parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::rz(double angle, unsigned short target_qubit)
{
    Operation* tmp = new Operation(25, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->parameter = angle;
    circuit.push_back(tmp);
}
void QuantumCircuit::rz(double angle, QuantumRegister target_qureg)
{
    Operation* tmp = new Operation(25, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {tmp->target_qubit[i] = target_qureg.get_bit_address(i); }
    tmp->parameter = angle;
    circuit.push_back(tmp);
}

//Swap gates
void QuantumCircuit::swap(unsigned short target_qubit_1, unsigned short target_qubit_2)
{
    Operation* tmp = new Operation(50, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit_1];
    tmp->target_qubit[1] = this->qubits[target_qubit_2];
    circuit.push_back(tmp);
}
void QuantumCircuit::swap(QuantumRegister target_qureg_1, QuantumRegister target_qureg_2)
{
    if (target_qureg_1.get_size() != target_qureg_2.get_size())
    {
        std::cerr<<"Quantum Registers must be of same dimension"<<std::endl;
        return;
    }
    Operation* tmp = new Operation(50, target_qureg_1.get_size()*2);
    for (unsigned short i=0; i<target_qureg_1.get_size(); i++)
    {
        tmp->target_qubit[i] = target_qureg_1.get_bit_address(i);
        tmp->target_qubit[i+1] = target_qureg_2.get_bit_address(i);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::cswap(unsigned short control_qubit, unsigned short target_qubit_1, unsigned short target_qubit_2)
{
    Operation* tmp = new Operation(51, 1);
    tmp->control_qubit[0] = this->qubits[control_qubit];
    tmp->target_qubit[0] = this->qubits[target_qubit_1];
    tmp->target_qubit[1] = this->qubits[target_qubit_2];
    circuit.push_back(tmp);
}
void QuantumCircuit::cswap(QuantumRegister control_qureg, QuantumRegister target_qureg_1, QuantumRegister target_qureg_2)
{
    if (control_qureg.get_size() != target_qureg_1.get_size() or control_qureg.get_size() != target_qureg_2.get_size())
    {
        std::cerr<<"Registers must be of the same size"<<std::endl;
        return;
    }
    Operation* tmp = new Operation(51, control_qureg.get_size());
    for (unsigned short i=0; i<control_qureg.get_size(); i++)
    {
        tmp->control_qubit[i] = control_qureg.get_bit_address(i);
        tmp->target_qubit[i] = target_qureg_1.get_bit_address(i);
        tmp->target_qubit[i+1] = target_qureg_2.get_bit_address(i);
    }
    circuit.push_back(tmp);
}

//Controlled phase gate
void QuantumCircuit::cp(double theta, unsigned short control_qubit, unsigned short target_qubit)
{
    Operation* tmp = new Operation(60, 1);
    tmp->control_qubit[0] = this->qubits[control_qubit];
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->parameter = theta;
    circuit.push_back(tmp);
}
void QuantumCircuit::cp(double theta, QuantumRegister control_qureg, QuantumRegister target_qureg)
{
    if (control_qureg.get_size() != control_qureg.get_size())
    {
        std::cerr<<"Quantum registers must be of same dimensions"<<std::endl;
        return;
    }
    Operation* tmp = new Operation(60, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp->control_qubit[i] = control_qureg.get_bit_address(i);
        tmp->target_qubit[i] = target_qureg.get_bit_address(i);
    }
    tmp->parameter = theta;
    circuit.push_back(tmp);
}

//Barrier
void QuantumCircuit::barrier()
{
    Operation* tmp = new Operation(100, 0);
    circuit.push_back(tmp);
}

//Measurement
void QuantumCircuit::measure(unsigned short target_qubit, unsigned short target_clbit)
{
    Operation* tmp = new Operation(101, 1);
    tmp->target_qubit[0] = this->qubits[target_qubit];
    tmp->target_clbit[0] = this->clbits[target_clbit];
    circuit.push_back(tmp);
}
void QuantumCircuit::measure(QuantumRegister target_qureg, ClassicalRegister target_clreg)
{
    Operation* tmp = new Operation(101, target_qureg.get_size());
    for (unsigned short i=0; i<target_qureg.get_size(); i++)
    {
        tmp->target_qubit[i] = target_qureg.get_bit_address(i); 
        tmp->target_clbit[i] = target_clreg.get_bit_address(i);
    }
    circuit.push_back(tmp);
}

//Classical gates
void QuantumCircuit::not_ (unsigned short  target_clbit)
{
    Operation* tmp = new Operation(110, 1);
    tmp->target_clbit[0] = this->clbits[target_clbit];
    circuit.push_back(tmp);
}
void QuantumCircuit::not_ (ClassicalRegister target_clreg)
{
    Operation* tmp = new Operation(110, target_clreg.get_size());
    for (unsigned int op_number=0; op_number<target_clreg.get_size(); op_number++)
    {
        tmp->target_clbit[op_number] = target_clreg.get_bit_address(op_number);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::and_ (unsigned short input_clbit1, unsigned short input_clbit2, unsigned short output_clbit)
{
    Operation* tmp = new Operation(111, 1);
    tmp->target_clbit[0] = this->clbits[input_clbit1];
    tmp->target_clbit[1] = this->clbits[input_clbit2];
    tmp->target_clbit[2] = this->clbits[output_clbit];
    circuit.push_back(tmp);
}
void QuantumCircuit::and_ (ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg)
{
    if (input_clreg1.get_size() != input_clreg2.get_size() or input_clreg1.get_size() != output_clreg.get_size())
    {
        std::cerr<<"Quantum registers must be of same dimensions"<<std::endl;
        return;
    }
    
    Operation* tmp = new Operation(111, input_clreg1.get_size());
    for (unsigned int op_number=0; op_number<input_clreg1.get_size(); op_number++)
    {
        tmp->target_clbit[op_number*3] = input_clreg1.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +1] = input_clreg2.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +2] = output_clreg.get_bit_address(op_number);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::nand_(unsigned short input_clbit1, unsigned short input_clbit2, unsigned short output_clbit)
{
    Operation* tmp = new Operation(112, 1);
    tmp->target_clbit[0] = this->clbits[input_clbit1];
    tmp->target_clbit[1] = this->clbits[input_clbit2];
    tmp->target_clbit[2] = this->clbits[output_clbit];
    circuit.push_back(tmp);
}
void QuantumCircuit::nand_(ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg)
{
    if (input_clreg1.get_size() != input_clreg2.get_size() or input_clreg1.get_size() != output_clreg.get_size())
    {
        std::cerr<<"Quantum registers must be of same dimensions"<<std::endl;
        return;
    }
    
    Operation* tmp = new Operation(112, input_clreg1.get_size());
    for (unsigned int op_number=0; op_number<input_clreg1.get_size(); op_number++)
    {
        tmp->target_clbit[op_number*3] = input_clreg1.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +1] = input_clreg2.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +2] = output_clreg.get_bit_address(op_number);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::or_  (unsigned short input_clbit1, unsigned short input_clbit2, unsigned short output_clbit)
{
    Operation* tmp = new Operation(113, 1);
    tmp->target_clbit[0] = this->clbits[input_clbit1];
    tmp->target_clbit[1] = this->clbits[input_clbit2];
    tmp->target_clbit[2] = this->clbits[output_clbit];
    circuit.push_back(tmp);
}
void QuantumCircuit::or_  (ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg)
{
    if (input_clreg1.get_size() != input_clreg2.get_size() or input_clreg1.get_size() != output_clreg.get_size())
    {
        std::cerr<<"Quantum registers must be of same dimensions"<<std::endl;
        return;
    }
    
    Operation* tmp = new Operation(113, input_clreg1.get_size());
    for (unsigned int op_number=0; op_number<input_clreg1.get_size(); op_number++)
    {
        tmp->target_clbit[op_number*3] = input_clreg1.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +1] = input_clreg2.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +2] = output_clreg.get_bit_address(op_number);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::nor_ (unsigned short input_clbit1, unsigned short input_clbit2, unsigned short output_clbit)
{
    Operation* tmp = new Operation(114, 1);
    tmp->target_clbit[0] = this->clbits[input_clbit1];
    tmp->target_clbit[1] = this->clbits[input_clbit2];
    tmp->target_clbit[2] = this->clbits[output_clbit];
    circuit.push_back(tmp);
}
void QuantumCircuit::nor_ (ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg)
{
    if (input_clreg1.get_size() != input_clreg2.get_size() or input_clreg1.get_size() != output_clreg.get_size())
    {
        std::cerr<<"Quantum registers must be of same dimensions"<<std::endl;
        return;
    }
    
    Operation* tmp = new Operation(114, input_clreg1.get_size());
    for (unsigned int op_number=0; op_number<input_clreg1.get_size(); op_number++)
    {
        tmp->target_clbit[op_number*3] = input_clreg1.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +1] = input_clreg2.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +2] = output_clreg.get_bit_address(op_number);
    }
    circuit.push_back(tmp);
}
void QuantumCircuit::xor_ (unsigned short input_clbit1, unsigned short input_clbit2, unsigned short output_clbit)
{
    Operation* tmp = new Operation(115, 1);
    tmp->target_clbit[0] = this->clbits[input_clbit1];
    tmp->target_clbit[1] = this->clbits[input_clbit2];
    tmp->target_clbit[2] = this->clbits[output_clbit];
    circuit.push_back(tmp);
}
void QuantumCircuit::xor_ (ClassicalRegister input_clreg1, ClassicalRegister input_clreg2, ClassicalRegister output_clreg)
{
    if (input_clreg1.get_size() != input_clreg2.get_size() or input_clreg1.get_size() != output_clreg.get_size())
    {
        std::cerr<<"Quantum registers must be of same dimensions"<<std::endl;
        return;
    }
    
    Operation* tmp = new Operation(115, input_clreg1.get_size());
    for (unsigned int op_number=0; op_number<input_clreg1.get_size(); op_number++)
    {
        tmp->target_clbit[op_number*3] = input_clreg1.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +1] = input_clreg2.get_bit_address(op_number);
        tmp->target_clbit[op_number*3 +2] = output_clreg.get_bit_address(op_number);
    }
    circuit.push_back(tmp);
}



/**********************
 * CIRCUIT MANAGEMENT *
 **********************/
//Circuit cleaning
void QuantumCircuit::purge_operations()
{
    for (Operation* ptr : this->circuit)
    {
        delete ptr;
    }
    this->circuit.clear();
}
void QuantumCircuit::optimize()
{}
void QuantumCircuit::print()
{
    printf("Debug of QuantumCircuit.\n");
    printf("Contains: \n\t%d\tqubits\n\t%d\tclbits\n\t%lld\tgates\n", this->n_qubit, this->n_clbit, this->circuit.size());
    printf("Qubits:\n");
    for (unsigned short i=0; i<n_qubit; i++) {printf("\t%p\t%s\n", qubits[i], (*qubits[i]).to_cstring().c_str()); }
    printf("ClBits:\n");
    for (unsigned short i=0; i<n_clbit; i++) {printf("\t%p\t%s\n", clbits[i], (*clbits[i]).to_cstring().c_str()); }
}
void QuantumCircuit::debug_operations()
{
    printf("Debug of Quantum Circuit Operations:\n");
    for (unsigned short i=0; i<circuit.size(); i++)
    {
        printf("Gate n%d \t", i);
        circuit[i]->debug_operation(); }
}
void QuantumCircuit::print_circuit()
{}



/*********************
 * CIRCUIT EMULATION *
 *********************/
char* QuantumCircuit::run(char verbose)
{
    this->clear_bits();

    if (verbose) 
    {
        printf("Start of the simulation:\n");
        for (unsigned short i=0; i<this->n_qubit; i++)
        {this->qubits[i]->print_amplitudes();
        printf("   ");}
        printf("\n");
    }

    for (unsigned short op_index=0; op_index<this->circuit.size(); op_index++)
    {
        switch (this->circuit[op_index]->get_gate_number())
        {
            case 0: //x
                this->run_x(op_index);
                break;
            case 1: //cx
                this->run_cx(op_index);
                break;
            case 2: //ccx
                this->run_ccx(op_index);
                break;
            case 5: //rx
                this->run_rx(op_index);
                break;
            case 10: //y
                this->run_y(op_index);
                break;
            case 11: //cy
                this->run_cy(op_index);
                break;
            case 12: //ccy
                this->run_ccy(op_index);
                break;
            case 15: //ry
                this->run_ry(op_index);
                break;
            case 20: //z
                this->run_z(op_index);
                break;
            case 21: //cz
                this->run_cz(op_index);
                break;
            case 22: //ccz
                this->run_ccz(op_index);
                break;
            case 25: //rz
                this->run_rz(op_index);
                break;
            case 30: //h
                this->run_h(op_index);
                break;
            case 31: //ch
                this->run_ch(op_index);
                break;
            case 40: //s
                this->run_s(op_index);
                break;
            case 41: //t
                this->run_t(op_index);
                break;
            case 50: //swap
                this->run_swap(op_index);
                break;
            case 51: //cswap
                this->run_cswap(op_index);
                break;
            case 60: //cp
                this->run_cp(op_index);
                break;
            case 100: //barrier
                this->run_barrier(op_index);
                break;
            case 101: //measure
                this->run_measure(op_index);
                break;
            case 110: //not
                this->run_not(op_index);
                break;
            case 111: //and
                this->run_and(op_index);
                break;
            case 112: //nand
                this->run_nand(op_index);
                break;
            case 113: //or
                this->run_or(op_index);
                break;
            case 114: //nor
                this->run_nor(op_index);
                break;
            case 115: //xor
                this->run_xor(op_index);
                break;
        
            default:
                std::cerr<<"Gate number not recognised"<<std::endl;
                break;
        }

        if (verbose) 
        {   
            printf("Op n%d:\n", op_index);
            for (unsigned short i=0; i<this->n_qubit; i++)
            {this->qubits[i]->print_amplitudes();
            printf("   ");}
            printf("\n");
        }
    }
    char* results = new char[this->n_clbit];
    for (unsigned short i=0; i<this->n_clbit; i++)
    {results[i] = (*(this->clbits[i])).value ; }
    return results;
}

unsigned short QuantumCircuit::get_ouptut_size() const
{return this->n_clbit; }

void QuantumCircuit::clear_bits()
{
    for (unsigned short i=0; i<this->n_qubit; i++)
    {
        this->qubits[i]->clear_bit();
    }
    for (unsigned short i=0; i<this->n_clbit; i++)
    {
        this->clbits[i]->clear_bit();
    }
}



/***************************
 * OPERATIONS CALCULATIONS *
 ***************************/
//Pauli gates
void QuantumCircuit::run_x(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 0)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * xGate[0][0] + 
                          (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * xGate[0][1];
        comp newAmp1  = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * xGate[1][0] + 
                          (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * xGate[1][1];

        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp0(newAmp0);
        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp1(newAmp1);
    }
}
void QuantumCircuit::run_y(unsigned short op_index) //Multiply by xGate matrix ([[0,1],[1,0]]), aka swap alpha and beta
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 10)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * yGate[0][0]+ 
                            (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * yGate[0][1];
        comp newAmp1  = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * yGate[1][0]+ 
                            (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * yGate[1][1];

        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp0(newAmp0);
        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp1(newAmp1);
    }
}
void QuantumCircuit::run_z(unsigned short op_index) //Multiply by xGate matrix ([[0,-i],[i,0]])
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 20)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * zGate[0][0] + 
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * zGate[0][1] ;
        comp newAmp1  = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * zGate[1][0] + 
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * zGate[1][1] ;

        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp0(newAmp0);
        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp1(newAmp1);
    }
}

//Controlled Pauli gates
void QuantumCircuit::run_cx(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 1)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  cxGate[0][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  cxGate[0][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * cxGate[0][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * cxGate[0][3];
        comp newAmp1 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  cxGate[1][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  cxGate[1][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * cxGate[1][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * cxGate[1][3];
        comp newCAmp0 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  cxGate[2][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  cxGate[2][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * cxGate[2][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * cxGate[2][3];
        comp newCAmp1 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  cxGate[3][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  cxGate[3][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * cxGate[3][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * cxGate[3][3];

        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp0(newAmp0);
        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp1(newAmp1);
        (*(this->circuit[op_index]->control_qubit[op_number])).set_amp0(newCAmp0);
        (*(this->circuit[op_index]->control_qubit[op_number])).set_amp1(newCAmp1);
    }
}
void QuantumCircuit::run_cy(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 11)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  cyGate[0][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  cyGate[0][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * cyGate[0][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * cyGate[0][3];
        comp newAmp1 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  cyGate[1][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  cyGate[1][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * cyGate[1][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * cyGate[1][3];
        comp newCAmp0 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  cyGate[2][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  cyGate[2][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * cyGate[2][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * cyGate[2][3];
        comp newCAmp1 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  cyGate[3][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  cyGate[3][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * cyGate[3][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * cyGate[3][3];

        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp0(newAmp0);
        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp1(newAmp1);
        (*(this->circuit[op_index]->control_qubit[op_number])).set_amp0(newCAmp0);
        (*(this->circuit[op_index]->control_qubit[op_number])).set_amp1(newCAmp1);
    }
}
void QuantumCircuit::run_cz(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 21)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  czGate[0][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  czGate[0][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * czGate[0][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * czGate[0][3];
        comp newAmp1 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  czGate[1][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  czGate[1][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * czGate[1][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * czGate[1][3];
        comp newCAmp0 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  czGate[2][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  czGate[2][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * czGate[2][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * czGate[2][3];
        comp newCAmp1 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  czGate[3][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  czGate[3][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * czGate[3][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * czGate[3][3];

        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp0(newAmp0);
        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp1(newAmp1);
        (*(this->circuit[op_index]->control_qubit[op_number])).set_amp0(newCAmp0);
        (*(this->circuit[op_index]->control_qubit[op_number])).set_amp1(newCAmp1);
    }
}

//Toffoli gate
void QuantumCircuit::run_ccx(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 2)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned int op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        //TODO: real ccx
        
    }
}
void QuantumCircuit::run_ccy(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 12)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned int op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        //TODO: real ccy
       
    }
}
void QuantumCircuit::run_ccz(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 22)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned int op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        //TODO: real ccz
        
    }
}

//Rotation gates //TODO: Implement all rotation gates
void QuantumCircuit::run_rx(unsigned short op_index)
{}
void QuantumCircuit::run_ry(unsigned short op_index)
{}
void QuantumCircuit::run_rz(unsigned short op_index)
{}

//Hammard gate
void QuantumCircuit::run_h(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 30)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned int op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * hGate[0][0] + 
                          (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * hGate[0][1];
        comp newAmp1  = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * hGate[1][0] + 
                          (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * hGate[1][1];

        (*(this->circuit[op_index]->target_qubit[op_number])).amp0 = newAmp0;
        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 = newAmp1;
    }
}
void QuantumCircuit::run_ch(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 31)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned int op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  chGate[0][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  chGate[0][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * chGate[0][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * chGate[0][3];
        comp newAmp1 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  chGate[1][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  chGate[1][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * chGate[1][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * chGate[1][3];
        comp newCAmp0 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  chGate[2][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  chGate[2][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * chGate[2][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * chGate[2][3];
        comp newCAmp1 = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 *  chGate[3][0] +
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 *  chGate[3][1] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp0 * chGate[3][2] +
                        (*(this->circuit[op_index]->control_qubit[op_number])).amp1 * chGate[3][3];

        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp0(newAmp0);
        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp1(newAmp1);
        (*(this->circuit[op_index]->control_qubit[op_number])).set_amp0(newCAmp0);
        (*(this->circuit[op_index]->control_qubit[op_number])).set_amp1(newCAmp1);
    }
}

// S & T gates
void QuantumCircuit::run_s(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 40)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * sGate[0][0] + 
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * sGate[0][1];
        comp newAmp1  = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * sGate[1][0] + 
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * sGate[1][1];

        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp0(newAmp0);
        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp1(newAmp1);
    }
}
void QuantumCircuit::run_t(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 41)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp newAmp0 =  (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * tGate[0][0] + 
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * tGate[0][1];
        comp newAmp1  = (*(this->circuit[op_index]->target_qubit[op_number])).amp0 * tGate[1][0] + 
                        (*(this->circuit[op_index]->target_qubit[op_number])).amp1 * tGate[1][1];

        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp0(newAmp0);
        (*(this->circuit[op_index]->target_qubit[op_number])).set_amp1(newAmp1);
    }
}

//Swap gates
void QuantumCircuit::run_swap(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 50)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        comp tmp0 = (*(this->circuit[op_index]->target_qubit[op_number*2])).amp0;
        comp tmp1 = (*(this->circuit[op_index]->target_qubit[op_number*2])).amp1;
        (*(this->circuit[op_index]->target_qubit[op_number*2])).set_amp0((*(this->circuit[op_index]->target_qubit[op_number*2 +1])).amp0);
        (*(this->circuit[op_index]->target_qubit[op_number*2])).set_amp1((*(this->circuit[op_index]->target_qubit[op_number*2 +1])).amp1);
        (*(this->circuit[op_index]->target_qubit[op_number*2 + 1])).set_amp0(tmp0);
        (*(this->circuit[op_index]->target_qubit[op_number*2 + 1])).set_amp1(tmp1);
    }
}
void QuantumCircuit::run_cswap(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 51)
    {std::cerr<<"Wrong gate"<<std::endl; return; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        //Control bit n1 (control_qubit[op_number*2]), skip if not |1>
        if  ((*(this->circuit[op_index]->control_qubit[op_number])).amp0.get_norm() != 0.0 ||
            (*(this->circuit[op_index]->control_qubit[op_number])).amp0.get_norm() != 1.0)
        {return; }

        comp tmp0 = (*(this->circuit[op_index]->target_qubit[op_number*2])).amp0;
        comp tmp1 = (*(this->circuit[op_index]->target_qubit[op_number*2])).amp1;
        (*(this->circuit[op_index]->target_qubit[op_number*2])).set_amp0((*(this->circuit[op_index]->target_qubit[op_number*2 +1])).amp0);
        (*(this->circuit[op_index]->target_qubit[op_number*2])).set_amp1((*(this->circuit[op_index]->target_qubit[op_number*2 +1])).amp1);
        (*(this->circuit[op_index]->target_qubit[op_number*2 + 1])).set_amp0(tmp0);
        (*(this->circuit[op_index]->target_qubit[op_number*2 + 1])).set_amp1(tmp1);
    }
}

//Controlled phase
void QuantumCircuit::run_cp(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 60)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        if  ((*(this->circuit[op_index]->control_qubit[op_number])).amp0.get_norm() != 0.0 ||
            (*(this->circuit[op_index]->control_qubit[op_number])).amp0.get_norm() != 1.0)
        {return; }

        (*(this->circuit[op_index]->target_qubit[op_number*2 + 1])).amp1 = (*(this->circuit[op_index]->target_qubit[op_number*2 + 1])).amp1 * std::exp(this->circuit[op_index]->parameter);
    }
}

//Circuit operations
void QuantumCircuit::run_barrier(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 100)
    {std::cerr<<"Wrong gate"<<std::endl; }
}
void QuantumCircuit::run_measure(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 101)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        (*(this->circuit[op_index]->target_clbit[op_number])).value = ((*(this->circuit[op_index]->target_qubit[op_number])).measure());
    }
}

//Classical gates
void QuantumCircuit::run_not(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 110)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        (*(this->circuit[op_index]->target_clbit[op_number])).value = 1 - (*(this->circuit[op_index]->target_clbit[op_number])).value;
    }
}
void QuantumCircuit::run_and(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 111)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        (*(this->circuit[op_index]->target_clbit[op_number*3 +2])).value = ((*(this->circuit[op_index]->target_clbit[op_number*3])).value && (*(this->circuit[op_index]->target_clbit[op_number*3 +1])).value);
    }
}
void QuantumCircuit::run_nand(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 112)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        (*(this->circuit[op_index]->target_clbit[op_number*3 +2])).value = 1-((*(this->circuit[op_index]->target_clbit[op_number*3])).value && (*(this->circuit[op_index]->target_clbit[op_number*3 +1])).value);
        
    }
}
void QuantumCircuit::run_or(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 113)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        (*(this->circuit[op_index]->target_clbit[op_number*3 +2])).value = ((*(this->circuit[op_index]->target_clbit[op_number*3])).value || (*(this->circuit[op_index]->target_clbit[op_number*3 +1])).value);
    }
}
void QuantumCircuit::run_nor(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 114)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        (*(this->circuit[op_index]->target_clbit[op_number*3 +2])).value = 1-((*(this->circuit[op_index]->target_clbit[op_number*3])).value || (*(this->circuit[op_index]->target_clbit[op_number*3 +1])).value);
    }
}
void QuantumCircuit::run_xor(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index]->get_gate_number() != 115)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index]->size; op_number++)
    {
        (*(this->circuit[op_index]->target_clbit[op_number*3 +2])).value = ((*(this->circuit[op_index]->target_clbit[op_number*3])).value != (*(this->circuit[op_index]->target_clbit[op_number*3 +1])).value);
    }
}