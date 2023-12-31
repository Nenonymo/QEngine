#pragma once

#include <cmath>


class QuBit
{
    private:
        //Values
        double alpha;
        double beta;

        //Internal functions
        void normalize();

    public:
        //Constructor
        QuBit(double alpha, double beta);
        QuBit();
        ~QuBit();

        //Value grabbing
        double getAlpha() const;
        double getBeta() const;

        void setAlpha(double new_value); //TODO
        void setBeta(double new_value); //TODO


        //QuBit operations
        char measure() const;
};

typedef QuBit qb;


class ClBit
{
    private:
        char value;

    public:
        ClBit();
        ~ClBit();

        char measure() const;

};

typedef ClBit cb;