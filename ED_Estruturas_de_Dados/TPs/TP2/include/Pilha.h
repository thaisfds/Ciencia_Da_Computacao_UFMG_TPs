#ifndef PILHA_H
#define PILHA_H

#include <iostream>

//Pilha comum constuida com base nos slides apresentados em sala de aula
class Item{
   public:
    int esq, dir;
    Item() : esq(0), dir(0){};
    Item(int e, int d): esq(e), dir(d){};

    friend class Node;
};

class Node{
    private:
        Item part;
        Node *prox;

    public:
        Node(): prox(nullptr){};
        Node(Item reg, Node *n) : part(reg), prox(n){};
    
    friend class Pilha;
};

class Pilha{
    private:
        int tamanho;
        Node *topo;
        
    public:
        ~Pilha(){Limpa();};
        Pilha();

        void Empilha(Item part);
        Item Desempilha();
        void Limpa();

        int getTamanho();
        bool Vazia();
    friend class MetodosOrdenacao;
        
};
#endif