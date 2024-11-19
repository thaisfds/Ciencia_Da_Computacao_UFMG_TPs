#ifndef COORDENADA_H
#define COORDENADA_H

#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class Coordenada{
    private:
        int row,col;
    
    public:
        Coordenada();
        Coordenada(int row, int col);
        void getCoordenadasAdjacentes(vector<Coordenada>& adjacentes, int rowBoundary, int colBoundary);
        int getRow();
        int getCol();
};

#endif