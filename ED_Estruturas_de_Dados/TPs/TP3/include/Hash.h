#ifndef HASH_H
#define HASH_H

#include "ArvoreAVL.h"

class Hash : public Dicionario{
    private:
        static const int M = 52;
        //Tabela de verbetes utilizada pelo hash
        //Armazena os verbetes de acordo com a primeira letra da palavra
        Lista<Verbete*> Tabela[M];

        //Funcao hash
        int FuncHash(std::string palavra);

    public:
        Hash(); //Contrutor do hash
        ~Hash(); //Destrutor do hash
        Verbete* Pesquisa(char tipo, std::string palavra); //Pesquisa uma palavra no hash
        void Insere(Verbete *verb); //Insere uma palvra no hash
        void RemoveComSignificado();
        void Remove(char tipo, std::string palavra); //Remove uma palvra do hash
        void Imprimir(); //Imprime as palavras do hash
        void Limpar(); //Limpa o hash no destrutor
};

#endif