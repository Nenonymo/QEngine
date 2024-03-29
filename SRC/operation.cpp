#include "operation.h"
#include <iostream>

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
            this->target_clbit = nullptr;
            break;
        case 1: //  cx  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            this->target_clbit = nullptr;
            break;
        case 2: //  ccx 1t  2c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size*2];
            this->target_clbit = nullptr;
            break;
        case 5: //  rx  1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;

        // y Gates
        case 10: // y   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;
        case 11: // cy  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            this->target_clbit = nullptr;
            break;
        case 12: // ccy 1t  2c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size*2];
            this->target_clbit = nullptr;
            break;
        case 15: // ry  1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;

        // z Gates
        case 20: // z   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;
        case 21: // cz  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            this->target_clbit = nullptr;
            break;
        case 22: // ccz 1t  2c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size*2];
            this->target_clbit = nullptr;
            break;
        case 25: // rz  1t  0t
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;

        // Hammard Gates
        case 30: // h   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;
        case 31: // ch  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            this->target_clbit = nullptr;
            break;

        // S & T
        case 40: // s   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;
        case 41: // t   1t  0c
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;

        // Swap
        case 50: // Swap    2t  0c
            this->target_qubit = new qb*[2*size];
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;
        case 51: // cSwap   2t  1c
            this->target_qubit = new qb*[2*size];
            this->control_qubit = new qb*[size];
            this->target_clbit = nullptr;
            break;


        case 60: // cp  1t  1c
            this->target_qubit = new qb*[size];
            this->control_qubit = new qb*[size];
            this->target_clbit = nullptr;
            break;

        // Circuit management
        case 100: // barrier
            this->target_qubit = nullptr;
            this->control_qubit = nullptr;
            this->target_clbit = nullptr;
            break;
        case 101: // measuring  1t  1cb
            this->target_qubit = new qb*[size];
            this->control_qubit = nullptr;
            this->target_clbit = new cb*[size];
            break;

        //Classical gates
        case 110: // not    1cb
            this->target_qubit = nullptr;
            this->control_qubit = nullptr;
            this->target_clbit = new cb*[size];
            break;
        case 111: // and    3cb
            this->target_qubit = nullptr;
            this->control_qubit = nullptr;
            this->target_clbit = new cb*[size];
            break;
        case 112: // nand   3cb
            this->target_qubit = nullptr;
            this->control_qubit = nullptr;
            this->target_clbit = new cb*[size];
            break;
        case 113: // or     3cb
            this->target_qubit = nullptr;
            this->control_qubit = nullptr;
            this->target_clbit = new cb*[size];
            break;
        case 114: // nor    3cb
            this->target_qubit = nullptr;
            this->control_qubit = nullptr;
            this->target_clbit = new cb*[size];
            break;
        case 115: // xor    3cb
            this->target_qubit = nullptr;
            this->control_qubit = nullptr;
            this->target_clbit = new cb*[size];
            break;

        // Non listed gate number
        default:
            std::cerr<<"Invlaid gate number"<<std::endl;
            break;
    }
}


Operation::~Operation()
{
    delete[] this->target_qubit;
    delete[] this->control_qubit;
}


