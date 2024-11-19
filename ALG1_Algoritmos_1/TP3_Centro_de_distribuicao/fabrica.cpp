#include "fabrica.hpp"

Fabrica::Fabrica(){
    // Construtor vazio
}

int Fabrica::otimizacaoLigasMetalicas(int *ligasMetalicas, int N, int W) {
    
    // Alocação de memória para o vetor
    int* melhorMinimoLigas = new int[W + 1];

    // Inicialização do vetor de melhor mínimo de ligas para cada demanda <= W
    for (int i = 0; i <= W; i++) {
        melhorMinimoLigas[i] = W + 1;
    }

    melhorMinimoLigas[0] = 0; // Caso base

    // Para cada tamanho de liga metálica até a demanda W
    for (int i = 1; i <= W; i++) {
        // Para cada liga metálica disponível
        for (int j = 0; j < N; j++) {
            int lm = ligasMetalicas[j];
            // Se a subtração da demanda i pelo tamanho da liga metálica atual for maior ou igual a 0
            if (i - lm >= 0){
                //Atualiza o melhor mínimo de ligas para a demanda i
                melhorMinimoLigas[i] = std::min(melhorMinimoLigas[i], 1 + melhorMinimoLigas[i - lm]);
            }
        }
    }

    int result = melhorMinimoLigas[W];
    delete[] melhorMinimoLigas;

    if(result != W + 1)
        return result;
     
    return -1;
}