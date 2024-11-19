#include "graph.hpp"
using namespace std;

Graph::Graph(){

}

/*Inicialização do grafo alocando a memoria necessária para a matriz de adjacencia*/
Graph::Graph(int numeroUsuarios, int numeroEmpregos, int numeroQualificacoes) {
    this->numeroUsuarios = numeroUsuarios; 
    this->numeroEmpregos = numeroEmpregos;
    this->numeroQualificacoes = numeroQualificacoes;
    matrizAdjacencia = new vector<vector<int>>(numeroUsuarios, vector<int>(numeroEmpregos, 0));
}

/*Adiciona uma aresta entre um usuario e uma empresa*/
void Graph::addAresta(int usuario, int empresa){
    (*matrizAdjacencia)[usuario][empresa] = 1;
}

/*Retorna o numero de vertices do grafo*/
int Graph::getNumVertices(){
    return numeroUsuarios + numeroEmpregos;
}

/*Retorna o numero de usuarios do grafo*/
int Graph::getNumUsuarios(){
    return numeroUsuarios;
}

/*Retorna o numero de empregos do grafo*/
int Graph::getNumEmpregos(){
    return numeroEmpregos;
}

/*Retorna o numero de qualificacoes do grafo*/
int Graph::getNumQualificacoes(){
    return numeroQualificacoes;
}

/*Retorna a matriz de adjacencia do grafo*/
vector<vector<int>>* Graph::getMatrizAdjacencia(){
    return matrizAdjacencia;
}
