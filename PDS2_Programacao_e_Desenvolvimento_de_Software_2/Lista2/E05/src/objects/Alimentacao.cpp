#include "Alimentacao.hpp"
Alimentacao::Alimentacao(float quantidadePorcao, float pesoPorcao, string tipoComida){
    this->quantidadePorcao = quantidadePorcao;
    this->pesoPorcao = pesoPorcao;
    this->tipoComida = tipoComida;
    this->descricao = "";
}

void Alimentacao::setQuantPorcao(float quantidadePorcao){
    this->quantidadePorcao = quantidadePorcao;
}

void Alimentacao::setPesoPorcao(float pesoPorcao){
    this->pesoPorcao = pesoPorcao;
}

void Alimentacao::setTipoComida(string tipoComida){
    this->tipoComida = tipoComida;
}

void Alimentacao::setDescricao(string descricao){
    this->descricao = descricao;
}

float Alimentacao::getQuantPorcao(){
    return this->quantidadePorcao;
}

float Alimentacao::getPesoPorcao(){
    return this->pesoPorcao;
}

string Alimentacao::getTipoComida(){
    return this->tipoComida;
}

string Alimentacao::getDescricao(){
    return this->descricao;
}
