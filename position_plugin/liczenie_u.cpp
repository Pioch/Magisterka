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
#include "liczenie_u.hpp"

using namespace std;

Matrix<float> sterowanie(vector<float> gr, vector<float> g_prim, vector<float> g, float alpha, float v0, float omega0, int dojazd)
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
		Matrix<float> P(3,1);
		Matrix<float> P_1(3,1);
		Matrix<float> P_2(3,1);
		Matrix<float> u1(3,1);
		Matrix<float> u(9,1);

		float K;
		float przyspieszenie = 11;
		float przyspieszenie_k = 18;
		float v_max = 5;
		float dT = delta_t();
		
		if(dojazd == 1)
		{
			K = -0.5;
		}
		
		if(dojazd == 0)
		{
			K = -3;
		}	
		
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

		P_1.put(0,0, cos(g_e[2]));
		P_1.put(1,0, sin(g_e[2]));
		P_1.put(2,0, 0);
		P_1 = P_1*g_prim[0];

		P_2.put(0,0, 0);
		P_2.put(1,0, 0);
		P_2.put(2,0, 1);
		P_2 = P_2*g_prim[1];

		P = P_1 + P_2;

		u1 = inv_H*(dlz_minus1_g_e*(drf_g_e*Z_z+P));
		
		if(dojazd == 0)
		{
		
		if((u1.get(0,0)-v0)/dT > przyspieszenie)
		{
			u1.put(0,0, v0 + przyspieszenie*dT);
		}
	
		if((u1.get(0,0)-v0)/dT < -przyspieszenie)
		{
			u1.put(0,0, v0 - przyspieszenie*dT);
		}
		
		
		if((u1.get(1,0)-omega0)/dT > przyspieszenie_k)
		{
			u1.put(1,0, omega0 + przyspieszenie_k*dT);
		}
	
		if((u1.get(1,0)-omega0)/dT < -przyspieszenie_k)
		{
			u1.put(1,0, omega0 - przyspieszenie_k*dT);
		}
		
		}
		
		/*if(u1.get(0,0) > v_max)
		{
			u1.put(0,0, v_max);
		} 
		
		if(u1.get(0,0) < -v_max)
		{
			u1.put(0,0, -v_max);
		} */
		
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
