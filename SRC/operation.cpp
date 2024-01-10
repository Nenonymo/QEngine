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
            break;

        // Non listed gate number
        default:
            std::cerr<<"Invlaid gate number"<<std::endl;
            break;
    }
}

void Operation::debug_operation()
{
    switch(gate_number)
    {
        // x Gates
        case 0: //  x   1t  0c
            printf("x Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;
        case 1: //  cx  1t  1c
            printf("cx Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d; c=%d}", i, this->target_qubit[i], this->control_qubit[i]); }
            break;
        case 2: //  ccx 1t  2c
            printf("ccx Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d; c_1=%d; c_2=%d}", i, this->target_qubit[i], this->control_qubit[i*2], this->control_qubit[i*2 + 1]); }
            break;
        case 5: //  rx  1t  0c
            printf("rx Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;

        // y Gates
        case 10: // y   1t  0c
            printf("y Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;
        case 11: // cy  1t  1c
            printf("cy Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d; c=%d}", i, this->target_qubit[i], this->control_qubit[i]); }
            break;
        case 12: // ccy 1t  2c
            printf("ccy Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d; c_1=%d; c_2=%d}", i, this->target_qubit[i], this->control_qubit[i*2], this->control_qubit[i*2 + 1]); }
            break;
        case 15: // ry  1t  0c
            printf("ry Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;

        // z Gates
        case 20: // z   1t  0c
            printf("z Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;
        case 21: // cz  1t  1c
            printf("cz Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d; c=%d}", i, this->target_qubit[i], this->control_qubit[i]); }
            break;
        case 22: // ccz 1t  2c
            printf("ccz Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d; c_1=%d; c_2=%d}", i, this->target_qubit[i], this->control_qubit[i*2], this->control_qubit[i*2 + 1]); }
            break;
        case 25: // rz  1t  0t
            printf("rz Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;

        // Hammard Gates
        case 30: // h   1t  0c
            printf("h Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;
        case 31: // ch  1t  1c
            printf("ch Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d; c=%d}", i, this->target_qubit[i], this->control_qubit[i]); }
            break;

        // S & T
        case 40: // s   1t  0c
            printf("s Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;
        case 41: // t   1t  0c
            printf("t Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;

        // Swap
        case 50: // Swap    2t  0c
            printf("swap Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t_1=%d; t_2=%d}", i, this->target_qubit[i*2], this->target_qubit[i*2 + 1]); }
            break;
        case 51: // cSwap   2t  1c
            printf("cswap Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t_1=%d; t_2=%d}", i, this->target_qubit[i*2], this->target_qubit[i*2 + 1]); }
            break;

        // Controlled phase
        case 60: // cp  1t  1c
            printf("cp Gate");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t_1=%d; t_2=%d; c=%d}", i, this->target_qubit[i*2], this->target_qubit[i*2 + 1], this->target_qubit[i]); }
            break;

        // Circuit management
        case 100: // barrier
            printf("Barrier");
            break;
        case 101: // measuring
            printf("Measure");
            for(unsigned short i=0; i<this->size; i++)
            {printf("Op n°%d: {t=%d}", i, this->target_qubit[i]); }
            break;

        // Non listed gate number
        default:
            std::cerr<<"Invalid gate number, check documentation for more informations"<<std::endl;
            break;
    }
}