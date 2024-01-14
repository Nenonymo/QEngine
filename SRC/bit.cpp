#include "bit.h"


Bit::Bit() 
{}
Bit::~Bit()
{}

char Bit::measure()
{
    return -1;
}
std::string Bit::to_cstring() const
{ return std::string();}

void Bit::clear_bit()
{}

/***************
 * QUANTUM BIT *
 ***************/
QuBit::QuBit(double alpha, double beta)
{
    this->value.r = alpha,
    this->value.i = beta;
    this->amp0 = comp(alpha, 0);
    this->amp1 = comp(beta, 0);
    normalize();
}

QuBit::QuBit()
{
    this->value.r = 1.0f;
    this->value.i = 0.0f;
    normalize();
    this->amp0 = comp(1, 0);
    this->amp1 = comp(0, 0);
}

QuBit::~QuBit()
{
}


char QuBit::measure()
{
    if (static_cast<double>(rand()) / RAND_MAX < pow(this->amp0.get_norm(), 2)) 
    {   
        this->amp1 = comp(0, 0);
        return 0; 
    }
    else
    {
        this->amp0 = comp(0, 0);
        return 1;
    }
    
}

void QuBit::normalize()
{
    double factor = std::sqrt(pow(this->value.r, 2) + pow(this->value.i, 2));
    this->value.r /= factor;
    this->value.i /= factor;
}

std::string QuBit::to_cstring() const
{
    char buffer[14];
    sprintf(buffer, "(%.3f;%.3f)", this->value.r, this->value.i);
    std::string str = buffer;
    return str;
}

void QuBit::clear_bit()
{
    this->value.r = 1.0;
    this->value.i = 0.0;
}

std::ostream& operator<<(std::ostream& os, const QuBit& obj)
{
    os << "|0> (" << obj.amp0.r << ";" << obj.amp0.i << " |1> (" << obj.amp1.r << ";" << obj.amp1.i << ")";
    return os;
}


/*****************
 * CLASSICAL BIT *
 *****************/
ClBit::ClBit()
{this->value = 0; }

ClBit::~ClBit()
{
}

char ClBit::measure()
{return this->value; }

std::string ClBit::to_cstring() const
{
    char buffer[7];
    sprintf(buffer, "(%d)", this->value);
    return buffer;
}

void ClBit::clear_bit()
{
    this->value = 0;
}

