#ifndef AVALIACAO_H
#define AVALIACAO_H

#include <iostream>
#include "FilaAtendimento.hpp"

using namespace std;

void avaliacao_basica() {
    
    FilaAtendimento fila;

    fila.adicionar_cliente("Cliente1N", 58);
    fila.adicionar_cliente("Cliente2N", 25);
    fila.adicionar_cliente("Cliente3P", 61);
    fila.adicionar_cliente("Cliente4P", 60);
    fila.adicionar_cliente("Cliente5N", 33);
    fila.imprimir_fila();

    cout << "----------" << endl;

    fila.estimativa_tempo_espera(1);

    cout << "----------" << endl;

    Cliente *cliente = nullptr;

    cliente = fila.chamar_cliente();
    cliente->imprimir_dados();
    
    cliente = fila.chamar_cliente();
    cliente->imprimir_dados();    

    cout << "----------" << endl;

    fila.imprimir_fila();

    cout << "----------" << endl;

    fila.estimativa_tempo_espera(5);

    cout << "----------" << endl;

    fila.chamar_cliente();
    fila.chamar_cliente();
    fila.chamar_cliente();

    cliente = fila.chamar_cliente();
    if (cliente == nullptr) {
        cout << "CORRECT" << endl; 
    } else {
        cout << "ERROR"; 
    }

    cout << "----------" << endl;
}

#endif