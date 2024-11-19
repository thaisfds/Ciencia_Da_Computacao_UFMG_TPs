#include "dijkstra.hpp"
#define INF 0x3f3f3f3f //define INF como maior número possivel

Dijkstra::Dijkstra(Graph G){
    this->G = G; //Add o grafo no dijkstra
}

/*Codigo Dijkstra contruido de acordo com o pseudocódigo visto em sala do passo 1 ao 8*/
int Dijkstra::MenorCaminho(int s, int d){
    /*----------1° Inicia o metodo----------*/
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> filaDePrioridade; // Inicia Fila de prioridade (distancia, vertice) invertida
    vector<int> dist(G.getNumVertices(), INF); //Inicia o vetor de distancias com valores infinitos
    filaDePrioridade.push(make_pair(0, s)); //Adiciona a origem na nossa fila de prioridade
    dist[s] = 0; //Inicializa a distancia da origem até ela mesma como 0*
    /*----------2° Repete n vezes = Enquanto a fila de prioridade não estiver vazia----------*/
    while (!filaDePrioridade.empty()) {
        /*----------3° Acha v desmarcado com menor d[v]----------*/
        int v = filaDePrioridade.top().second;
        /*----------4° Marca v----------*/
        filaDePrioridade.pop();
        list<pair<int,int>>::iterator i; //ponteiro para lista de pares
        list<pair<int,int> >*LA = G.getListaDeAdjacencia(); //pega a lista de adj. do grafo G
        /*----------5° Para cada vizinho w de v----------*/
        for (i = LA[v].begin(); i != LA[v].end(); ++i) {
            int w = (*i).first; //pega o vizinho com interdor
            int c = (*i).second; //pega a distancia até esse vizinho
            /*----------6° Se w desmarcado e d + c(v,w) < d[w]----------*/
            if (dist[v]+c < dist[w] && c != -1) {
                /*----------7° d[w] = d + c(v,w)----------*/
                dist[w] = dist[v] + c;
                /*----------8° Atualiza (w,d[w])----------*/
                filaDePrioridade.push(make_pair(dist[w], w));
            }
        }
        
    }
    
    /*----------9° Retorna -1 se não ouver nenhum caminho ou a distancia caso contrário----------*/
    if(dist[d-1] == INF)
        return -1;
    else
        return dist[d-1];
    /*Retorna dist[d-1] pois
        - A entrada vai de 1 a d
        - O grafo vai de 0 a d-1
    */
}