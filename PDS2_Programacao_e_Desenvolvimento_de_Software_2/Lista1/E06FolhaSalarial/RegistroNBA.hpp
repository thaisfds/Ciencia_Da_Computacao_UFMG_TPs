#ifndef RegistroNBA_H
#define RegistroNBA_H

#include <iterator>
#include <map>
#include "Time.hpp"

using std::map;

struct RegistroNBA{
    map<std::string, Time>registro;

    void adicionar_time(std::string nome); 
    void adicionar_jogador(std::string nome_time, std::string nome_jogador, std::string posicao, int salario);
    void imprimir_lista_jogadores_time(std::string nome_time); 
    void imprimir_folha_consolidada_time(std::string nome_time); 
    void imprimir_folha_salarial_geral();    
};


#endif