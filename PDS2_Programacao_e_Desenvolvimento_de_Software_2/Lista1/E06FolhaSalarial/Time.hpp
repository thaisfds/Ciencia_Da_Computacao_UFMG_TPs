#ifndef Time_H
#define Time_H

#include"Jogador.hpp"
#include"list"

//using namespace std;

struct jogadorComparator{
    bool operator()(const Jogador & jogador1, const Jogador & jogador2){
        if(jogador1.salario == jogador2.salario)
            return jogador1.salario > jogador2.salario;
        return jogador1.salario > jogador2.salario;
    }
};

struct Time{
    std::string nome;
    std::list<Jogador> jogadores;
    Time() = default;
    Time(std::string nome); 
    void adicionar_jogador(std::string nome, std::string posicao, int salario); 
    void imprimir_lista_jogadores(); 
    void imprimir_folha_salarial_consolidada();
};


#endif