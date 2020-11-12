
#ifndef liczenie_u_hpp
#define liczenie_u_hpp

#include <vector>
#include "matrix.h"

using namespace std;

Matrix<float> sterowanie(vector<float> gr, vector<float> g_prim, vector<float> g, float alpha, float v0, float omega0, int dojazd);

#endif
