#ifndef BLOCOMINA_H
#define BLOCOMINA_H

#include "Bloco.hpp"
#include "BlocoContador.hpp"

class BlocoMina: public Bloco{
    public:
       BlocoMina(vector<vector<Bloco*>>& tabuleiro, Coordenada coord);
       virtual ~BlocoMina();
       virtual bool revelar(vector<vector<Bloco*>>& tabuleiro) override;
};

#endif