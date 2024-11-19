#ifndef AVALIACAO_H
#define AVALIACAO_H

#include <iostream>
#include "RegistroNBA.hpp"

using namespace std;

void avaliacao_basica() {
    
    RegistroNBA registro;

    registro.adicionar_time("TimeA");
    registro.adicionar_time("TimeB");
    
    registro.imprimir_lista_jogadores_time("TimeA");
    registro.imprimir_lista_jogadores_time("TimeB");

    cout << "----------" << endl;
    
    registro.adicionar_jogador("TimeA", "JogadorA", "XY", 10);
    registro.adicionar_jogador("TimeA", "JogadorB", "XY", 100);
    
    registro.adicionar_jogador("TimeB", "JogadorC", "XY", 50);
    registro.adicionar_jogador("TimeB", "JogadorD", "XY", 50);

    registro.imprimir_lista_jogadores_time("TimeA");
    registro.imprimir_lista_jogadores_time("TimeB");

    cout << "----------" << endl;

    registro.imprimir_folha_consolidada_time("TimeA");
    registro.imprimir_folha_consolidada_time("TimeB");

    cout << "----------" << endl;

    registro.imprimir_folha_salarial_geral();
    
}

#endif