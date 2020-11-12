#include <math.h>
#include <vector>
#include "matrix.h"
#include "dzialanie_grupowe.hpp"
#include "liczenie_R.hpp"

using namespace std;

vector<float> liczenie_grupy(vector<float> g1, vector<float> g2)
{
	vector<float> g3;
	Matrix<float> g3a(2,1);
	Matrix<float> g1a(2,1);
	Matrix<float> g2a(2,1);

	g1a.put(0,0, g1[0]);
	g1a.put(1,0, g1[1]);
	g2a.put(0,0, g2[0]);
	g2a.put(1,0, g2[1]);

	g3a = g1a + R(g1[2])*g2a;

	g3.push_back(g3a.get(0,0));
	g3.push_back(g3a.get(1,0));
	g3.push_back(g1[2]+g2[2]);

	return g3;
}
