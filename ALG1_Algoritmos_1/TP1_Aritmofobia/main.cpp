#include <iostream>
#include "dijkstra.hpp"

int main(int argc, char const *argv[]) {
    // Your code here
    /*Inicialização de variáveis de acordo com as informações do TP
        - N = Numero de vertices
        - A = Numero de arestas
        - X1 = Vertice X1
        - X2 = Vertice X2
        - D = Distancia entre X1 e X2
    */
    int N, A, X1, X2, D;

    /*Leitura do numero de vertices e arestas*/
    cin >> N >> A;

    /*Inicializa o grafo como mapa da cidade*/
    Graph mapa = Graph(N); 

    /*Loop para adicionar  as arestas de peso par no grafo*/
    for(int i = 0; i< A; i++){
        cin >> X1 >> X2 >> D;
        if(D%2 == 0){
           mapa.addAresta(X1-1, X2-1, D); //Add aresta par
        }
    }

    /*Inicializa o dijkstra como caminhos entre as cidades*/
    Dijkstra caminho = Dijkstra(mapa); 

    /*Calcula o menor caminho da origem para a ultima cidade*/
    cout << caminho.MenorCaminho(0,N) << endl;

    return 0;
}