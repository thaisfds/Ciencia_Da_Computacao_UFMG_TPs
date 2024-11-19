#include "Jogador.hpp"

Jogador::Jogador(std::string nome, std::string posicao, int salario){
    this->nome = nome;
    this->posicao = posicao;
    this->salario = salario;
}
void Jogador::imprimir_dados(){
    std::cout << this->nome << "\t" << this->posicao << "\t" << this->salario << std::endl;
}