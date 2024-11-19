#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <list> //Para lista de Adjacencia
#include <queue> //Para definir as prioridades
using namespace std;

class Graph {
    private:
        int numeroVerticesOriginal; // Numero de vertices original
        int numeroVerticesDuplicados; // Numero de vertices*2
        list<pair<int,int> >* adjacencia; //Lista de adj. com vertice e distancia
    public:
        Graph();
        Graph(int numeroVerticesDuplicados); //Construtor
        void addAresta(int v, int u, int D); //Adiciona Aresta
        int getNumVertices(); //pega o numero de vertices
        list<pair<int,int> >* getListaDeAdjacencia(); //pega a lista de adjacencia

};

#endif // GRAPH_HPP