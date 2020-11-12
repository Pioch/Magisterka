#include <iostream>
#include <math.h>
#include <vector>
#include "matrix.h"
#include "Init.hpp"
#include "kinematyka.hpp"

using namespace std;

vector<float> position_update(float x_, float y_, float th_, Matrix<float> u)
{
	float x, y, th, dT;
	float v, omega;
	vector<float> tab;
	dT = delta_t();
	
	v = u.get(0,0);
	omega = u.get(1,0);
		
	x = x_ + dT*v*cos(th_);
	y = y_ + dT*v*sin(th_);
	th = th_ + dT*omega;
	
	tab.push_back(x);
	tab.push_back(y);
	tab.push_back(th);
	
	return tab;
} 

float liczenie_alpha(float alpha_1, Matrix<float> u)
{
	float alpha, dT;
	
	dT = delta_t();
	alpha = alpha_1 - dT*u.get(2,0);
	
	return alpha;
}
