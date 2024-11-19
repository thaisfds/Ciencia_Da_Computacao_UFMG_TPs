#include "graph.hpp"

using namespace std;
/*Construtor padrão necessário para o dijkstra*/
Graph::Graph(){

}
/*Armazenamento do numero de vertices original e duplicado*/
Graph::Graph(int numeroVerticesOriginal) {
    this->numeroVerticesOriginal = numeroVerticesOriginal; //armazena o numero de vertices original
    this->numeroVerticesDuplicados = numeroVerticesOriginal*2; //armazena o novo numero de vertices dobrados
    adjacencia = new list<pair<int,int>>[numeroVerticesOriginal*2]; //cria a lista de adj. para os vertices dobrados
}

/*Duplicação e inicialização do grafo G como Gpar e Gimpar realizando conecções 
apenas do lado par com o lado impar, e do lado impar com o par
A primeira metade da lista é par, e a segunda metade é impar

    LEMBRETE:
    G = [0,1,2,3,4] = grafo original
    Gnovo = [0,1,2,3,4,5,6,7,8,9] = grafo modificado
    Gpar = [0,1,2,3,4]
    Gimpar = [5,6,7,8,9] = [0,1,2,3,4]+5 = Gpar + numeroVerticesOriginal
*/
void Graph::addAresta(int v, int u, int D){
    adjacencia[v].push_back(make_pair(u+numeroVerticesOriginal, D)); //v par conecta em u impar
    adjacencia[v+numeroVerticesOriginal].push_back(make_pair(u, D)); //v impar conecta em u par
    adjacencia[u].push_back(make_pair(v+numeroVerticesOriginal, D)); //u par conecta em v impar
    adjacencia[u+numeroVerticesOriginal].push_back(make_pair(v, D)); //Todos com mesma distancia D
}
//make_par() cria um par com vertice e distancia

/*Retorna o numero de vertices do novo grafo*/
int Graph::getNumVertices(){
    return numeroVerticesDuplicados;
}

//Retorna a lista de adjacencia do grafo
list<pair<int,int> >* Graph::getListaDeAdjacencia(){
    return adjacencia;
}
