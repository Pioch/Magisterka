#include <math.h>
#include <vector>
#include "matrix.h"
#include "f_alpha.hpp"
#include "Init.hpp"

using namespace std;

vector<float> f_alpha(float alpha)
{
	float eps1, eps2;
	vector<float> f_a;

	eps1 = epsilon1();
	eps2 = epsilon2();

	f_a.push_back(eps1*sin(alpha)*sin(eps2*cos(alpha))/(eps2*cos(alpha)));
	f_a.push_back(eps1*sin(alpha)*(1-cos(eps2*cos(alpha)))/(eps2*cos(alpha)));
	f_a.push_back(eps2*cos(alpha));

	return f_a;

}
