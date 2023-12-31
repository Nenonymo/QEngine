#include <cmath>
#include <iostream>

#include "complex.h"



/****************
 * CONSTRUCTORS *
 ****************/
Complex::Complex()
{
    r=0.0f;
    i=0.0f;
}

Complex::Complex(double a, double b)
{
    r=a;
    i=b;
}

Complex::~Complex()
{}


/**************
 * GET VALUES *
 **************/
double* Complex::get()
{
    double* values = new double[2];
    values[0] = r;
    values[1] = i;
    return values;
}

double Complex::get_norm() const
{return sqrt(r*r + i*i); }



/*******************
 * TRANSFORMATIONS *
 *******************/
void Complex::conjugate()
{
    this->i = -(this->i);
}
Complex Complex::get_conjugate()
{
    return Complex(this->a, -(this->i));
}



/************************
 * ARITHMETIC OPERATORS *
 ************************/
Complex Complex::operator+ (Complex const& obj)
{return Complex(r+obj.r, i+obj.i); }

Complex Complex::operator- (Complex const& obj)
{return Complex(r-obj.r, i-obj.i); }

Complex Complex::operator* (Complex const& obj)
{return Complex(r*obj.r - i*obj.i, r*obj.i + i*obj.r); }



/************************
 * ASSIGNMENT OPERATORS *
 ************************/
void Complex::operator= (Complex const& obj)
{r=obj.r; i=obj.i; }

void Complex::operator+= (Complex const& obj)
{r=r+obj.r; i=i+obj.i; }

void Complex::operator-= (Complex const& obj)
{r=r-obj.r; i=i-obj.i; }



/************************
 * COMPARISON OPERATORS *
 ************************/
bool Complex::operator== (Complex const& obj)
{return (i==obj.i && r==obj.r); }

bool Complex::operator!= (Complex const& obj)
{return (i!=obj.i || r!=obj.r); }

bool Complex::operator<= (Complex const& obj)
{return (get_norm() <= obj.get_norm()); }

bool Complex::operator<  (Complex const& obj)
{return (this->get_norm() <  obj.get_norm()); }

bool Complex::operator>= (Complex const& obj)
{return (this->get_norm() >= obj.get_norm()); }

bool Complex::operator>  (Complex const& obj)
{return (this->get_norm() >  obj.get_norm()); }


/*********
 * DEBUG *
 *********/
void Complex::print()
{std::cout<<r<<"+"<<i<<"i"<<std::endl; }

void Complex::print_nr()
{std::cout<<r<<'+'<<i<<'i'; }