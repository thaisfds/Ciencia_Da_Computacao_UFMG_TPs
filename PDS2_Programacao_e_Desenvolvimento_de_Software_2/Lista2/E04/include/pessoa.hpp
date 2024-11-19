#ifndef PESSOA_H
#define PESSOA_H

#include "ireadable.hpp"
using std::stoi;
using std::stoul;
using std::to_string;

class Pessoa : public IReadable{
    private:
        string nome; //Nome da pessoa
        int idade; //dade da pessoa
        unsigned long cpf; //CPF da pessoa

    protected: 
        virtual void print(ostream& out) override;

    public: 
        virtual void GetCampos(vector<string>& out) override;
        virtual void setAtributo(string key, string valor) override;
        virtual string GetAtributo(string key) override;

        bool operator==(Pessoa& rhs);
};

#endif