#include "bit.h"


/***************
 * QUANTUM BIT *
 ***************/
QuBit::QuBit(double alpha, double beta)
{
    this->alpha = alpha,
    this->beta = beta;
    normalize();
}

QuBit::QuBit()
{
    this->alpha = 1.0f;
    this->beta = 0.0f;
    normalize();
}

QuBit::~QuBit()
{
    
}


char QuBit::measure() const
{
    if (static_cast<double>(rand()) / RAND_MAX < pow(alpha, 2)) 
    {return 0; }
    return 1;
}

void QuBit::normalize()
{
    double factor = std::sqrt(pow(alpha, 2) + pow(beta, 2));
    alpha /= factor;
    beta /= factor;
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

