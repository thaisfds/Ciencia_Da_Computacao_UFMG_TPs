#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game_logic.h"


// Variáveis globais do estado do jogo
int player_x, player_y;
int maze[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int visible_maze[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int maze_size = 0;
int maze_rows, maze_cols;


void find_player_position() {
    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        for (int j = 0; j < MAX_BOARD_SIZE; j++) {
            if (maze[i][j] == 2) {
                player_x = i;
                player_y = j;
                return;
            }
        }
    }
}

void initialize_visible_maze() {
    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        for (int j = 0; j < MAX_BOARD_SIZE; j++) {
            if (maze[i][j] == -1) {
                visible_maze[i][j] = -1; // Fora dos limites
            } else {
                visible_maze[i][j] = 4; // Não descoberto
            }
        }
    }

    // Revela a posição inicial do jogador
    visible_maze[player_x][player_y] = 5; // Jogador
}


// Carrega o labirinto do arquivo
void load_maze(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo do labirinto");
        exit(EXIT_FAILURE);
    }

    maze_rows = 0;
    maze_cols = 0;

    char buffer[256]; // Buffer para armazenar cada linha do arquivo
    while (fgets(buffer, sizeof(buffer), file)) {
        int col = 0;
        char *token = strtok(buffer, " "); // Divide a linha em tokens (números)

        while (token != NULL && col < MAX_BOARD_SIZE) {
            maze[maze_rows][col] = atoi(token); // Converte o token para inteiro
            col++;
            token = strtok(NULL, " ");
        }

        if (col > 0) { // Se houve algo para ler na linha
            maze_rows++;
            if (maze_cols < col) {
                maze_cols = col; // Atualiza o número máximo de colunas
            }
        }

        if (maze_rows >= MAX_BOARD_SIZE) {
            break; // Evita ultrapassar o tamanho máximo da matriz
        }
    }

    fclose(file);

    // Preenche o restante do tabuleiro com -1
    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        for (int j = 0; j < MAX_BOARD_SIZE; j++) {
            if (i >= maze_rows || j >= maze_cols) {
                maze[i][j] = -1;
            }
        }
    }

    initialize_visible_maze();

}

void update_visible_maze() {
    // Revela as células adjacentes ao jogador (dentro do raio 1)
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = player_x + dx;
            int ny = player_y + dy;

            // Verifica se está dentro do limite do labirinto
            if (nx >= 0 && ny >= 0 && nx < MAX_BOARD_SIZE && ny < MAX_BOARD_SIZE) {
                // Revela apenas células válidas (não paredes ou fora dos limites)
                if (maze[nx][ny] != -1) {
                    visible_maze[nx][ny] = maze[nx][ny];
                }
            }
        }
    }

    // Preserva células já reveladas e restaura caminhos livres
    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        for (int j = 0; j < MAX_BOARD_SIZE; j++) {
            if (visible_maze[i][j] != 4 && maze[i][j] != -1) { 
                visible_maze[i][j] = maze[i][j]; // Mantém células já visíveis
            }
        }
    }

    // Marca a posição atual do jogador
    visible_maze[player_x][player_y] = 5; // Jogador
}

void reveal_full_maze() {
    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        for (int j = 0; j < MAX_BOARD_SIZE; j++) {
            if (maze[i][j] != -1) { // Apenas células válidas
                visible_maze[i][j] = maze[i][j];
            }
        }
    }
}


// Gera a lista de movimentos válidos
void get_possible_moves(int *moves) {
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Cima, Direita, Baixo, Esquerda
    int move_index = 0;

    for (int i = 0; i < 4; i++) {
        int nx = player_x + directions[i][0];
        int ny = player_y + directions[i][1];

        // Verifica se a nova posição está dentro dos limites do tabuleiro
        if (nx >= 0 && ny >= 0 && nx < MAX_BOARD_SIZE && ny < MAX_BOARD_SIZE) {
            // Verifica se a posição não é uma parede ou fora do tabuleiro
            if (maze[nx][ny] != 0 && maze[nx][ny] != -1) {
                moves[move_index++] = i + 1; // Adiciona o movimento (1 = Cima, 2 = Direita, etc.)
            }
        }
    }

    // Preenche o restante com 0 para indicar que não há mais movimentos válidos
    while (move_index < MAX_MOVES) {
        moves[move_index++] = 0;
    }
}

