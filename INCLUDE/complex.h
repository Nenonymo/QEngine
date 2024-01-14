#pragma once


class Complex
{
    public:
        double r;
        double i;

        Complex();
        Complex(double a, double b);

        ~Complex();

        //get values
        double* get();
        double get_norm() const;

        //change values
        void update(double r, double i, char normalize=1);
        
        //Transformations
        void conjugate();
        Complex get_conjugate();

        //Arithmetic operations
        Complex operator+ (Complex const& obj);
        Complex operator- (Complex const& obj);
        Complex operator* (Complex const& obj);
        Complex operator* (double const& d);
        //Complex operator/ (Complex const& obj);

        //Assignment operators
        void operator=  (Complex const& obj);
        void operator+= (Complex const& obj);
        void operator-= (Complex const& obj);

        //Comparison operators
        bool operator== (Complex const& obj);
        bool operator!= (Complex const& obj);
        bool operator<= (Complex const& obj);
        bool operator<  (Complex const& obj);
        bool operator>= (Complex const& obj);
        bool operator>  (Complex const& obj);

        //Debug
        void print();
        void print_nr();

    private:
        void normalize();

};

typedef Complex comp;