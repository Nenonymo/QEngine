#pragma once

#include "bit.h"


class Operation
{
    private:
        char gate_number;
        

    public:
        qb** target_qubit;
        qb** control_qubit;
        cb** target_clbit;
        double parameter;
        unsigned short size;

        Operation(char gate_number, unsigned short size);
        ~Operation();

        void debug_operation();
        unsigned short get_gate_number() const;
};