// Processa um movimento do jogador
int move_player(int direction) {
    int new_x = player_x;
    int new_y = player_y;

    // Calcula a nova posição com base na direção
    switch (direction) {
        case 1: // Cima
            new_x = player_x - 1;
            break;
        case 2: // Direita
            new_y = player_y + 1;
            break;
        case 3: // Baixo
            new_x = player_x + 1;
            break;
        case 4: // Esquerda
            new_y = player_y - 1;
            break;
        default:
            return 0; // Movimento inválido
    }

    // Verifica se a nova posição é válida
    if (new_x < 0 || new_x >= MAX_BOARD_SIZE || new_y < 0 || new_y >= MAX_BOARD_SIZE ||
        maze[new_x][new_y] == 0) {
        return 0; // Movimento inválido (fora do limite ou parede)
    }

    // Atualiza a posição do jogador
    player_x = new_x;
    player_y = new_y;

    // Verifica se o jogador chegou à saída
    if (maze[player_x][player_y] == 3) {
        return 2; // Jogador venceu
    }

    return 1; // Movimento bem-sucedido
}

// Retorna o labirinto visível
void get_visible_maze(int visible[MAX_BOARD_SIZE][MAX_BOARD_SIZE]) {
    memcpy(visible, visible_maze, sizeof(visible_maze));
}

typedef struct {
    int x, y;
} Position;

void calculate_hint(int x, int y, int maze[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int *moves) {
    int visited[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = {0};
    Position queue[MAX_QUEUE_SIZE];
    int parent[MAX_BOARD_SIZE][MAX_BOARD_SIZE][2];
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Cima, direita, baixo, esquerda
    int front = 0, rear = 0;

    // Inicializa a fila e os pais
    queue[rear++] = (Position){x, y};
    visited[x][y] = 1;
    parent[x][y][0] = -1; // Indica que não há pai
    parent[x][y][1] = -1;

    // Busca em largura (BFS) para encontrar o caminho até a saída
    while (front < rear) {
        Position current = queue[front++];
        if (maze[current.x][current.y] == 3) { // Encontrou a saída
            int path[MAX_MOVES];
            int idx = 0;

            // Reconstrói o caminho a partir dos pais
            while (parent[current.x][current.y][0] != -1) {
                int px = parent[current.x][current.y][0];
                int py = parent[current.x][current.y][1];

                // Determina o movimento que levou à posição atual
                for (int i = 0; i < 4; i++) {
                    if (px + directions[i][0] == current.x && py + directions[i][1] == current.y) {
                        path[idx++] = i + 1; // Converte para movimentos [1, 2, 3, 4]
                        break;
                    }
                }

                current.x = px;
                current.y = py;
            }

            // Preenche o vetor `moves` com o caminho encontrado
            for (int i = idx - 1; i >= 0; i--) {
                moves[idx - 1 - i] = path[i];
            }
            while (idx < MAX_MOVES) {
                moves[idx++] = 0; // Preenche o restante com 0
            }

            return; // Encerra após encontrar o caminho
        }

        // Adiciona os vizinhos válidos à fila
        for (int i = 0; i < 4; i++) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];

            // Verifica se a célula é válida, não visitada e não é um muro
            if (nx >= 0 && ny >= 0 && nx < MAX_BOARD_SIZE && ny < MAX_BOARD_SIZE &&
                maze[nx][ny] != 0 && maze[nx][ny] != -1 && !visited[nx][ny]) {
                queue[rear++] = (Position){nx, ny};
                visited[nx][ny] = 1;
                parent[nx][ny][0] = current.x;
                parent[nx][ny][1] = current.y;

                // Verifica se a fila ultrapassou o limite
                if (rear >= MAX_QUEUE_SIZE) {
                    printf("[ERROR] Queue overflow in calculate_hint\n");
                    memset(moves, 0, sizeof(int) * MAX_MOVES); // Retorna vazio
                    return;
                }
            }
        }
    }

    // Se não encontrou caminho, preenche `moves` com 0
    memset(moves, 0, sizeof(int) * MAX_MOVES);
}
