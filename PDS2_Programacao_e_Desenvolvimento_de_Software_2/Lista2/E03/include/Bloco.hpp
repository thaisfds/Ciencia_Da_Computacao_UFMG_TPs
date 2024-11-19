#ifndef BLOCO_H
#define BLOCO_H

#include "Coordenada.hpp"
#include <sstream>
#include <iostream>
#include <string>

class Bloco{
    protected:
        Coordenada coord;
        bool revelado;
        int valor;
    
    public:
        Bloco(Coordenada coord);
        virtual ~Bloco();
        virtual bool revelar(vector<vector<Bloco*>>& tabuleiro);
        string getSimbolo();
        bool ehRevelado();
        int getValor();
};

#endif