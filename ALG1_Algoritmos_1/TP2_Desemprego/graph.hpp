#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
//#include <queue>
#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f

using namespace std;

class Graph {
    private:
        int numeroUsuarios;
        int numeroEmpregos;
        int numeroQualificacoes;
        
        vector<vector<int>>* matrizAdjacencia; //Matriz de adjacencia

    public:
        Graph();
        Graph(int numeroUsuarios, int numeroEmpregos, int numeroQualificacoes); //Construtor
        void addAresta(int usuario, int empresa); //Adiciona Aresta
        int getNumVertices(); //Retorna o numero de vertices do grafo
        int getNumUsuarios(); //Retorna o numero de usuarios do grafo
        int getNumEmpregos(); //Retorna o numero de empregos do grafo
        int getNumQualificacoes(); //Retorna o numero de qualificacoes do grafo
        vector<vector<int>>* getMatrizAdjacencia(); //Retorna lista de adjacencia
        
};

#endif // GRAPH_HPP