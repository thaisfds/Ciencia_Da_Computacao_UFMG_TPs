#ifndef DICIONARIO_H
#define DICIONARIO_H

#include "Verbete.h"

//Classe abstrada Dicionário
class Dicionario{
    public:
        virtual ~Dicionario(){};
        virtual void Insere(Verbete *verb) = 0; //Insere um verbete no dicionario
        virtual void Remove(char tipo, std::string palavra) = 0; //Remove um verbete do dicionario
        virtual void RemoveComSignificado() = 0;
        virtual void Imprimir() = 0; //Imprime o tudo que tem no dicionario
        virtual void Limpar() = 0; //Limapa o dicionario
};

#endif