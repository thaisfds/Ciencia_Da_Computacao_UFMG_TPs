#ifndef FilaAtendimento_H
#define FilaAtendimento_H

#include "Cliente.hpp"
#include <stdio.h>

// using namespace std;
struct Node{
    Cliente* cliente;
    Node* next;
};

struct FilaAtendimento{
    Node* head = nullptr;
    Node* tail = nullptr;

    int senhaAtual = 1;

    void adicionar_cliente(std::string nome, int idade);
    Cliente* chamar_cliente();
    void estimativa_tempo_espera(int senha);
    void imprimir_fila();
};
#endif