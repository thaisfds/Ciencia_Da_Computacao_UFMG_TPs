#ifndef FABRICA_HPP
#define FABRICA_HPP

#include <iostream>
#include <limits>
#define INF 0x3f3f3f3f
using namespace std;

class Fabrica{
    public:
        Fabrica(); //Construtor
        int otimizacaoLigasMetalicas(int *ligasMetalicas, int N, int W); //Função que retorna o menor número de ligas metálicas para atingir o peso W
};

#endif