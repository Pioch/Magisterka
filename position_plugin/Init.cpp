#include <iostream>
#include <fstream>
#include <string.h>
#include "Init.hpp"


using namespace std;

float epsilon1()
{
	float eps1 = 0.25; //0.25 osemka
	
	return eps1;
}

float epsilon2()
{
	float eps2 = 0.3; //0.3 osemka
	
	return eps2;
}

float delta_t()
{
	float dT = 0.02;
	
	return dT;
}


float alpha_wielomian()
{
	float alpha_w = 0.05;
	
	return alpha_w;
}

const char *pomiary_path()
{
	const char *pomiary = "/home/piotr/Magisterka/position_plugin/pomiary.txt";
	
	return pomiary;
}

const char *sciezka_path()
{
	const char *sciezka = "/home/piotr/Magisterka/position_plugin/sciezka.txt";
	
	return sciezka;
}

const char *przeszkody_path()
{
	const char *przeszkody = "/home/piotr/Magisterka/position_plugin/przeszkody.txt";
	
	return przeszkody;
}

const char *punkty_path()
{
	const char *punkty = "/home/piotr/Magisterka/position_plugin/punkty.txt";
	
	return punkty;
}

const char *temp_path()
{
	const char *temp = "/home/piotr/Magisterka/position_plugin/temp.txt";
	
	return temp;
}

const char *okregi_przeszkody_path()
{
	const char *okregi_przeszkody = "/home/piotr/Magisterka/position_plugin/okregi_przeszkody.txt";
	
	return okregi_przeszkody;
}

const char *sciezka_copy_path()
{
	const char *sciezka_copy = "/home/piotr/Magisterka/position_plugin/sciezka_copy.txt";
	
	return sciezka_copy;
}



