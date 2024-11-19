#include "Herpestidae.hpp"

Herpestidae::Herpestidae(string nome, string especie, int idade){
    this->nome = nome;
    this->familia = "Herpestidae";
    this->idade = idade;
    this->especie = especie;
    this->alimentacao = Alimentacao(0, 0, "");
}
        
void Herpestidae::print(){
    cout << "[Animal]\n" << "  Nome: " << this->nome << "\n  Idade: " << this->idade << "\n  Familia: " << this->familia << endl;
    cout << "  Especie: " << this->especie <<endl;
}