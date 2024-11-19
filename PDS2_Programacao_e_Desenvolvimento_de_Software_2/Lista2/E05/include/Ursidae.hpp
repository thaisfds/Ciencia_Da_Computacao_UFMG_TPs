#ifndef URSIDAE_HPP
#define URSIDAE_HPP

#include "Animal.hpp"

class Ursidae : public Animal {

    private:
        string especie;

    public:
        //construtores
        Ursidae();
        Ursidae(string nome, string especie, int idade);

        //funcoes
        virtual void print() override;
};

#endif

