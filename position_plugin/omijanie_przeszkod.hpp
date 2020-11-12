#ifndef omijanie_przeszkod_hpp
#define omijanie_przeszkod_hpp

#include <vector>

using namespace std;

vector<float> wspolczynniki_wielomianow(float x0, float y0, float th0, float x1, float y1, float th1, float x2, float y2, float th2, float v0, float v1, float v2, int sigma);
vector<float> wspolczynniki_wielomianow2(float x0, float y0, float th0, float x1, float y1, float th1, float v0, float v1, int sigma);;
float oblicz_dlugosc(vector<float> params, float t);
float max_krzywizna(vector<float> params, float t);
vector<float> odleglosc_od_przeszkody(vector<float> params, float x0, float y0, float r, float t);
int sprawdzenie_wielomianu(vector<float> params, vector<float> prz_x, vector<float> prz_y, vector<float> r, float t);
int sprawdzenie_wielomianu2(vector<float> params, vector<float> prz_x, vector<float> prz_y, vector<float> r, float t, float odl);
void punkty_zapis(vector<float> params, float t);
vector<float> punkty(vector<float> params, float t);

#endif
