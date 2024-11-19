#include "pokemonCapturado.hpp"
PokemonCapturado::PokemonCapturado(Pokemon& pok) : Pokemon(pok) {
    this->evoluido = false;
    this->dormindo = true;
}

void PokemonCapturado::evoluir(double taxaPoder){
    double taxa = 1 + taxaPoder;
    this->evoluido = true;
    this->nome = this->proxEvolucao;
    this->proxEvolucao = "vazia";
    this->forcaAtaque *= taxa;
    this->forcaDefesa *= taxa;
}

bool PokemonCapturado::getEvoluido(){
    return this->evoluido;
}

bool PokemonCapturado::getDormindo(){
    return this->dormindo;
}

void PokemonCapturado::setEvoluido(bool evoluido){
    this->evoluido = evoluido;
}

void PokemonCapturado::setDormindo(bool dormindo){
    this->dormindo = dormindo;
}