void Operation::debug_operation()
{
    switch(this->gate_number)
    {
        // x Gates
        case 0: //  x   1t  0c
            printf("x Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p}\n", i, this->target_qubit[i]); }
            break;
        case 1: //  cx  1t  1c
            printf("cx Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p; c=%p}\n", i, this->target_qubit[i], this->control_qubit[i]); }
            break;
        case 2: //  ccx 1t  2c
            printf("ccx Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p; c_1=%p; c_2=%p}\n", i, this->target_qubit[i], this->control_qubit[i*2], this->control_qubit[i*2 + 1]); }
            break;
        case 5: //  rx  1t  0c
            printf("rx Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p}\n", i, this->target_qubit[i]); }
            break;

        // y Gates
        case 10: // y   1t  0c
            printf("y Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p}\n", i, this->target_qubit[i]); }
            break;
        case 11: // cy  1t  1c
            printf("cy Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p; c=%pp}", i, this->target_qubit[i], this->control_qubit[i]); }
            break;
        case 12: // ccy 1t  2c
            printf("ccy Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p; c_1=%p; c_2=%p}\n", i, this->target_qubit[i], this->control_qubit[i*2], this->control_qubit[i*2 + 1]); }
            break;
        case 15: // ry  1t  0c
            printf("ry Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p}\n", i, this->target_qubit[i]); }
            break;

        // z Gates
        case 20: // z   1t  0c
            printf("z Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p}\n", i, this->target_qubit[i]); }
            break;
        case 21: // cz  1t  1c
            printf("cz Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p; c=%p}\n", i, this->target_qubit[i], this->control_qubit[i]); }
            break;
        case 22: // ccz 1t  2c
            printf("ccz Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p; c_1=%p; c_2=%p}\n", i, this->target_qubit[i], this->control_qubit[i*2], this->control_qubit[i*2 + 1]); }
            break;
        case 25: // rz  1t  0t
            printf("rz Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p}\n", i, this->target_qubit[i]); }
            break;

        // Hammard Gates
        case 30: // h   1t  0c
            printf("h Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p}\n", i, this->target_qubit[i]); }
            break;
        case 31: // ch  1t  1c
            printf("ch Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p; c=%p}\n", i, this->target_qubit[i], this->control_qubit[i]); }
            break;

        // S & T
        case 40: // s   1t  0c
            printf("s Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p}\n", i, this->target_qubit[i]); }
            break;
        case 41: // t   1t  0c
            printf("t Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t=%p}\n", i, this->target_qubit[i]); }
            break;

        // Swap
        case 50: // Swap    2t  0c
            printf("swap Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t_1=%p; t_2=%p}\n", i, this->target_qubit[i*2], this->target_qubit[i*2 + 1]); }
            break;
        case 51: // cSwap   2t  1c
            printf("cswap Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t_1=%p; t_2=%p}\n", i, this->target_qubit[i*2], this->target_qubit[i*2 + 1]); }
            break;

        // Controlled phase
        case 60: // cp  1t  1c
            printf("cp Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {t_1=%p; t_2=%p; c=%p}\n", i, this->target_qubit[i*2], this->target_qubit[i*2 + 1], this->target_qubit[i]); }
            break;

        // Circuit management
        case 100: // barrier
            printf("Barrier:\n");
            break;
        case 101: // measuring
            printf("Measure:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {qb=%p; cb=%p}\n", i, this->target_qubit[i], this->target_clbit[i]); }
            break;

        // Classical gates
        case 110: // not
            printf("not Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {cb=%p}\n", i, this->target_clbit[i]);}
            break;
        case 111: // and
            printf("and Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {i_1=%p; i_2=%p; o=%p}\n", i, this->target_clbit[i*3], this->target_clbit[i*3 +1], this->target_clbit[i*3 +2]); }
            break;
        case 112: // nand
            printf("nand Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {i_1=%p; i_2=%p; o=%p}\n", i, this->target_clbit[i*3], this->target_clbit[i*3 +1], this->target_clbit[i*3 +2]);}
            break;
        case 113: // or
            printf("or Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {i_1=%p; i_2=%p; o=%p}\n", i, this->target_clbit[i*3], this->target_clbit[i*3 +1], this->target_clbit[i*3 +2]);}
            break;
        case 114: // nor
            printf("nor Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {i_1=%p; i_2=%p; o=%p}\n", i, this->target_clbit[i*3], this->target_clbit[i*3 +1], this->target_clbit[i*3 +2]);}
            break;
        case 115: // xor
            printf("xor Gate:\n");
            for(unsigned short i=0; i<this->size; i++)
            {printf("\tOp n%d: {i_1=%p; i_2=%p; o=%p}\n", i, this->target_clbit[i*3], this->target_clbit[i*3 +1], this->target_clbit[i*3 +2]);}
            break;

        // Non listed gate number
        default:
            std::cerr<<"Invalid gate number, check documentation for more informations"<<std::endl;
            break;
    }
}

unsigned short Operation::get_gate_number() const
{return this->gate_number; }