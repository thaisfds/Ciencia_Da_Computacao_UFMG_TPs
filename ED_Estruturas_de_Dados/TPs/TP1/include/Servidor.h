#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "CaixaDeEntrada.h"
#include<fstream>
#include <unistd.h>

class Servidor{
    private:
        Lista<CaixaDeEntrada*> usuarios;
        int tamanho;

    public:

        Servidor();
        ~Servidor();

        void gerenciarServidor(std::string nameFile);
        void adicionarUsuario(int ID);
        void removerUsuario(int ID);
        void enviarEmail(std::string MSG, int PRI, int ID);
        void lerEmail(int ID);
        int pesquisarPosicao(int ID);
        
};
#endif