#ifndef HERPESTIDAE_HPP
#define HERPESTIDAE_HPP

#include "Animal.hpp"

class Herpestidae : public Animal {

    private:
        string especie;

    public:
        //construtores
        Herpestidae();
        Herpestidae(string nome, string especie, int idade);

        //funcoes
        virtual void print() override;
};

#endif
