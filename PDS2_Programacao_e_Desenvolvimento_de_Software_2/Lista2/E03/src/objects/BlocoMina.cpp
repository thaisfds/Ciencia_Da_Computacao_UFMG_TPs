#include "BlocoMina.hpp"

BlocoMina::BlocoMina(vector<vector<Bloco*>>& tabuleiro, Coordenada coord): Bloco(coord){
    this->valor = -1;

    int Boundary = tabuleiro.size();
    vector<Coordenada> adjacentes;
    this->coord.getCoordenadasAdjacentes(adjacentes, Boundary, Boundary);

    
    for(Coordenada a : adjacentes){

        if(tabuleiro[a.getRow()][a.getCol()]->getValor() == -1)
            continue;

        if(tabuleiro[a.getRow()][a.getCol()]->getValor() == 0){
            Coordenada c = Coordenada(a.getRow(), a.getCol());
            delete tabuleiro[a.getRow()][a.getCol()];
            tabuleiro[c.getRow()][c.getCol()] =  new BlocoContador(c);

        }

        BlocoContador* bc = dynamic_cast<BlocoContador*>(tabuleiro[a.getRow()][a.getCol()]);
        bc->incrementarValor();


    }
}

BlocoMina::~BlocoMina(){

}

bool BlocoMina::revelar(vector<vector<Bloco*>>& tabuleiro){

    for(auto linha : tabuleiro)
        for(auto bloco : linha)
            if(bloco->ehRevelado() == false){
                this->revelado = true;
                bloco->revelar(tabuleiro);
            }

    return false;
}