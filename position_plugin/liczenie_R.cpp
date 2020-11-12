#include <math.h>
#include <vector>
#include "matrix.h"
#include "liczenie_R.hpp"

using namespace std;

Matrix<float> R(float th)
{
	Matrix<float> r(2,2); // (wierszy, kolumn) przy przypisywaniu wartosci do konkretnych komorek zaczyna sie od 0, czyli tutaj 0-1 indeksy
	
	r.put(0,0,cos(th));
	r.put(1,0, sin(th));
	r.put(0,1, -sin(th));
	r.put(1,1, cos(th));
	

	return r;
	
}
