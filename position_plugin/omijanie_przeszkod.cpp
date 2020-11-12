#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <sstream>
#include "matrix.h"
#include "Init.hpp"

using namespace std;

vector<float> wspolczynniki_wielomianow(float x0, float y0, float th0, float x1, float y1, float th1, float x2, float y2, float th2, float v0, float v1, float v2, int sigma)
{

	Matrix<float> W(6,6);
	Matrix<float> inv_W(6,6);
	Matrix<float> rownania_x(6,1);
	Matrix<float> rownania_y(6,1);

	Matrix<float> cx(6,1);
	Matrix<float> cy(6,1);
	vector<float> params;

	//W(0)

	W.put(0,0, 0);
	W.put(0,1, 0);
	W.put(0,2, 0);
	W.put(0,3, 0);
	W.put(0,4, 0);
	W.put(0,5, 1);


	W.put(1,0, 0);
	W.put(1,1, 0);
	W.put(1,2, 0);
	W.put(1,3, 0);
	W.put(1,4, 1);
	W.put(1,5, 0);

	//W(0.5)

	W.put(2,0, 0.03125);
	W.put(2,1, 0.0625);
	W.put(2,2, 0.125);
	W.put(2,3, 0.25);
	W.put(2,4, 0.5);
	W.put(2,5, 1);

	W.put(3,0, 0.3125);
	W.put(3,1, 0.5);
	W.put(3,2, 0.75);
	W.put(3,3, 1);
	W.put(3,4, 1);
	W.put(3,5, 0);


	//W(1)

	W.put(4,0, 1);
	W.put(4,1, 1);
	W.put(4,2, 1);
	W.put(4,3, 1);
	W.put(4,4, 1);
	W.put(4,5, 1);


	W.put(5,0, 5);
	W.put(5,1, 4);
	W.put(5,2, 3);
	W.put(5,3, 2);
	W.put(5,4, 1);
	W.put(5,5, 0);



	rownania_x.put(0,0, x0);
	rownania_x.put(1,0, sigma*v0*cos(th0));
	rownania_x.put(2,0, x1);
	rownania_x.put(3,0, sigma*v1*cos(th1));
	rownania_x.put(4,0, x2);
	rownania_x.put(5,0, sigma*v2*cos(th2));


	rownania_y.put(0,0, y0);
	rownania_y.put(1,0, sigma*v0*sin(th0));
	rownania_y.put(2,0, y1);
	rownania_y.put(3,0, sigma*v1*sin(th1));
	rownania_y.put(4,0, y2);
	rownania_y.put(5,0, sigma*v2*sin(th2));

	inv_W = W.getInverse();


	cx = inv_W*rownania_x;
	cy = inv_W*rownania_y;

	params.push_back(cx.get(0,0));
	params.push_back(cx.get(1,0));
	params.push_back(cx.get(2,0));
	params.push_back(cx.get(3,0));
	params.push_back(cx.get(4,0));
	params.push_back(cx.get(5,0));

	params.push_back(cy.get(0,0));
	params.push_back(cy.get(1,0));
	params.push_back(cy.get(2,0));
	params.push_back(cy.get(3,0));
	params.push_back(cy.get(4,0));
	params.push_back(cy.get(5,0));

	return params;
}

