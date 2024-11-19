#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "Alimentacao.hpp"

using namespace std;

class Animal {
    protected:
        string nome, familia;
        int idade;
        float quantidadeConsumida;
        Alimentacao alimentacao;

    public:
        //construtores
        Animal(string nome, string familia, int idade); 
        Animal() = default;

        //gets
        string getNome();
        string getFamilia();
        int getIdade();
        float getQuantidadeConsumida();
        string getDescricao();

        //sets
        void setQuantidadeConsumida(float quantidadeConsumida);
        void setTipoDescricao(string tipoComida, string descricao);
        void setPorcaoQuantidadePorcao(float quantidadePorcao, float pesoPorcao);

        //funcoes
        float calcularQuantidadeConsumida(); //calcula a quantidade de comida consumida com base na quantidadePorcao e pesoPorcao
        virtual void print();
};

#endif
