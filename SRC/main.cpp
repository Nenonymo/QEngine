#include <stdlib.h>

#include "complex.h"

int main(int argc, char* argv[])
{
    comp a(3, 5);
    comp b(1, 2);

    a.print();
    b.print();
    comp c = a+b;
    c.print();
    c+=b;
    c.print();
    return 0;
}