vector<float> wspolczynniki_wielomianow2(float x0, float y0, float th0, float x1, float y1, float th1, float v0, float v1, int sigma)
{

	Matrix<float> W(6,6);
	Matrix<float> inv_W(6,6);
	Matrix<float> rownania_x(6,1);
	Matrix<float> rownania_y(6,1);

	Matrix<float> cx(6,1);
	Matrix<float> cy(6,1);
	vector<float> params;

	//W(0)

	W.put(0,0, 0);
	W.put(0,1, 0);
	W.put(0,2, 0);
	W.put(0,3, 0);
	W.put(0,4, 0);
	W.put(0,5, 1);


	W.put(1,0, 0);
	W.put(1,1, 0);
	W.put(1,2, 0);
	W.put(1,3, 0);
	W.put(1,4, 1);
	W.put(1,5, 0);

	W.put(2,0, 0);
	W.put(2,1, 0);
	W.put(2,2, 0);
	W.put(2,3, 1);
	W.put(2,4, 0);
	W.put(2,5, 0);


	//W(1)

	W.put(3,0, 1);
	W.put(3,1, 1);
	W.put(3,2, 1);
	W.put(3,3, 1);
	W.put(3,4, 1);
	W.put(3,5, 1);

	W.put(4,0, 5);
	W.put(4,1, 4);
	W.put(4,2, 3);
	W.put(4,3, 2);
	W.put(4,4, 1);
	W.put(4,5, 0);

	W.put(5,0, 20);
	W.put(5,1, 12);
	W.put(5,2, 6);
	W.put(5,3, 2);
	W.put(5,4, 0);
	W.put(5,5, 0);



	rownania_x.put(0,0, x0);
	rownania_x.put(1,0, sigma*v0*cos(th0));
	rownania_x.put(2,0, -sigma*v0*sin(th0));
	rownania_x.put(3,0, x1);
	rownania_x.put(4,0, sigma*v1*cos(th1));
	rownania_x.put(5,0, -sigma*v1*sin(th1));


	rownania_y.put(0,0, y0);
	rownania_y.put(1,0, sigma*v0*sin(th0));
	rownania_y.put(2,0, sigma*v0*cos(th0));
	rownania_y.put(3,0, y1);
	rownania_y.put(4,0, sigma*v1*sin(th1));
	rownania_y.put(5,0, sigma*v1*cos(th1));

	inv_W = W.getInverse();


	cx = inv_W*rownania_x;
	cy = inv_W*rownania_y;

	params.push_back(cx.get(0,0));
	params.push_back(cx.get(1,0));
	params.push_back(cx.get(2,0));
	params.push_back(cx.get(3,0));
	params.push_back(cx.get(4,0));
	params.push_back(cx.get(5,0));

	params.push_back(cy.get(0,0));
	params.push_back(cy.get(1,0));
	params.push_back(cy.get(2,0));
	params.push_back(cy.get(3,0));
	params.push_back(cy.get(4,0));
	params.push_back(cy.get(5,0));

	return params;
}

float oblicz_dlugosc(vector<float> params, float t)
{
	float l, dl, ds, s, dx, dy;
	Matrix<float> Q_prim(1,6);
	Matrix<float> cx(6,1);
	Matrix<float> cy(6,1);
	Matrix<float> dx_m(1,1);
	Matrix<float> dy_m(1,1);

	cx.put(0,0, params[0]);
	cx.put(1,0, params[1]);
	cx.put(2,0, params[2]);
	cx.put(3,0, params[3]);
	cx.put(4,0, params[4]);
	cx.put(5,0, params[5]);

	cy.put(0,0, params[6]);
	cy.put(1,0, params[7]);
	cy.put(2,0, params[8]);
	cy.put(3,0, params[9]);
	cy.put(4,0, params[10]);
	cy.put(5,0, params[11]);

	ds = t*50;
	l = 0;
	dl = 0;

	for(int i = 0; i <= ds; i++)
	{
		s = i/ds;

		Q_prim.put(0,0, 5*pow(s,4));
		Q_prim.put(0,1, 4*pow(s,3));
		Q_prim.put(0,2, 3*pow(s,2));
		Q_prim.put(0,3, 2*s);
		Q_prim.put(0,4, 1);
		Q_prim.put(0,5, 0);

		dx_m = Q_prim*cx;
		dy_m = Q_prim*cy;
		dx = dx_m.get(0,0);
		dy = dy_m.get(0,0);

		dl = sqrt(pow(dx,2) + pow(dy,2));
		l = l + dl*(1/ds);
	}

	return l;

}

