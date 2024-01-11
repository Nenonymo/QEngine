#include "bit.h"


Bit::Bit() 
{}
Bit::~Bit()
{}

char Bit::measure() const
{}
char* Bit::to_cstring() const
{}


/***************
 * QUANTUM BIT *
 ***************/
QuBit::QuBit(double alpha, double beta)
{
    this->value.r = alpha,
    this->value.i = beta;
    normalize();
}

QuBit::QuBit()
{
    this->value.r = 1.0f;
    this->value.i = 0.0f;
    normalize();
}

QuBit::~QuBit()
{
    
}


char QuBit::measure() const
{
    if (static_cast<double>(rand()) / RAND_MAX < pow(this->value.r, 2)) 
    {return 0; }
    return 1;
}

void QuBit::normalize()
{
    double factor = std::sqrt(pow(this->value.r, 2) + pow(this->value.i, 2));
    this->value.r /= factor;
    this->value.i /= factor;
}

char* QuBit::to_cstring() const
{
    char buffer[14];
    sprintf(buffer, "(%.3f;%.3f)", this->value.r, this->value.i);
    return buffer;
}


/*****************
 * CLASSICAL BIT *
 *****************/
ClBit::ClBit()
{this->value = 0; }

ClBit::~ClBit()
{}

char ClBit::measure() const
{return this->value; }

char* ClBit::to_cstring() const
{
    char buffer[4];
    sprintf(buffer, "(%d)", this->value);
    return buffer;
}

