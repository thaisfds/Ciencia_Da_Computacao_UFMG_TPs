#ifndef HEALTHBALL_H
#define HEALTHBALL_H
#include "pokebola.hpp"
#include <ctime>

class HealthBall : public Pokebola{
    private:
        time_t ultimoUso;
        double intervalo;

    public:
        HealthBall(double intervalo);
        bool recuperarPokemon();
        
};

#endif