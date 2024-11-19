#include "Bloco.hpp"

Bloco::Bloco(Coordenada coord){
    this->coord = coord;
    this->revelado = false;
    this->valor = 0;
}

Bloco::~Bloco(){
    
}

bool Bloco::revelar(vector<vector<Bloco*>>& tabuleiro){

    this->revelado = true;

    int Boundary = tabuleiro.size();
    vector<Coordenada> adjacentes;
    this->coord.getCoordenadasAdjacentes(adjacentes, Boundary, Boundary);

    for(Coordenada a : adjacentes){
        if(tabuleiro[a.getRow()][a.getCol()]->ehRevelado() == false){
            tabuleiro[a.getRow()][a.getCol()]->revelar(tabuleiro);
        }
    }

    return true;
}

string Bloco::getSimbolo(){
    if(this->revelado == false){
        return "#";
    }else if(this->valor == -1){
        return "*";
    }
    
    string str = std::to_string(this->valor);
    return str;
}

bool Bloco::ehRevelado(){
    return this->revelado;
}

int Bloco::getValor(){
    return this->valor;
}