float max_krzywizna(vector<float> params, float t)
{
	float ds, s;
	float kappa_max;
	Matrix<float> Q_prim(1,6);
	Matrix<float> Q_bis(1,6);
	Matrix<float> cx(6,1);
	Matrix<float> cy(6,1);
	Matrix<float> x_prim_m(1,1);
	Matrix<float> y_prim_m(1,1);
	Matrix<float> x_bis_m(1,1);
	Matrix<float> y_bis_m(1,1);
	vector<float> kappa;
	float x_prim, y_prim, x_bis, y_bis;

	ds = t*50;


	cx.put(0,0, params[0]);
	cx.put(1,0, params[1]);
	cx.put(2,0, params[2]);
	cx.put(3,0, params[3]);
	cx.put(4,0, params[4]);
	cx.put(5,0, params[5]);

	cy.put(0,0, params[6]);
	cy.put(1,0, params[7]);
	cy.put(2,0, params[8]);
	cy.put(3,0, params[9]);
	cy.put(4,0, params[10]);
	cy.put(5,0, params[11]);

	for(int i = 0; i <= ds; i++)
	{
		s = i/ds;

		Q_prim.put(0,0, 5*pow(s,4));
		Q_prim.put(0,1, 4*pow(s,3));
		Q_prim.put(0,2, 3*pow(s,2));
		Q_prim.put(0,3, 2*s);
		Q_prim.put(0,4, 1);
		Q_prim.put(0,5, 0);

		Q_bis.put(0,0, 20*pow(s,3));
		Q_bis.put(0,1, 12*pow(s,2));
		Q_bis.put(0,2, 6*s);
		Q_bis.put(0,3, 2);
		Q_bis.put(0,4, 0);
		Q_bis.put(0,5, 0);

		x_prim_m = Q_prim*cx;
		y_prim_m = Q_prim*cy;
		x_bis_m = Q_bis*cx;
		y_bis_m = Q_bis*cy;

		x_prim = x_prim_m.get(0,0);
		y_prim = y_prim_m.get(0,0);
		x_bis = x_bis_m.get(0,0);
		y_bis = y_bis_m.get(0,0);

		kappa.push_back(abs((x_prim*y_bis - y_prim*x_bis)/pow(sqrt(pow(x_prim,2) + pow(y_prim,2)),3)));

	}

	kappa_max = *max_element(kappa.begin(), kappa.end());

	return kappa_max;

}


vector<float> odleglosc_od_przeszkody(vector<float> params, float x0, float y0, float r, float t)
{
	Matrix<float> Q(1,6);
	Matrix<float> cx(6,1);
	Matrix<float> cy(6,1);
	Matrix<float> x_m(1,1);
	Matrix<float> y_m(1,1);
	vector<float> d;
	float ds, x, y, d_min, s;

	ds = t*50;

	cx.put(0,0, params[0]);
	cx.put(1,0, params[1]);
	cx.put(2,0, params[2]);
	cx.put(3,0, params[3]);
	cx.put(4,0, params[4]);
	cx.put(5,0, params[5]);

	cy.put(0,0, params[6]);
	cy.put(1,0, params[7]);
	cy.put(2,0, params[8]);
	cy.put(3,0, params[9]);
	cy.put(4,0, params[10]);
	cy.put(5,0, params[11]);

	for(int i = 0; i <= ds; i++)
	{
		s = i/ds;

		Q.put(0,0, pow(s,5));
		Q.put(0,1, pow(s,4));
		Q.put(0,2, pow(s,3));
		Q.put(0,3, pow(s,2));
		Q.put(0,4, s);
		Q.put(0,5, 1);

		x_m = Q*cx;
		y_m = Q*cy;
		x = x_m.get(0,0);
		y = y_m.get(0,0);

		d.push_back(pow(x-x0,2) + pow(y-y0,2) - pow(r,2));

	}

	return d;
}

int sprawdzenie_wielomianu(vector<float> params, vector<float> prz_x, vector<float> prz_y, vector<float> r, float t)
{
	Matrix<float> Q(1,6);
	Matrix<float> cx(6,1);
	Matrix<float> cy(6,1);
	Matrix<float> x_m(1,1);
	Matrix<float> y_m(1,1);
	float ds, x, y, x0, y0, r0, s, j;

	ds = t*50;

	cx.put(0,0, params[0]);
	cx.put(1,0, params[1]);
	cx.put(2,0, params[2]);
	cx.put(3,0, params[3]);
	cx.put(4,0, params[4]);
	cx.put(5,0, params[5]);

	cy.put(0,0, params[6]);
	cy.put(1,0, params[7]);
	cy.put(2,0, params[8]);
	cy.put(3,0, params[9]);
	cy.put(4,0, params[10]);
	cy.put(5,0, params[11]);


	for(int i = 0; i <= ds; i++)
	{
		s = i/ds;

		Q.put(0,0, pow(s,5));
		Q.put(0,1, pow(s,4));
		Q.put(0,2, pow(s,3));
		Q.put(0,3, pow(s,2));
		Q.put(0,4, s);
		Q.put(0,5, 1);

		x_m = Q*cx;
		y_m = Q*cy;
		x = x_m.get(0,0);
		y = y_m.get(0,0);


		for(int ii = 0; ii <= r.size()-1; ii++)
		{
			x0 = prz_x[ii];
			y0 = prz_y[ii];
			r0 = r[ii];

			if(pow(x-x0,2) + pow(y-y0,2) < pow(r0+0.5,2) && r0 >= 0.05)
			{
				j = 0;
				break;
			}

			else
			{
				j = 1;
			}
		}

		if(j == 0)
		{
			break;
		}

	}

	return j;
}

