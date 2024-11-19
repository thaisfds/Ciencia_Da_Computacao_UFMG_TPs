#ifndef CAIXADEENTRADA_H
#define CAIXADEENTRADA_H

#include "Email.h"
#include "Lista.h"

class CaixaDeEntrada{
    private:
        int tamanho;
        int ID;
        Lista<Email*> caixaEmail;

    public:

        CaixaDeEntrada(int ID);
        ~CaixaDeEntrada();

        int getTamanho();
        void adicionarEmail(std::string mensagem, int prioridade);
        void imprimirEmail();
        std::string deletarEmail();
        int getID();
};
#endif