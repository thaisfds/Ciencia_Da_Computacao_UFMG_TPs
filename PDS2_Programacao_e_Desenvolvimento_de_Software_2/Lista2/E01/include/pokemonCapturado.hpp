#ifndef POKEMONCAPTURADO_H
#define POKEMONCAPTURADO_H

#include "pokemon.hpp"

class PokemonCapturado : public Pokemon{
    private:
        bool evoluido;
        bool dormindo;

    public:
        PokemonCapturado(Pokemon& pok);
        void evoluir(double taxaPoder);

        //gets
        bool getEvoluido();
        bool getDormindo();

        //sets
        void setEvoluido(bool evoluido);
        void setDormindo(bool dormindo);

};

#endif