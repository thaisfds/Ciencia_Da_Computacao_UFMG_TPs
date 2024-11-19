#include"Time.hpp"

Time::Time(std::string nome){
    this->nome = nome;
}

void Time::adicionar_jogador(std::string nome, std::string posicao, int salario){
    Jogador* auxiliar = new Jogador(nome, posicao, salario);  
    jogadores.push_back(*auxiliar);
}

void Time::imprimir_lista_jogadores(){
    std::list<Jogador>::iterator k;
    std::list<Jogador>::iterator l;

    std::cout << this->nome << std::endl;

    jogadores.sort(jogadorComparator());

    for(k = jogadores.begin(); k != jogadores.end(); k++){
        (*k).imprimir_dados();
    }
}

void Time::imprimir_folha_salarial_consolidada(){
    std::list<Jogador>::iterator k;
    int folha_salarial_consolidade = 0;
    for(k = jogadores.begin(); k != jogadores.end(); k++){
        folha_salarial_consolidade += (*k).salario;
    }
    std::cout << nome << "\t" << folha_salarial_consolidade << std::endl;
}
