#include "RegistroNBA.hpp"
void RegistroNBA::adicionar_time(std::string nome){
    Time* auxiliar = new Time(nome); 
    registro.insert(std::pair<std::string, Time> (nome, *auxiliar));
    registro[nome].imprimir_lista_jogadores();
}

void RegistroNBA::adicionar_jogador(std::string nome_time, std::string nome_jogador, std::string posicao, int salario){
    if(registro.find(nome_time) != registro.end()){
        registro[nome_time].adicionar_jogador(nome_jogador, posicao, salario);
    }else{
        Time auxiliar = Time(nome_time); 
        registro.insert(std::pair <std::string,Time> (nome_time, auxiliar));
        registro[nome_time].adicionar_jogador(nome_jogador, posicao, salario);
    }
}

void RegistroNBA::imprimir_lista_jogadores_time(std::string nome_time){
    registro[nome_time].imprimir_lista_jogadores();
}

void RegistroNBA::imprimir_folha_consolidada_time(std::string nome_time){
    registro[nome_time].imprimir_folha_salarial_consolidada();
}

void RegistroNBA::imprimir_folha_salarial_geral(){
    std::map<std::string,Time>::iterator it;
    for(it = registro.begin(); it != registro.end(); it++){
        imprimir_folha_consolidada_time(it->second.nome);
    }
}