#ifndef ALIMENTACAO_HPP
#define ALIMENTACAO_HPP

#include <string>
#include <iostream>
#include "Cuidador.hpp"

//padronizacao do uso de: string, cout, cin, endl
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Alimentacao{

    private:
        float quantidadePorcao, pesoPorcao;
        string tipoComida, descricao;

    public:
        //construtores
        Alimentacao(float quantidadePorcao, float pesoPorcao, string tipoComida);
        Alimentacao() = default;
        
        //sets
        void setQuantPorcao(float quantidadePorcao);
        void setPesoPorcao(float pesoPorcao);
        void setTipoComida(string tipoComida);
        void setDescricao(string descricao);

        //gets
        float getQuantPorcao();
        float getPesoPorcao();
        string getTipoComida();
        string getDescricao();
};

#endif