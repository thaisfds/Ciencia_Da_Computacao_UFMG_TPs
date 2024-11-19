#include "Animal.hpp"


Animal::Animal(string nome, string familia, int idade){
    this->nome = nome;
    this->familia = familia;
    this->idade = idade;
    this->alimentacao = Alimentacao(0, 0, "");
    this->quantidadeConsumida = 0;

} 
        
string Animal::getNome(){
    return this->nome; 
}

string Animal::getFamilia(){
    return this->familia; 
}

int Animal::getIdade(){
    return this->idade; 
}

float Animal::getQuantidadeConsumida(){ 
    return this->quantidadeConsumida; 
}

string Animal::getDescricao(){
    return this->alimentacao.getDescricao();
}

void Animal::setQuantidadeConsumida(float quantidadeConsumida){
    this->quantidadeConsumida = quantidadeConsumida;
}

float Animal::calcularQuantidadeConsumida(){
    return this->alimentacao.getQuantPorcao() * this->alimentacao.getPesoPorcao();
}

void Animal::print(){
    cout << "[Animal]\n" << "  Nome: " << this->nome << "\n  Idade: " << this->idade << "\n  Familia: " << this->familia << "\n" << endl;
}

void Animal::setTipoDescricao(string tipoComida, string descricao){
    this->alimentacao.setTipoComida(tipoComida);
    this->alimentacao.setDescricao(descricao);
}

void Animal::setPorcaoQuantidadePorcao(float quantidadePorcao, float pesoPorcao){
    this->alimentacao.setQuantPorcao(quantidadePorcao);
    this->alimentacao.setPesoPorcao(pesoPorcao);
}