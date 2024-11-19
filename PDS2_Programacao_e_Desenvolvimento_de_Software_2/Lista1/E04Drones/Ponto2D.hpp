#ifndef Ponto2D_H
#define Ponto2D_H

#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include<cmath>

using namespace std;

struct Ponto2D{
    double x, y;
    Ponto2D();
    Ponto2D(double, double);
    double calcular_distancia(Ponto2D* ponto);
    string get_dados();
};


#endif