#include "interface.h"

#include <iostream>

QuantumCircuit circuit_from_console()
{
    //Quantum Circuit dimensions
    unsigned short n_qb, n_cb;
    std::cin>>n_qb>>n_cb;
    QuantumCircuit circuit(n_qb, n_cb);

    //Gates
    unsigned short n_gates;
    std::cin>>n_gates;
    for (unsigned short gate=0; gate<n_gates; gate++)
    {
        unsigned short gate_number;
        std::cin>> gate_number;
        unsigned short arg1, arg2, arg3;
        double argD;
        switch (gate_number)
        {
        case 0: // x gate
            std::cin>>arg1;
            circuit.x(arg1);
            break;
        case 1: // cx gate
            std::cin>>arg1>>arg2;
            circuit.cx(arg1, arg2);
            break;
        case 2: // ccx gate
            std::cin>>arg1>>arg2>>arg3;
            circuit.ccx(arg1, arg2,arg3);
            break;
        case 5: // rx gate
            std::cin>>arg1>>argD;
            circuit.rx(argD, arg1);
            break;

        case 10: // y gate
            std::cin>>arg1;
            circuit.y(arg1);
            break;
        case 11: // cy gate
            std::cin>>arg1>>arg2;
            circuit.cy(arg1, arg2);
            break;
        case 15: // rx gate
            std::cin>>arg1>>argD;
            circuit.rx(argD, arg1);
            break;

        case 20: // z gate
            std::cin>>arg1;
            circuit.z(arg1);
            break;
        case 21: // cz gate
            std::cin>>arg1>>arg2;
            circuit.cz(arg1, arg2);
            break;
        case 25: // rx gate
            std::cin>>arg1>>argD;
            circuit.rx(argD, arg1);
            break;

        case 30: // h gate
            std::cin>>arg1;
            circuit.h(arg1);
            break;
        case 31: // ch gate
            std::cin>>arg1>>arg2;
            circuit.ch(arg1, arg2);
            break;

        case 40: // s gate
            std::cin>>arg1;
            circuit.s(arg1);
            break;

        case 41: // t gate
            std::cin>>arg1;
            circuit.t(arg1);
            break;

        case 50: // swap gate
            std::cin>>arg1>>arg2;
            circuit.swap(arg1, arg2);
            break;
        case 51: // cswap gate
            std::cin>>arg1>>arg2>>arg3;
            circuit.cswap(arg1, arg2, arg3);
            break;
        
        case 60: // cp gate
            std::cin>>arg1>>arg2>>argD;
            circuit.cp(argD, arg1, arg2);
            break;
        
        case 100:
            circuit.barrier();
            break;
        case 101:
            std::cin>>arg1>>arg2;
            circuit.measure(arg1, arg2);
            break;

        case 110: // not gate
            std::cin>>arg1;
            circuit.not_(arg1);
            break;
        case 111: // cswap gate
            std::cin>>arg1>>arg2>>arg3;
            circuit.and_(arg1, arg2, arg3);
            break;
        case 112: // cswap gate
            std::cin>>arg1>>arg2>>arg3;
            circuit.nand_(arg1, arg2, arg3);
            break;
        case 113: // cswap gate
            std::cin>>arg1>>arg2>>arg3;
            circuit.or_(arg1, arg2, arg3);
            break;
        case 114: // cswap gate
            std::cin>>arg1>>arg2>>arg3;
            circuit.nor_(arg1, arg2, arg3);
            break;
        case 115: // cswap gate
            std::cin>>arg1>>arg2>>arg3;
            circuit.xor_(arg1, arg2, arg3);
            break;

        default:
            printf("Gate number not recognized:%d\n", gate_number);
            break;

        }
    }
    return circuit;
}