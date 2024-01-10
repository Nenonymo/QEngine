#include "circuit.h"

#include <iostream>



/***************************
 * CONSTRUCTORS/DESTRUCTOR *
 ***************************/
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



/*********
 * GATES *
 *********/
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



/**********************
 * CIRCUIT MANAGEMENT *
 **********************/
//Circuit cleaning
void QuantumCircuit::purge_operations()
{
    for (unsigned short i=circuit.size(); i>0; --i)
    {
        if (circuit[i].target_qubit != nullptr)
        {delete[] circuit[i].target_qubit; }
        if (circuit[i].control_qubit != nullptr)
        {delete[] circuit[i].control_qubit; }
        circuit.pop_back();
    }
}
void QuantumCircuit::optimize()
{}
void QuantumCircuit::print()
{
    printf("Debug of QuantumCircuit.");
    printf("Contains: \n\t%d\tqubits\n\t%d\tclbits\n\t%d\tgates", this->n_qubit, this->n_clbit, this->circuit.size());
    printf("Qubits:");
    for (unsigned short i=0; i<n_qubit; i++) {printf("\t%d", qubits[i]); }
    for (unsigned short i=0; i<n_clbit; i++) {printf("\t%d", clbits[i]); }
}
void QuantumCircuit::debug_operations()
{
    printf("Debug of Quantum Circuit Operations:\n");
    for (unsigned short i=0; i<circuit.size(); i++)
    {
        printf("Gate n°%d", i);
        circuit[i].debug_operation(); }
}
void QuantumCircuit::print_circuit()
{}



/*********************
 * CIRCUIT EMULATION *
 *********************/









/***************************
 * OPERATIONS CALCULATIONS *
 ***************************/

//Pauli gates
void QuantumCircuit::run_x(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 0)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        double newAlpha = xGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          xGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = xGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          xGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}
void QuantumCircuit::run_y(unsigned short op_index) //Multiply by xGate matrix ([[0,1],[1,0]]), aka swap alpha and beta
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 10)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        double newAlpha = yGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          yGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = yGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          yGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}
void QuantumCircuit::run_z(unsigned short op_index) //Multiply by xGate matrix ([[0,-i],[i,0]])
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 20)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        double newAlpha = zGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          zGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = zGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          zGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}

//Controlled Pauli gates
void QuantumCircuit::run_cx(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 1)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        if ((*(this->circuit[op_index].control_qubit[op_number])).value.r != 0.0 ||
            (*(this->circuit[op_index].control_qubit[op_number])).value.i != 1.0)
        {return; }

        double newAlpha = xGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          xGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = xGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          xGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}
void QuantumCircuit::run_cy(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 11)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        if ((*(this->circuit[op_index].control_qubit[op_number])).value.r != 0.0 ||
            (*(this->circuit[op_index].control_qubit[op_number])).value.i != 1.0)
        {return; }

        double newAlpha = yGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          yGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = yGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          yGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}
void QuantumCircuit::run_cz(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 21)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        if ((*(this->circuit[op_index].control_qubit[op_number])).value.r != 0.0 ||
            (*(this->circuit[op_index].control_qubit[op_number])).value.i != 1.0)
        {return; }

        double newAlpha = zGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          zGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = zGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          zGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
    }
}

//Toffoli gate
void QuantumCircuit::run_ccx(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 2)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned int op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        //Control bit n°1 (control_qubit[op_number*2]), skip if not |1>
        if ((*(this->circuit[op_index].control_qubit[2*op_number])).value.r != 0.0 ||
            (*(this->circuit[op_index].control_qubit[2*op_number])).value.i != 1.0)
        {return; }
        //Control bit n°2 (control_qubit[op_number*2 + 1]), skip if not |1>
        if ((*(this->circuit[op_index].control_qubit[2*op_number+1])).value.r != 0.0 || 
            (*(this->circuit[op_index].control_qubit[2*op_number+1])).value.i != 1.0)
        {return; }
        
        double newAlpha = xGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          xGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = xGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          xGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}

//Hammard gate
void QuantumCircuit::run_h(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 30)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned int op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        double newAlpha = hGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          hGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = hGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          hGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}
void QuantumCircuit::run_ch(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 31)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned int op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        if ((*(this->circuit[op_index].control_qubit[op_number])).value.r != 0.0 || 
            (*(this->circuit[op_index].control_qubit[op_number])).value.i != 1.0)
        {return; }

        double newAlpha = hGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          hGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = hGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          hGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}

// S & T gates
void QuantumCircuit::run_s(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 40)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        double newAlpha = sGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          sGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = sGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          sGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}
void QuantumCircuit::run_t(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 41)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        double newAlpha = tGate[0][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          tGate[0][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;
        double newBeta  = tGate[1][0] * (*(this->circuit[op_index].target_qubit[op_number])).value.r + 
                          tGate[1][1] * (*(this->circuit[op_index].target_qubit[op_number])).value.i;

        (*(this->circuit[op_index].target_qubit[op_number])).value.update(newAlpha, newBeta);
    }
}

//Swap gates
void QuantumCircuit::run_swap(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 50)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        comp tmp = (*(this->circuit[op_index].target_qubit[op_number*2])).value;
        (*(this->circuit[op_index].target_qubit[op_number*2])).value = (*(this->circuit[op_index].target_qubit[op_number*2 +1])).value;
        (*(this->circuit[op_index].target_qubit[op_number*2 + 1])).value = tmp;
    }
}
void QuantumCircuit::run_cswap(unsigned short op_index)
{
    //make sure good gate number and good operation to not cause segfaults
    if (this->circuit[op_index].get_gate_number() != 51)
    {std::cerr<<"Wrong gate"<<std::endl; }

    for (unsigned short op_number=0; op_number<this->circuit[op_index].size; op_number++)
    {
        //Control bit n°1 (control_qubit[op_number*2]), skip if not |1>
        if ((*(this->circuit[op_index].control_qubit[op_number])).value.r != 0.0 ||
            (*(this->circuit[op_index].control_qubit[op_number])).value.i != 1.0)
        {return; }

        comp tmp = (*(this->circuit[op_index].target_qubit[op_number*2])).value;
        (*(this->circuit[op_index].target_qubit[op_number*2])).value = (*(this->circuit[op_index].target_qubit[op_number*2 +1])).value;
        (*(this->circuit[op_index].target_qubit[op_number*2 + 1])).value = tmp;
    }
}