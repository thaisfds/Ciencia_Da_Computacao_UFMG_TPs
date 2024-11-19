#ifndef Jogador_H
#define Jogador_H

#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include<cmath>

//using namespace std;

struct Jogador{
    std::string nome, posicao;
    int salario;
    Jogador(std::string nome, std::string posicao, int salario); 
    void imprimir_dados();
};


#endif