#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define MAX_BOARD_SIZE 10
#define MAX_MOVES 100
#define MAX_QUEUE_SIZE 1000

// Variáveis globais públicas
extern int player_x; // Posição X do jogador
extern int player_y; // Posição Y do jogador
extern int maze[MAX_BOARD_SIZE][MAX_BOARD_SIZE]; // Labirinto completo
extern int visible_maze[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
extern int maze_rows; // Número de linhas do labirinto
extern int maze_cols; // Número de colunas do labirinto

// Funções públicas
void initialize_visible_maze();
void load_maze(const char *filename);
void update_visible_maze();
void reveal_full_maze();
void find_player_position();
void get_possible_moves(int *moves);
int move_player(int direction);
void get_visible_maze(int visible[MAX_BOARD_SIZE][MAX_BOARD_SIZE]);
void calculate_hint(int x, int y, int maze[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int *moves);

#endif
