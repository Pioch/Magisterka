#include <math.h>
#include <vector>
#include "matrix.h"
#include "liczenie_R.hpp"
#include "odwrotnosc_g.hpp"

using namespace std;

vector<float> odwrotnosc(vector<float> g)
{
	vector<float> g_minus;
	Matrix<float> g_1(2,1);
	Matrix<float> g_2(2,1);

	g_1.put(0,0, g[0]);
	g_1.put(1,0, g[1]);
	g_2 = R(-g[2])*(-1)*g_1;


	g_minus.push_back(g_2.get(0,0));
	g_minus.push_back(g_2.get(1,0));
	g_minus.push_back(-g[2]);

	return g_minus;

}
