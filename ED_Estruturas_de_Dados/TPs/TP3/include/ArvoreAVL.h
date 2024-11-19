#ifndef ARVOREAVL_H
#define ARVOREAVL_H

#include "Dicionario.h"

class NodeAVL{
    private: 
        Verbete *verb;
        NodeAVL *esq;
        NodeAVL *dir;

    public:
        NodeAVL();
        NodeAVL(Verbete *v);
        ~NodeAVL();
    friend class ArvoreAVL;
};


class ArvoreAVL : public Dicionario{
    private:
        NodeAVL *raiz;
        int FatorBalanceamento(NodeAVL *&no); //Pega o fator de balanceamaneto da arvore
        int Altura(NodeAVL *&no); //Pega a altura
        void RotacaoDireita(NodeAVL *&no); //Rotacao pra direita
        void RotacaoEsquerda(NodeAVL *&no); //Rotacao pra esquerda
        void RotacaoDDireita(NodeAVL *&no); //Rotacao dupla pra direita
        void RotacaoDEsquerda(NodeAVL *&no); //Rotacao dupla pra esquerda
        void Balancear();
        void BalancearRecursivo(NodeAVL *&no);
        Verbete* PesquisaRecursivo(char tipo, std::string palavra, NodeAVL *&no); //Pesquisa uma palavra na arvore
        void InsereRecursivo(Verbete *v, NodeAVL *&no);
        void RemoveRecursivo(char tipo, std::string palavra, NodeAVL *&no);
        void RemoveComSignificadoRecursivo(NodeAVL *&no);
        void LimparRecursivo(NodeAVL *&no);
        void ImprimirRecursivo(NodeAVL *&no);
        
    public:
        ArvoreAVL(); //Contrutor da Arvore
        ~ArvoreAVL(); //Destrutor da Arvore

        Verbete* Pesquisa(char tipo, std::string palavra); //Pesquisa uma palavra na arvore
        void Insere(Verbete *v); //Insere uma palvra na arvore
        void Remove(char tipo, std::string palavra); //Remove uma palvra da arvore
        void RemoveComSignificado();
        void Imprimir(); //Imprime as palavras da arvore
        void Limpar(); //Limpa a arvore no destrutor

};

#endif