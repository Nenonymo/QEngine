#include "matrices.h"

#include <iostream>


/****************************
 * CONSTRUCTOR & DESTRUCTOR *
 ****************************/
Matrice::Matrice()
{
    this->rows = 0;
    this->cols = 0;
    this->values = new comp[0];
}
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
 * GET VALUES FUNCTIONS *
 ************************/
unsigned int Matrice::get_size() const 
{return rows*cols; }

unsigned int Matrice::get_rows() const
{return rows; }

unsigned int Matrice::get_cols() const
{return cols; }

comp Matrice::get_val(unsigned int pos) const 
{return values[pos]; }

comp* Matrice::get_val_ad(unsigned int pos) const
{return &(values[pos]); }



/************************
 * SET VALUES FUNCTIONS *
 ************************/
void Matrice::set_val (unsigned int pos, comp val)
{
    this->values[pos] = val;
}



/************************
 * ARITHMETIC OPERATORS *
 ************************/
Matrice Matrice::operator+ (Matrice const& obj)
{
    if (get_size() != obj.get_size()) 
    {std::cerr << "Matrices must be of same dimension" << std::endl; }
    Matrice tmp = Matrice(this->rows, this->cols);
    for (unsigned int i = 0; i < this->get_size(); i++)
    {tmp.set_val(i, this->get_val(i) + obj.get_val(i)); }
    return tmp;
}

Matrice Matrice::operator- (Matrice const& obj)
{
    if (get_size() != obj.get_size()) 
    {std::cerr << "Matrices must be of same dimension" << std::endl; }
    Matrice tmp = Matrice(this->rows, this->cols);
    for (unsigned int i = 0; i < this->get_size(); i++)
    {tmp.set_val(i, this->get_val(i) - obj.get_val(i)); }
    return tmp;
}

Matrice Matrice::operator* (Matrice const& obj)
{
    if (get_size() != obj.get_size())
    {std::cerr << "Matrices must be of corresponding dimension" << std::endl; }
    Matrice tmp(this->rows, obj.cols);
    for (unsigned int row = 0; row < this->rows; row++)
    {
        for (unsigned int col = 0; col < obj.cols; col++)
        {
            comp value(0,0);
            for (unsigned int i=0; i<this->cols; i++)
            {
                value+= this->get_val(row*this->cols + i) + obj.get_val(obj.rows*i + col);
            }
            tmp.set_val(row * this->rows + col, value);
        }
    }
    return tmp;
}



/************************
 * ASSIGNMENT OPERATORS *
 ************************/
void Matrice::operator= (Matrice const& obj)
{
    std::cout<<"manual copy, let's go"<<std::endl;
    if (this->rows != obj.rows || this->cols != obj.cols)
    {
        this->rows = obj.rows;
        this->cols = obj.cols;
        delete[] this->values;
        this->values = new comp[rows*cols];
    }
    for (unsigned int i=0; i<rows*cols; i++)
    {
        values[i] = *(obj.get_val_ad(i));
    }
}



/*******************
 * ARRAY OPERATORS *
 *******************/
comp& Matrice::operator[] (unsigned int i)
{return this->values[i]; }

comp  Matrice::operator[] (unsigned int i) const
{return this->values[i]; }



/************************
 * COMPARISON OPERATORS *
 ************************/
bool Matrice::operator== (Matrice const& obj)
{
    for (unsigned int i=0; i<this->get_size(); i++)
    {
        if (this->values[i] != (obj[i])) {return 0; }
    }
    return 1;
}

bool Matrice::operator!= (Matrice const& obj)
{
    for (unsigned int i=0; i<this->get_size(); i++)
    {
        if (this->values[i] != (obj[i])) {return 1; }
    }
    return 1;
}



/*********************
 * MATRICE FUNCTIONS *
 *********************/
comp Matrice::dot_product(Matrice const& obj) //TODO dot product
{
    if (this->cols != obj.rows || this->rows != obj.cols)
    {std::cerr<<"Matrices must be of corresponding dimensions"<<std::endl; }
    comp result;
    for (unsigned int i = 0; i < this->get_size(); i++)
    {
        result += this->get_val(i) * obj.get_val(i);
    }
}


Matrice Matrice::dagger() //TODO dagger
{

}



/*******************
 * DEBUG FUNCTIONS *
 *******************/
void Matrice::print()
{
    for (unsigned int r=0; r<this->rows; r++)
    {
        for (unsigned int c=0; c<this->cols; c++)
        {
            this->values[r*cols + c].print_nr();
            std::cout<<' ';
        }
        std::cout<<std::endl;
    }
}

void Matrice::print_nr()
{
    for (unsigned int r=0; r<this->rows; r++)
    {
        for (unsigned int c=0; c<this->cols; c++)
        {
            this->values[r*cols + c].print_nr();
            std::cout<<' ';
        }
        if (r<this->rows-1) {std::cout<<"  /  "; }
    }
    std::cout<<std::endl;
}



/***********************
 * OPERATION FUNCTIONS *
 ***********************/
comp mat_dot_product(Matrice&a, Matrice&b)
{return a.dot_product(b); }