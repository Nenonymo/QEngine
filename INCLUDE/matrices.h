#include "complex.h"

class Matrice
{
    public:
        Matrice(unsigned int rows, unsigned int cols);
        ~Matrice();

        unsigned int get_size();
        comp get_val(unsigned int pos);

        //Arithmetic operators
        Matrice operator+ (Matrice const& obj);
        Matrice operator- (Matrice const& obj);

        //Assignment operators
        void operator= (Matrice const& obj);
        void operator+= (Matrice const& obj);
        void operator-= (Matrice const& obj);

        //Array operators
        comp& operator[] (unsigned int i);
        comp operator[] (unsigned int i) const;

        //Comparison operators
        bool operator== (Matrice const& obj);
        bool operator!= (Matrice const& obj);

    private:
        unsigned int rows, cols;
        comp* values;

};

typedef Matrice mat;

//Operation functions
Matrice dot_product(const Matrice& a, const Matrice& b);