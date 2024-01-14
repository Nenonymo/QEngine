#include <stdlib.h>
#include <iostream>

#include "interface.h"

using namespace std;

unsigned short bin_to_int(char* value, unsigned short size)
{
    unsigned short result=0;
    for (unsigned short i=0; i<size; i++)
    {
        if (value[i] == 1)
        {result+=std::pow(2, i); }
    }
    return result;
}

int main(int argc, char* argv[])
{
    QuantumCircuit circuit = circuit_from_console();

    unsigned short n = 1;
    if (argc >= 2)
    {n = atoi(argv[1]); }
    
    std::cout<<std::endl;        
    for (unsigned short i=0; i<n; i++)
    {
        char* results = circuit.run();
        printf("%d ", bin_to_int(results, circuit.get_ouptut_size()));
    }
    std::cout<<std::endl;
    
    return 0;
}