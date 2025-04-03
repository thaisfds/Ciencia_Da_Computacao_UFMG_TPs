// common.h

#ifndef COMMON_H
#define COMMON_H

// Definições de constantes para o tamanho máximo do labirinto e número máximo de movimentos.
#define MAX_SIZE 10       // Tamanho máximo do labirinto (10x10).
#define MAX_MOVES 100     // Número máximo de movimentos permitidos em uma ação.

// Definição de enumeradores para diferentes tipos de ações que podem ser realizadas.
typedef enum {
    ACTION_START = 0,   // Iniciar um novo jogo.
    ACTION_MOVE = 1,    // Realizar um movimento.
    ACTION_MAP = 2,     // Solicitar o mapa atual do labirinto.
    ACTION_HINT = 3,    // Solicitar uma dica de movimento.
    ACTION_UPDATE = 4,  // Atualizar o estado do jogo.
    ACTION_WIN = 5,     // Indicar que o jogador venceu o jogo.
    ACTION_RESET = 6,   // Reiniciar o jogo.
    ACTION_EXIT = 7     // Sair do jogo.
} ActionType;

// Enumerador para tipos de movimentos que o jogador pode realizar.
typedef enum {
    MOVE_UP = 1,     // Movimento para cima.
    MOVE_RIGHT = 2,  // Movimento para a direita.
    MOVE_DOWN = 3,   // Movimento para baixo.
    MOVE_LEFT = 4    // Movimento para a esquerda.
} MoveType;

// Estrutura que representa uma ação entre cliente e servidor.
struct action {
    ActionType type;               // Tipo da ação.
    MoveType moves[MAX_MOVES];     // Array de movimentos (direções).
    int board[MAX_SIZE][MAX_SIZE]; // Estado atual do tabuleiro do labirinto.
};

#endif // COMMON_H
