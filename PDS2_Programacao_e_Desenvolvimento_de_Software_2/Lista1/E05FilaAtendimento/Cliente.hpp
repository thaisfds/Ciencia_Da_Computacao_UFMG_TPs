#ifndef Cliente_H
#define Cliente_H

#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include<cmath>

//using namespace std;

struct Cliente{
    int idade, senha;
    std::string nome;
    Cliente(std::string nome, int idade, int senha);
    bool eh_prioritario();
    int tempo_estimado_atendimento();
    void imprimir_dados();
};


#endif