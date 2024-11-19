#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <iostream>
//#include <iomanip>

using std::cout;
using std::endl;
using std::string;

class Pokemon{
    protected:
        string nome;
        string tipo;
        double forcaAtaque;
        double forcaDefesa;
        string proxEvolucao;
        double saude;

    public:
        Pokemon(string nome, string tipo, string pEvol, double fA, double fD, double saude);
        void maxSaude();
        void info();

        //gets
        string getNome();

};

#endif