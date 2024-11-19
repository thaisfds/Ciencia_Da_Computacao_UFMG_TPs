#include "fabrica.hpp"

int main(int argc, char const *argv[]) {

    Fabrica fabrica;
    // Your code here
    // T = numero de casos de teste (fabricas)
    // N = numero de ligas metalicas disponiveis
    // W = quantidade de ligas solicitadas
    int T, N, W;

    cin >> T;

    for(int i = 0; i < T; i++){
        cin >> N >> W;
        int* ligasMetalicas = new int[N]; // vetor que armazena as ligas metalicas disponiveis

        //Preenche o vetir com os tamanhos das ligas metalicas disponiveis
        for(int j = 0; j < N; j++){
            cin >> ligasMetalicas[j];
        }
        
        cout << fabrica.otimizacaoLigasMetalicas(ligasMetalicas,N, W) << endl;
        
        delete[] ligasMetalicas;
    }

    return 0;
}      
