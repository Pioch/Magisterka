#include <math.h>
#include "matrix.h"
#include "Init.hpp"
#include "f_alpha.hpp"
#include "liczenie_H.hpp"

using namespace std;

Matrix<float> H(float alpha)
	{
		float eps1 = epsilon1();
		float eps2 = epsilon2();
		vector<float> f;
		Matrix<float> X1_f(3,1);
		Matrix<float> X2(3,1);
		Matrix<float> df_alpha(3,1);
		Matrix<float> H_alpha(3,3);

		f = f_alpha(alpha);
		X1_f.put(0,0, cos(f[2]));
		X1_f.put(1,0, sin(f[2]));
		X1_f.put(2,0, 0);

		X2.put(0,0, 0);
		X2.put(1,0, 0);
		X2.put(2,0, 1);

		df_alpha.put(0,0, (eps1*sin(eps2*cos(alpha))/eps2) - (eps1*cos(eps2*cos(alpha))*pow(sin(alpha), 2)/cos(alpha)) + (eps1*sin(eps2*cos(alpha))*pow(sin(alpha), 2)/(eps2*pow(cos(alpha), 2))));
		df_alpha.put(1,0, (-eps1*(cos(eps2*cos(alpha))-1)/eps2) - (eps1*sin(eps2*cos(alpha))*pow(sin(alpha), 2)/cos(alpha)) - (eps1*pow(sin(alpha), 2)*(cos(eps2*cos(alpha))-1)/(eps2*pow(cos(alpha), 2))));
		df_alpha.put(2,0, -eps2*sin(alpha));

		H_alpha.put(0,0, X1_f.get(0,0));
		H_alpha.put(1,0, X1_f.get(1,0));
		H_alpha.put(2,0, X1_f.get(2,0));
		H_alpha.put(0,1, X2.get(0,0));
		H_alpha.put(1,1, X2.get(1,0));
		H_alpha.put(2,1, X2.get(2,0));
		H_alpha.put(0,2, df_alpha.get(0,0));
		H_alpha.put(1,2, df_alpha.get(1,0));
		H_alpha.put(2,2, df_alpha.get(2,0));

		return H_alpha;

	}
	
	
