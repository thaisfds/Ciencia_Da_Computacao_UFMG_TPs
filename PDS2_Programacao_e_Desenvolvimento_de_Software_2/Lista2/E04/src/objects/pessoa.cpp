#include "pessoa.hpp"
void Pessoa::print(ostream& out){
    out << "(nome = " << this->nome << ", idade = " << this->idade << ", CPF = " << this->cpf << ")";
}

void Pessoa::GetCampos(vector<string>& out){
    out = {"nome","idade","cpf"};
}

void Pessoa::setAtributo(string key, string valor){
    if(key == "nome"){
        this->nome = valor;
    }else if(key == "idade"){
        this->idade = stoi(valor);

    }else if(key == "cpf"){
        this->cpf = stoul(valor);
    }
}

string Pessoa::GetAtributo(string key){
    string valor;
    if(key == "nome"){
        valor = this->nome;
    }else if(key == "idade"){
        valor = to_string(this->idade);

    }else if(key == "cpf"){
        valor = to_string(this->cpf);
    }
    return valor;
}

bool Pessoa::operator==(Pessoa& rhs){
    bool valor = false;
    if(this->cpf == rhs.cpf){
        valor = true;
    }
    return valor;
}