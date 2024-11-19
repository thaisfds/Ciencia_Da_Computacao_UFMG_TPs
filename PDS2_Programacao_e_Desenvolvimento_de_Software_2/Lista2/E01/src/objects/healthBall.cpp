#include "healthBall.hpp"

HealthBall::HealthBall(double intervalo) : Pokebola(){
    this->intervalo = intervalo;
}

bool HealthBall::recuperarPokemon(){
    if(this->pokemon == nullptr || difftime(time(NULL),this->ultimoUso) <= this->intervalo){
        return(false);
    }

    this->pokemon->maxSaude();
    this->ultimoUso = time(NULL);
    return true;
}