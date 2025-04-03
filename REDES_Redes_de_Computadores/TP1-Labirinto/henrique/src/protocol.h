#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MAX_MOVES 100
#define MAX_BOARD_SIZE 10

typedef struct {
    int type; // Tipo da ação
    int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE]; // Labirinto visível
    int moves[MAX_MOVES]; // Movimentos possíveis
} Action;



#endif
