#ifndef kinematyka_hpp
#define kinematyka_hpp

#include <vector>
#include "matrix.h"

using namespace std;

vector<float> position_update(float x_, float y_, float th_, Matrix<float> u);
float liczenie_alpha(float alpha_1, Matrix<float> u);

#endif
