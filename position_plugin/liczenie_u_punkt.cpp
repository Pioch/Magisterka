#include <math.h>
#include <vector>
#include <iostream>
#include "matrix.h"
#include "liczenie_R.hpp"
#include "odwrotnosc_g.hpp"
#include "Init.hpp"
#include "dzialanie_grupowe.hpp"
#include "liczenie_H.hpp"
#include "f_alpha.hpp"
#include "liczenie_u_punkt.hpp"

using namespace std;

Matrix<float> sterowanie_punkt(vector<float> gr, vector<float> g, float alpha)
	{
		vector<float> f;
		vector<float> inv_f;
		vector<float> inv_gr;
		vector<float> g_e;
		vector<float> z;
		vector<float> inv_z;
		Matrix<float> Z_z(3,1);
		Matrix<float> R_z(2,2);
		Matrix<float> dlz_minus1_g_e(3,3);
		Matrix<float> inv_H(3,3);
		Matrix<float> drf_g_e(3,3);
		Matrix<float> drf_g_e1(2,2);
		Matrix<float> drf_g_e2(2,1);
		Matrix<float> drf_g_e3(2,1);
		Matrix<float> u1(3,1);
		Matrix<float> u(9,1);

		float K = -1;

		f = f_alpha(alpha);
		inv_f = odwrotnosc(f);
		inv_gr = odwrotnosc(gr);
		g_e = liczenie_grupy(inv_gr, g);
		z = liczenie_grupy(g_e, inv_f);
		inv_z = odwrotnosc(z);

		Z_z.put(0,0, z[0]);
		Z_z.put(1,0, z[1]);
		Z_z.put(2,0, z[2]);
		Z_z = Z_z*K;
		R_z = R(inv_z[2]);

		dlz_minus1_g_e.put(0,0, R_z.get(0,0));
		dlz_minus1_g_e.put(1,0, R_z.get(1,0));
		dlz_minus1_g_e.put(2,0, 0);
		dlz_minus1_g_e.put(0,1, R_z.get(0,1));
		dlz_minus1_g_e.put(1,1, R_z.get(1,1));
		dlz_minus1_g_e.put(2,1, 0);
		dlz_minus1_g_e.put(0,2, 0);
		dlz_minus1_g_e.put(1,2, 0);
		dlz_minus1_g_e.put(2,2, 1);

		inv_H = H(alpha).getInverse();

		drf_g_e1 = R(z[2]);
		drf_g_e2.put(0,0, -f[1]);
		drf_g_e2.put(1,0, f[0]);
		drf_g_e3 = drf_g_e1*drf_g_e2;

		drf_g_e.put(0,0, 1);
		drf_g_e.put(1,0, 0);
		drf_g_e.put(2,0, 0);
		drf_g_e.put(0,1, 0);
		drf_g_e.put(1,1, 1);
		drf_g_e.put(2,1, 0);
		drf_g_e.put(0, 2, drf_g_e3.get(0,0));
		drf_g_e.put(1,2, drf_g_e3.get(1,0));
		drf_g_e.put(2,2, 1);		

		u1 = inv_H*(dlz_minus1_g_e*(drf_g_e*Z_z));
		
		u.put(0,0, u1.get(0,0));
		u.put(1,0, u1.get(1,0));
		u.put(2,0, u1.get(2,0));
		u.put(3,0, g_e[0]);
		u.put(4,0, g_e[1]);
		u.put(5,0, g_e[2]);
		u.put(6,0, z[0]);
		u.put(7,0, z[1]);
		u.put(8,0, z[2]);
		

		return u;

	}
