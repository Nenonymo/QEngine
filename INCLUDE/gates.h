#pragma once

#include <cmath>

double xGate[2][2] = {{0, 1}, {1, 0}};
double yGate[2][2] = {{0, -1}, {1, 0}}; // supposed to be [[0,-i],[i,0]]
double zGate[2][2] = {{1, 0}, {0, -1}};

double sGate[2][2] = {{1, 0}, {0, i}};
double tGate[2][2] = {{1, 0}, {0, std::exp(M_PI/4)}};