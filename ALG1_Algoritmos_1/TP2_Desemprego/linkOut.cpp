#include "linkOut.hpp"

LinkOut::LinkOut(Graph Rede){
    this->Rede = Rede;
}

/* Algoritmo Guloso */
int LinkOut::algoritmoGuloso(){
    
    int numeroDeConexoes = 0; //Numero de conexoes máximo
    int numeroUsuarios = Rede.getNumUsuarios();
    int numeroEmpregos = Rede.getNumEmpregos();


    vector<vector<int>>* matrizAdjacencia = Rede.getMatrizAdjacencia(); //Pega a matriz de adjacencia do grafo
    
    //Percorre a matriz de adjacencia procurando por conexoes entre usuarios e empresas
    for(int i = 0; i < numeroUsuarios; i++){
        for(int j = 0; j < numeroEmpregos; j++){
            //Se encontrar uma conexao entre um usuario e uma empresa, e a empresa ainda nao estiver conectada a nenhum usuario, conecta
            if((*matrizAdjacencia)[i][j] == 1 && (*matrizAdjacencia)[0][j] != 2){
                (*matrizAdjacencia)[0][j] = 2; //Marca a empresa como conectada adicionando 2 na matriz de adjacencia
                j = numeroEmpregos; //Finaliza o loop
                j--; //Finaliza o loop
                numeroDeConexoes++; //Incrementa o numero de conexoes
            }
        }
    }

    return numeroDeConexoes;

}

/* Algoritmo Exato */
int LinkOut::algoritmoExato() {

    int U = Rede.getNumUsuarios(); //Numero de usuarios
    int E = Rede.getNumEmpregos(); //Numero de empresas

    vector<vector<int>> bipartido(U, vector<int>(E, 0)); //Matriz de adjacencia bipartida

    //Preenche a matriz de adjacencia bipartida
    for (int i = 0; i < U; i++) {
        for (int j = 0; j < E; j++) {
            bipartido[i][j] = (*Rede.getMatrizAdjacencia())[i][j];
        }
    }

    vector<int> candidatos(E, -1); //Vetor de candidatos inicializado com -1

    int numeroDeConexoes = 0;

    //Percorre os usuarios procurando por conexoes
    for (int u = 0; u < U; u++) {
        vector<bool> visitado(E, false); //Vetor de visitados inicializado com false
        if (DFS(bipartido, u, visitado, candidatos))
            numeroDeConexoes++; //Incrementa o numero de conexoes se exisir um caminho
    }

    return numeroDeConexoes;
}

/* Algoritmo auxiliar para o algoritmo exato (DFS) */
bool LinkOut::DFS(vector<vector<int>>& bipartido, int u, vector<bool>& visitado, vector<int>& candidatos) {
    
    //Percorre as empresas procurando por conexoes
    for (int v = 0; v < Rede.getNumEmpregos(); v++) {
        //Se encontrar uma conexao entre um usuario e uma empresa, e a empresa ainda nao estiver conectada a nenhum usuario, conecta
        if (bipartido[u][v] && !visitado[v]) {
            visitado[v] = true;

            //Se não ouver candidato ou se o DFS para o candidato for verdadeiro atualiza o emparelhamento
            if (candidatos[v] < 0 || DFS(bipartido, candidatos[v], visitado, candidatos)) {
                candidatos[v] = u;
                return true;
            }
        }
    }

    return false;
}


