#include "Ursidae.hpp"

Ursidae::Ursidae(string nome, string especie, int idade){
    this->nome = nome;
    this->familia = "Ursidae";
    this->idade = idade;
    this->especie = especie;
    this->alimentacao = Alimentacao(0, 0, "");
}


void Ursidae::print() {
    cout << "[Animal]\n" << "  Nome: " << this->nome << "\n  Idade: " << this->idade << "\n  Família: " << this->familia << endl;
    cout << "  Especie: " << this->especie << "\n" <<endl;
}