int sprawdzenie_wielomianu2(vector<float> params, vector<float> prz_x, vector<float> prz_y, vector<float> r, float t, float odl)
{
	Matrix<float> Q(1,6);
	Matrix<float> cx(6,1);
	Matrix<float> cy(6,1);
	Matrix<float> x_m(1,1);
	Matrix<float> y_m(1,1);
	float ds, x, y, x0, y0, r0, s, j;

	ds = t*50;

	cx.put(0,0, params[0]);
	cx.put(1,0, params[1]);
	cx.put(2,0, params[2]);
	cx.put(3,0, params[3]);
	cx.put(4,0, params[4]);
	cx.put(5,0, params[5]);

	cy.put(0,0, params[6]);
	cy.put(1,0, params[7]);
	cy.put(2,0, params[8]);
	cy.put(3,0, params[9]);
	cy.put(4,0, params[10]);
	cy.put(5,0, params[11]);


	for(int i = 0; i <= ds; i++)
	{
		s = i/ds;

		Q.put(0,0, pow(s,5));
		Q.put(0,1, pow(s,4));
		Q.put(0,2, pow(s,3));
		Q.put(0,3, pow(s,2));
		Q.put(0,4, s);
		Q.put(0,5, 1);

		x_m = Q*cx;
		y_m = Q*cy;
		x = x_m.get(0,0);
		y = y_m.get(0,0);


		for(int ii = 0; ii <= r.size()-1; ii++)
		{
			x0 = prz_x[ii];
			y0 = prz_y[ii];
			r0 = r[ii];

			if(pow(x-x0,2) + pow(y-y0,2) < pow(r0+odl-0.02,2) && r0 >= 0.05)
			{
				j = 0;
				break;
			}

			else
			{
				j = 1;
			}
		}

		if(j == 0)
		{
			break;
		}

	}

	return j;
}


void punkty_zapis(vector<float> params, float t)
{
	Matrix<float> Q(1,6);
	Matrix<float> Q_prim(1,6);
	Matrix<float> Q_bis(1,6);
	Matrix<float> cx1(6,1);
	Matrix<float> cy1(6,1);
	Matrix<float> cx2(6,1);
	Matrix<float> cy2(6,1);
	Matrix<float> x_m(1,1);
	Matrix<float> y_m(1,1);
	Matrix<float> x_prim_m(1,1);
	Matrix<float> y_prim_m(1,1);
	Matrix<float> x_bis_m(1,1);
	Matrix<float> y_bis_m(1,1);
	vector<float> pkt;
	float s, ds, x, y, x_prim, y_prim, x_bis, y_bis;

	ds = t*50;

	cx1.put(0,0, params[0]);
	cx1.put(1,0, params[1]);
	cx1.put(2,0, params[2]);
	cx1.put(3,0, params[3]);
	cx1.put(4,0, params[4]);
	cx1.put(5,0, params[5]);

	cy1.put(0,0, params[6]);
	cy1.put(1,0, params[7]);
	cy1.put(2,0, params[8]);
	cy1.put(3,0, params[9]);
	cy1.put(4,0, params[10]);
	cy1.put(5,0, params[11]);

	ofstream file_sciezka;
	file_sciezka.open(sciezka_path(), ios_base::out | ios_base::app); // append instead of overwrite

	for(int i = 0; i <= ds; i++)
	{
		s = i/ds;

		Q.put(0,0, pow(s,5));
		Q.put(0,1, pow(s,4));
		Q.put(0,2, pow(s,3));
		Q.put(0,3, pow(s,2));
		Q.put(0,4, s);
		Q.put(0,5, 1);

		Q_prim.put(0,0, 5*pow(s,4));
		Q_prim.put(0,1, 4*pow(s,3));
		Q_prim.put(0,2, 3*pow(s,2));
		Q_prim.put(0,3, 2*s);
		Q_prim.put(0,4, 1);
		Q_prim.put(0,5, 0);

		Q_bis.put(0,0, 20*pow(s,3));
		Q_bis.put(0,1, 12*pow(s,2));
		Q_bis.put(0,2, 6*s);
		Q_bis.put(0,3, 2);
		Q_bis.put(0,4, 0);
		Q_bis.put(0,5, 0);

		x_m = Q*cx1;
		y_m = Q*cy1;
		x_prim_m = Q_prim*cx1;
		y_prim_m = Q_prim*cy1;
		x_bis_m = Q_bis*cx1;
		y_bis_m = Q_bis*cy1;

		x = x_m.get(0,0);
		y = y_m.get(0,0);
		x_prim = x_prim_m.get(0,0)/t;
		y_prim = y_prim_m.get(0,0)/t;
		x_bis = x_bis_m.get(0,0)/pow(t,2);
		y_bis = y_bis_m.get(0,0)/pow(t,2);

		file_sciezka<<x;
		file_sciezka<<"	";
		file_sciezka<<y;
		file_sciezka<<"	";
		file_sciezka<<x_prim;
		file_sciezka<<"	";
		file_sciezka<<y_prim;
		file_sciezka<<"	";
		file_sciezka<<x_bis;
		file_sciezka<<" ";
		file_sciezka<<y_bis;
		file_sciezka<<"	";
		file_sciezka<<s<<endl;

	}



	file_sciezka.close();

	ifstream inFile(sciezka_path());
  ofstream outFile(sciezka_copy_path());

  outFile << inFile.rdbuf();

}

