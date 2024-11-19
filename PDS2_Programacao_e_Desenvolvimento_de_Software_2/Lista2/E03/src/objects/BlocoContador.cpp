#include "BlocoContador.hpp"

BlocoContador::BlocoContador(Coordenada coord) : Bloco(coord){
    this->valor = 0;
}

bool BlocoContador::revelar(vector<vector<Bloco*>>& tabuleiro){
    this->revelado = true;
    return true;
}

BlocoContador::~BlocoContador(){

}

void BlocoContador::incrementarValor(){
    this->valor++;
}