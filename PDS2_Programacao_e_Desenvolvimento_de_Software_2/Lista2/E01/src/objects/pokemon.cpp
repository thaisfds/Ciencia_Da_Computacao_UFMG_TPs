#include "pokemon.hpp"

Pokemon::Pokemon(string nome, string tipo, string pEvol, double fA, double fD, double saude){
    this->nome = nome;
    this->tipo = tipo;
    this->proxEvolucao = pEvol;
    this->forcaAtaque = fA;
    this->forcaDefesa = fD;
    this->saude = saude;
}

void Pokemon::maxSaude(){
    this->saude = 100;
}

void Pokemon::info(){
    cout << "Pokemon: " << this->nome << ", " << this->tipo << ", " << this->forcaAtaque << ", " << this->forcaDefesa << ", " << this->saude << endl;
}

string Pokemon::getNome(){
    return this->nome;
}

