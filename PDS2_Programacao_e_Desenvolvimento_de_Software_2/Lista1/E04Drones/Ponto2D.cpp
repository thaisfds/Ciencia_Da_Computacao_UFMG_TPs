#include "Ponto2D.hpp"

Ponto2D::Ponto2D(){
    this->x = 0;
    this->y = 0;
}

Ponto2D::Ponto2D(double x, double y){
    this->x = x;
    this->y = y;
}

double Ponto2D::calcular_distancia(Ponto2D* ponto){
    double x = ponto->x - this->x;
    double y = ponto->y - this->y;
    return sqrt(x*x + y*y);
}

string Ponto2D::get_dados(){
    stringstream dados;
    dados << "[" << fixed << setprecision(2) << this->x << "," << fixed << setprecision(2) << this->y << "]";
    return dados.str();
}