#pragma once

#include "complex.h"

class Matrice
{
    public:
        Matrice();
        Matrice(unsigned int rows, unsigned int cols);
        ~Matrice();

        //Get alues functions
        unsigned int get_size() const;
        unsigned int get_rows() const;
        unsigned int get_cols() const;
        comp get_val(unsigned int pos) const;
        comp* get_val_ad(unsigned int pos) const;

        //Set values functions
        void set_val(unsigned int pos, comp val);

        //Arithmetic operators
        Matrice operator+ (Matrice const& obj);
        Matrice operator- (Matrice const& obj);
        Matrice operator* (Matrice const& obj);

        //Assignment operators
        void operator= (Matrice const& obj);

        //Array operators
        comp& operator[] (unsigned int i);
        comp operator[] (unsigned int i) const;

        //Comparison operators
        bool operator== (Matrice const& obj);
        bool operator!= (Matrice const& obj);

        //Matrice functions
        comp dot_product(Matrice const& obj);
        Matrice dagger();

        //Debug functions
        void print();
        void print_nr();

    private:
        unsigned int rows, cols;
        comp* values;

};

typedef Matrice mat;

//Operation functions
comp mat_dot_product(Matrice& a, Matrice& b);