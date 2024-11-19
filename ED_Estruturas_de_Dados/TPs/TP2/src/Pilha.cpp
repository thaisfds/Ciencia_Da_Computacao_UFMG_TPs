#include "Pilha.h"

Pilha::Pilha(){
    topo = nullptr;
    tamanho = 0;
}

void Pilha::Empilha(Item part){
    Node *nova = new Node(part, topo);
    topo = nova;
    tamanho++;
}

Item Pilha::Desempilha(){
    Item aux; 
    Node *n;

    aux = topo->part;
    n = topo;
    topo = topo->prox;
    delete n;
    tamanho--;
    
    return aux;
}

void Pilha::Limpa(){
    while(!Vazia())
        Desempilha();
}

int Pilha::getTamanho(){
    return tamanho;
}

bool Pilha::Vazia(){
    return (tamanho == 0);
}
