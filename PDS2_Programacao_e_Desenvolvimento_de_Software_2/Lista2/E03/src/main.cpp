#include "Coordenada.hpp"
#include "BlocoMina.hpp"
#include "Bloco.hpp"
#include <iostream>
#include <iomanip>
#include <string>

/**
 * @brief Libera a memória alocada para montar o tabuleiro
 * @param tabuleiro Tabuleiro do jogo
 */
void liberarMemoria(std::vector<std::vector<Bloco*>>& tabuleiro) {
    for (auto linha : tabuleiro) {
        for (auto bloco : linha) {
            delete bloco;
        }
    }
}

/**
 * @brief Printa o tabuleiro do jogo no terminal
 * @param tabuleiro Tabuleiro do jogo
 */
void printarTabuleiro(std::vector<std::vector<Bloco*>>& tabuleiro) {
    for (auto linha: tabuleiro) {
        for (auto bloco : linha) {
            std::cout << std::setw(3) << bloco->getSimbolo();
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


/**
 * @brief Inicia o jogo:
 * "r x y": Revela o bloco nas coordenadas x e y
 * "e": Sai do jogo
 * @param tabuleiro 
 */
void jogar(std::vector<std::vector<Bloco*>>& tabuleiro) {
    bool exit = false;
    bool podeMovimentar = true;
    printarTabuleiro(tabuleiro);

    while((exit == false) && podeMovimentar) {
        char opt;
        std::cin >> opt;

        switch (opt) {
            case 'r': {
                int row, col;
                std::cin >> row >> col;

                Bloco* bloco = tabuleiro[row][col];
                podeMovimentar = bloco->revelar(tabuleiro);
                printarTabuleiro(tabuleiro);
                if (!podeMovimentar)
                    std::cout << "Você perdeu!" << std::endl;
                break;
            }
            case 'e': {
                std::cout << "Jogo encerrado!" << std::endl;
                exit = true; 
                break; 
            }         
        }
    }
}

/**
 * @brief Coloca as bombas no jogo seguindo os seguintes comandos:
 * "b x y": Transforma o bloco nas coordenadas [x, y] em uma bomba
 * "e": Para de inserir bombas
 * @param tabuleiro 
 */
void colocarBombas(std::vector<std::vector<Bloco*>>& tabuleiro) {
    bool continuar = true;

    while(continuar) {
        char opt;
        std::cin >> opt;

        switch (opt) {
            case 'b': {
                int row; int col;
                std::cin >> row >> col;

                // Libera o espaço de memória reservado para o bloco e cria um novo espaço
                // para o tipo BlocoMina
                delete tabuleiro[row][col];
                Coordenada coord(row, col);
                tabuleiro[row][col] = new BlocoMina(tabuleiro, coord);
                break;
            }
            case 'e': {
                continuar = false;
                break;
            }
        }
    }
}

/**
 * @brief Cria um tabuleiro NxN e preenche com blocos
 * @param tabuleiro Tabuleiro do jogo
 */
void preencherTabuleiro(std::vector<std::vector<Bloco*>>& tabuleiro, const int N) {
    for (int l = 0; l < N; l++) {
        tabuleiro[l] = std::vector<Bloco*>(N);

        for (int c = 0; c < N; c++) {
            Coordenada coord(l, c);
            tabuleiro[l][c] = new Bloco(coord);
        }
    }
}


int main() {
    /**
     * @brief Inicializa o tamanho do tabuleiro.
     * Note que ele será uma matrix quadrada
     */
    int tamTab;
    std::cin >> tamTab;
    std::vector<std::vector<Bloco*>> tabuleiro(tamTab);

    preencherTabuleiro(tabuleiro, tamTab);
    colocarBombas(tabuleiro);
    jogar(tabuleiro);
    liberarMemoria(tabuleiro);

    return 0;
}