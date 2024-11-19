#ifndef TREINADOR_H
#define TREINADOR_H

#include "evolutionBall.hpp"
#include "healthBall.hpp"
#include "pokemonCapturado.hpp"
#include <vector>
using std::vector;

class Treinador{
    private:
        string nome;
        vector<EvolutionBall*> evolution_balls;
        vector<HealthBall*> health_balls;

    public:
       Treinador(string nome);
       ~Treinador();
       HealthBall* selecionarHealthBall(int id);
       EvolutionBall* selecionarEvolBall(int id);
       void adicionarPokebola(HealthBall* pokebola);
       void adicionarPokebola(EvolutionBall* pokebola);
       void listarPokemons();

};

#endif