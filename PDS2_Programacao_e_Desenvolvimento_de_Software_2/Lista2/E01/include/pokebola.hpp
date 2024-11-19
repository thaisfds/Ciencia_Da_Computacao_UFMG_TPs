#ifndef POKEBOLA_H
#define POKEBOLA_H
#include "pokemonCapturado.hpp"
#include <cstdlib>


class Pokebola{
    private:
        static int count;

    protected:
        int id;
        PokemonCapturado* pokemon;

    public:
        Pokebola();
        ~Pokebola();
        int getCount();
        int getId();
        PokemonCapturado* getPokemonCap();
        void setId();
        void guardarPokemon();
        Pokemon* liberarPokemon();
        bool capturar(Pokemon& pokemon);

};

#endif