#include "matrices.h"



/****************************
 * CONSTRUCTOR & DESTRUCTOR *
 ****************************/
Matrice::Matrice(unsigned int rows, unsigned int cols)
{
    this->rows = rows;
    this->cols = cols;
    this->values = new comp[rows*cols];
}

Matrice::~Matrice()
{
    delete[] values;
}



/************************
 * GET VALUES FONCTIONS *
 ************************/
unsigned int Matrice::get_size() {return rows*cols; }
comp Matrice::get_val(unsigned int pos) {return values[pos]; }



/************************
 * ARITHMETIC OPERATORS *
 ************************/
Matrice Matrice::operator+ (Matrice const& obj)
{}

Matrice Matrice::operator- (Matrice const& obj)
{}


comp& Matrice::operator[] (unsigned int i)
{return this->values[i]; }

comp  Matrice::operator[] (unsigned int i) const
{return this->values[i]; }



/************************
 * ASSIGNMENT OPERATORS *
 ************************/
void Matrice::operator= (Matrice const& obj)
{}

void Matrice::operator+= (Matrice const& obj)
{}

void Matrice::operator-= (Matrice const& obj)
{}



/************************
 * COMPARISON OPERATORS *
 ************************/
bool Matrice::operator== (Matrice const& obj)
{
    for (unsigned int i=0; i<this->get_size(); i++)
    {
        if (this->values[i] != (obj[i])) {return 0; }
    }
}

bool Matrice::operator!= (Matrice const& obj)
{
    for (unsigned int i=0; i<this->get_size(); i++)
    {
        if (this->values[i] != (obj[i])) {return 1; }
    }
}