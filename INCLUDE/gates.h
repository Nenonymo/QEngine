#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

double sq2 = std::sqrt(2.0);

double xGate[2][2] = {{0, 1}, {1, 0}};
double yGate[2][2] = {{0, -1}, {1, 0}}; // supposed to be [[0,-i],[i,0]]
double zGate[2][2] = {{1, 0}, {0, -1}};

double hGate[2][2] = {{1.0/sq2, 1.0/sq2}, {1.0/sq2, -1.0/sq2}};

double sGate[2][2] = {{1, 0}, {0, -1}};
double tGate[2][2] = {{1, 0}, {0, std::exp(M_PI/4)}};