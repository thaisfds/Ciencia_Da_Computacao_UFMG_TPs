#include "evolutionBall.hpp" 

EvolutionBall::EvolutionBall(double taxaPoder) : Pokebola(){
    this->taxaPoder = taxaPoder;
}

bool EvolutionBall::evoluirPokemon(){
    if(this->pokemon == nullptr || this->habilidadeUsada == true){
        return(false);
    }

    this->habilidadeUsada = true;
    this->pokemon->evoluir(taxaPoder);
    return true;
}