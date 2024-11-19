#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
#include "graph.hpp"

class Dijkstra{
    private:
        Graph G;
    public:
        Dijkstra(Graph G); //inicia o dijkstra
        int MenorCaminho(int s, int d); //recebe origem e destino

};

#endif // DIJKSTRA_HPP