vector<float> punkty(vector<float> params, float t)
{
	Matrix<float> Q(1,6);
	Matrix<float> Q_prim(1,6);
	Matrix<float> Q_bis(1,6);
	Matrix<float> cx(6,1);
	Matrix<float> cy(6,1);
	Matrix<float> x_m(1,1);
	Matrix<float> y_m(1,1);
	Matrix<float> x_prim_m(1,1);
	Matrix<float> y_prim_m(1,1);
	Matrix<float> x_bis_m(1,1);
	Matrix<float> y_bis_m(1,1);
	vector<float> pkt;
	float s, ds, x, y, x_prim, y_prim, x_bis, y_bis;

	ds = t*50;

	cx.put(0,0, params[0]);
	cx.put(1,0, params[1]);
	cx.put(2,0, params[2]);
	cx.put(3,0, params[3]);
	cx.put(4,0, params[4]);
	cx.put(5,0, params[5]);

	cy.put(0,0, params[6]);
	cy.put(1,0, params[7]);
	cy.put(2,0, params[8]);
	cy.put(3,0, params[9]);
	cy.put(4,0, params[10]);
	cy.put(5,0, params[11]);


	for(int i = 0; i <= ds; i++)
	{
		s = i/ds;

		Q.put(0,0, pow(s,5));
		Q.put(0,1, pow(s,4));
		Q.put(0,2, pow(s,3));
		Q.put(0,3, pow(s,2));
		Q.put(0,4, s);
		Q.put(0,5, 1);

		Q_prim.put(0,0, 5*pow(s,4));
		Q_prim.put(0,1, 4*pow(s,3));
		Q_prim.put(0,2, 3*pow(s,2));
		Q_prim.put(0,3, 2*s);
		Q_prim.put(0,4, 1);
		Q_prim.put(0,5, 0);

		Q_bis.put(0,0, 20*pow(s,3));
		Q_bis.put(0,1, 12*pow(s,2));
		Q_bis.put(0,2, 6*s);
		Q_bis.put(0,3, 2);
		Q_bis.put(0,4, 0);
		Q_bis.put(0,5, 0);

		x_m = Q*cx;
		y_m = Q*cy;
		x_prim_m = Q_prim*cx;
		y_prim_m = Q_prim*cy;
		x_bis_m = Q_bis*cx;
		y_bis_m = Q_bis*cy;

		x = x_m.get(0,0);
		y = y_m.get(0,0);
		x_prim = x_prim_m.get(0,0);
		y_prim = y_prim_m.get(0,0);
		x_bis = x_bis_m.get(0,0);
		y_bis = y_bis_m.get(0,0);

		pkt.push_back(x);
		pkt.push_back(y);
		pkt.push_back(x_prim);
		pkt.push_back(y_prim);
		pkt.push_back(x_bis);
		pkt.push_back(y_bis);

	}

	return pkt;

}
