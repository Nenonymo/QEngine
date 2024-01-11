#include "gates.h"

char not_gate(char target)
{return (1 - target); }

char and_gate(char input_1, char input_2)
{return (input_1 && input_2); }

char nand_gate(char input_1, char input_2)
{return 1-(input_1 && input_2); }

char or_gate(char input_1, char input_2)
{return (input_1 || input_2); }

char nor_gate(char input_1, char input_2)
{return 1-(input_1 || input_2); }

char xor_gate(char input_1, char input_2)
{return (input_1 != input_2); }
