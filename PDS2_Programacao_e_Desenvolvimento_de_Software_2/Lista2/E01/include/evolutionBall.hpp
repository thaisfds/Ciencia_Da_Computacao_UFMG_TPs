#ifndef EVOLUTIONBALL_H
#define EVOLUTIONBALL_H

#include "pokebola.hpp"
#include <stdlib.h>

class EvolutionBall : public Pokebola{
    private:
        double taxaPoder;
        bool habilidadeUsada;
    
    public:
        EvolutionBall(double taxaPoder);
        bool evoluirPokemon();

};

#endif