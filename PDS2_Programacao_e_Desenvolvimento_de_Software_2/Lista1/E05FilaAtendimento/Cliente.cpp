#include "Cliente.hpp"

Cliente::Cliente(std::string nome, int idade, int senha){
    this->nome = nome;
    this->idade = idade;
    this->senha = senha;
}

bool Cliente::eh_prioritario(){
    if(this->idade >= 60){
        return true;
    }else{
        return false;
    }
}

int Cliente::tempo_estimado_atendimento(){
    if(eh_prioritario()){
        return 12;
    }else{
        return 8;
    }
}

void Cliente::imprimir_dados(){
    std::cout << this->senha << "\t" << this->nome << "\t" << this->idade << std::endl;
}