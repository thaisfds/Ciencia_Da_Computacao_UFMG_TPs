#include "Coordenada.hpp"

Coordenada::Coordenada(){
    this->row = 0;
    this->col = 0;
}

Coordenada::Coordenada(int row, int col){
    this->row = row;
    this->col = col;
}


void Coordenada::getCoordenadasAdjacentes(vector<Coordenada>& adjacentes, int rowBoundary, int colBoundary){
    if(this->row < rowBoundary && this->row >= 0 && this->col < colBoundary && this->col >= 0){
        for(int i = row-1 ; i <= row+1; i++){
            if(i>=0 && i<rowBoundary){
                for(int j = col-1 ; j<= col+1 ; j++){
                    if(j>=0 && j<rowBoundary && (i != this->row || j != this->col)){
                        Coordenada aux = Coordenada(i,j);
                        adjacentes.push_back(aux);
                    }
                }
            }
        }
    }
}

int Coordenada::getRow(){
    return this->row;
}
int Coordenada::getCol(){
    return this->col;
}


