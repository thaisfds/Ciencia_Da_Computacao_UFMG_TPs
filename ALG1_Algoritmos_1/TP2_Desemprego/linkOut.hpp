#ifndef LINKOUT_HPP
#define LINKOUT_HPP
#include "graph.hpp"

class LinkOut{
    private: 
        Graph Rede; //Grafo

    public:
        LinkOut(Graph Rede); //Construtor
        int algoritmoGuloso(); //Algoritmo Guloso
        int algoritmoExato(); //Algoritmo Exato
        bool DFS(vector<vector<int>>& bpGraph, int u, vector<bool>& seen, vector<int>& matchR); //Algoritmo auxiliar para o algoritmo exato (DFS)

};

#endif // LINKOUT_HPP