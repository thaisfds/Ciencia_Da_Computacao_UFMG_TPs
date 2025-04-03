// Este é o servidor do jogo de labirinto. Ele gerencia o estado do jogo, processa
// as ações dos clientes e comunica atualizações sobre o estado do labirinto.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "common.h"

// Estrutura que representa o estado do jogo.
typedef struct {
    int maze[MAX_SIZE][MAX_SIZE];      // Representação do labirinto.
    int game_state[MAX_SIZE][MAX_SIZE]; // Estado visível do jogo para o jogador.
    int player_x;                       // Posição X do jogador no labirinto.
    int player_y;                       // Posição Y do jogador no labirinto.
    int exit_x;                         // Posição X da saída do labirinto.
    int exit_y;                         // Posição Y da saída do labirinto.
    int rows;                           // Número de linhas no labirinto.
    int cols;                           // Número de colunas no labirinto.
} Game;

// Prototipação das funções utilizadas no servidor.
int read_maze(const char *filename, Game *game);
int setup_server_socket(const char *ip_version, const char *port);
void handle_client(int client_fd, Game *game);
void initialize_game(Game *game);
void send_update(int client_fd, Game *game);
void send_map(int client_fd, Game *game);
void send_hint(int client_fd, Game *game);
int find_path(Game *game, int start_x, int start_y, int exit_x, int exit_y, MoveType *hint_moves);
void reveal_cells(Game *game);
void send_win(int client_fd, Game *game);
void send_nothing(int client_fd);

// Estrutura para nós da fila utilizada no algoritmo BFS (Busca em Largura).
typedef struct {
    int x;                  // Posição X do nó no labirinto.
    int y;                  // Posição Y do nó no labirinto.
    MoveType path[MAX_MOVES];    // Caminho percorrido até este nó.
    int path_length;        // Comprimento do caminho.
} Node;

/**
 * Função para ler o labirinto a partir de um arquivo e armazená-lo na estrutura Game.
 *
 * @param filename Nome do arquivo que contém a representação do labirinto.
 * @param game Ponteiro para a estrutura Game onde o labirinto será armazenado.
 * @return Retorna 0 em caso de sucesso.
 */
int read_maze(const char *filename, Game *game) {
    FILE *file = fopen(filename, "r"); // Abre o arquivo para leitura.

    game->rows = 0; // Inicializa o número de linhas.
    game->cols = 0; // Inicializa o número de colunas.
    char line[256];  // Buffer para armazenar cada linha do arquivo.

    // Lê o arquivo linha por linha.
    while (fgets(line, sizeof(line), file)) {
        if (game->rows < MAX_SIZE) { // Garante que não exceda o tamanho máximo.
            int col = 0;
            char *token = strtok(line, " \t\n"); // Tokeniza a linha com base em espaços, tabulações e quebras de linha.
            while (token != NULL) {
                if (col < MAX_SIZE) { // Garante que não exceda o tamanho máximo.
                    game->maze[game->rows][col++] = atoi(token); // Converte o token para inteiro e armazena no labirinto.
                    token = strtok(NULL, " \t\n"); // Obtém o próximo token.
                }
            }
            if (col > game->cols) {
                game->cols = col; // Atualiza o número máximo de colunas.
            }
            game->rows++; // Incrementa o número de linhas.
        }
    }

    fclose(file); // Fecha o arquivo.
    return 0;
}

/**
 * Função para configurar o socket do servidor, seja IPv4 ou IPv6.
 *
 * @param ip_version Versão do IP a ser utilizada ("v4" ou "v6").
 * @param port Porta na qual o servidor irá escutar.
 * @return Retorna o descritor do socket de escuta configurado.
 */
int setup_server_socket(const char *ip_version, const char *port) {
    struct addrinfo hints, *res, *p;
    int listen_fd = -1; // Inicialização para evitar uso não inicializado.

    memset(&hints, 0, sizeof hints); // Zera a estrutura hints.
    if (strcmp(ip_version, "v4") == 0) {
        hints.ai_family = AF_INET; // Define família de endereços IPv4.
    } else if (strcmp(ip_version, "v6") == 0) {
        hints.ai_family = AF_INET6; // Define família de endereços IPv6.
    }
    hints.ai_socktype = SOCK_STREAM; // Define tipo de socket como TCP.
    hints.ai_flags = AI_PASSIVE;     // Indica que o socket será usado para escuta.

    getaddrinfo(NULL, port, &hints, &res); // Obtém as informações de endereço.

    // Itera sobre os resultados e tenta criar e vincular o socket.
    for(p = res; p != NULL; p = p->ai_next) {
        listen_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol); // Cria o socket.

        int yes = 1;
        setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)); // Define a opção SO_REUSEADDR.

        bind(listen_fd, p->ai_addr, p->ai_addrlen); // Vincula o socket ao endereço e porta.

        break; // Sai do loop após o primeiro sucesso.
    }

    freeaddrinfo(res); // Libera a estrutura de endereços.

    listen(listen_fd, 1); // Coloca o socket em modo de escuta, com backlog de 1.

    return listen_fd; // Retorna o descritor do socket de escuta.
}

/**
 * Função para inicializar o estado do jogo, configurando a posição do jogador e da saída.
 *
 * @param game Ponteiro para a estrutura Game que representa o estado do jogo.
 */
void initialize_game(Game *game) {
    // Inicializa o estado do jogo com células desconhecidas (valor 4).
    for(int i = 0; i < game->rows; i++) {
        for(int j = 0; j < game->cols; j++) {
            game->game_state[i][j] = 4; // Marca como célula desconhecida.
        }
    }

    // Procura pelas posições de entrada (valor 2) e saída (valor 3) no labirinto.
    for(int i = 0; i < game->rows; i++) {
        for(int j = 0; j < game->cols; j++) {
            if(game->maze[i][j] == 2) { // Entrada encontrada.
                game->player_x = i;       // Define a posição X do jogador.
                game->player_y = j;       // Define a posição Y do jogador.
                game->game_state[i][j] = 5; // Marca a posição do jogador no estado do jogo.
            }
            if(game->maze[i][j] == 3) { // Saída encontrada.
                game->exit_x = i;         // Define a posição X da saída.
                game->exit_y = j;         // Define a posição Y da saída.
            }
        }
    }

    reveal_cells(game); // Revela as células ao redor do jogador.

    // Redefine a posição do jogador para garantir que esteja marcada corretamente.
    game->game_state[game->player_x][game->player_y] = 5; // Marca a posição do jogador.
}

/**
 * Função para revelar as células ao redor da posição atual do jogador.
 *
 * @param game Ponteiro para a estrutura Game que representa o estado do jogo.
 */
void reveal_cells(Game *game) {
    int x = game->player_x; // Posição X do jogador.
    int y = game->player_y; // Posição Y do jogador.

    // Itera pelas células adjacentes (incluindo a própria posição do jogador).
    for(int i = x-1; i <= x+1; i++) {
        for(int j = y-1; j <= y+1; j++) {
            // Verifica se a posição está dentro dos limites do labirinto.
            if(i >=0 && i < game->rows && j >=0 && j < game->cols) {
                game->game_state[i][j] = game->maze[i][j]; // Revela o conteúdo da célula.
            }
        }
    }

    // Nota: Não há necessidade de sobrescrever a posição do jogador aqui, pois já está marcada.
}

/**
 * Função para enviar uma atualização do estado do jogo para o cliente.
 *
 * @param client_fd Descritor do socket do cliente.
 * @param game Ponteiro para a estrutura Game que representa o estado do jogo.
 */
void send_update(int client_fd, Game *game) {
    struct action msg; // Estrutura para a mensagem a ser enviada.
    memset(&msg, -1, sizeof(msg)); // Inicializa msg.board com -1 para células não utilizadas.
    msg.type = ACTION_UPDATE;      // Define o tipo da ação como atualização.

    int move_count = 0; // Contador de movimentos possíveis.

    // Verifica possíveis movimentos e adiciona-os à lista de movimentos na mensagem.
    // Movimento para cima.
    if(game->player_x > 0 && game->maze[game->player_x -1][game->player_y] != 0) {
        msg.moves[move_count++] = MOVE_UP;
    }
    // Movimento para a direita.
    if(game->player_y < game->cols -1 && game->maze[game->player_x][game->player_y +1] != 0) {
        msg.moves[move_count++] = MOVE_RIGHT;
    }
    // Movimento para baixo.
    if(game->player_x < game->rows -1 && game->maze[game->player_x +1][game->player_y] != 0) {
        msg.moves[move_count++] = MOVE_DOWN;
    }
    // Movimento para a esquerda.
    if(game->player_y > 0 && game->maze[game->player_x][game->player_y -1] != 0) {
        msg.moves[move_count++] = MOVE_LEFT;
    }

    // Preenche os movimentos restantes com 0 para indicar ausência de movimento.
    for(int i = move_count; i < MAX_MOVES; i++) {
        msg.moves[i] = 0;
    }

    // Preenche o tabuleiro com o estado atual do jogo.
    for(int i = 0; i < game->rows; i++) {
        for(int j = 0; j < game->cols; j++) {
            msg.board[i][j] = game->game_state[i][j];
        }
    }

    // Envia a mensagem de atualização para o cliente.
    send(client_fd, &msg, sizeof(msg), 0);
}

/**
 * Função para enviar o mapa completo do jogo para o cliente.
 *
 * @param client_fd Descritor do socket do cliente.
 * @param game Ponteiro para a estrutura Game que representa o estado do jogo.
 */
void send_map(int client_fd, Game *game) {
    struct action msg; // Estrutura para a mensagem a ser enviada.
    memset(&msg, -1, sizeof(msg)); // Inicializa msg.board com -1.
    msg.type = ACTION_UPDATE;          // Define o tipo da ação como mapa.

    // Preenche o tabuleiro com o estado atual do jogo.
    for(int i = 0; i < game->rows; i++) {
        for(int j = 0; j < game->cols; j++) {
            msg.board[i][j] = game->game_state[i][j];
        }
    }

    // Envia a mensagem de mapa para o cliente.
    send(client_fd, &msg, sizeof(msg), 0);
}

/**
 * Função para enviar uma dica de movimento para o cliente.
 *
 * @param client_fd Descritor do socket do cliente.
 * @param game Ponteiro para a estrutura Game que representa o estado do jogo.
 */
void send_hint(int client_fd, Game *game) {
    struct action msg; // Estrutura para a mensagem a ser enviada.
    memset(&msg, -1, sizeof(msg)); // Inicializa msg.board com -1.
    msg.type = ACTION_HINT;         // Define o tipo da ação como dica.

    // Tenta encontrar um caminho usando BFS. Se encontrado, os movimentos são preenchidos.
    if(find_path(game, game->player_x, game->player_y, game->exit_x, game->exit_y, msg.moves)) {
        // Caminho encontrado e preenchido em msg.moves.
    } else {
        // Nenhum caminho encontrado, preenche com movimentos vazios.
        for(int i = 0; i < MAX_MOVES; i++) {
            msg.moves[i] = 0;
        }
    }

    // Envia a mensagem de dica para o cliente.
    send(client_fd, &msg, sizeof(msg), 0);
}

/**
 * Função para encontrar um caminho do jogador até a saída usando BFS.
 *
 * @param game Ponteiro para a estrutura Game que representa o estado do jogo.
 * @param start_x Posição X inicial (do jogador).
 * @param start_y Posição Y inicial (do jogador).
 * @param exit_x Posição X da saída.
 * @param exit_y Posição Y da saída.
 * @param hint_moves Array onde os movimentos do caminho serão armazenados.
 * @return Retorna 1 se um caminho for encontrado, 0 caso contrário.
 */
int find_path(Game *game, int start_x, int start_y, int exit_x, int exit_y, MoveType *hint_moves) {
    int visited[MAX_SIZE][MAX_SIZE] = {0}; // Matriz para marcar células visitadas.
    Node queue[MAX_SIZE * MAX_SIZE];        // Fila para BFS.
    int front = 0, rear = 0;                // Índices para frente e traseira da fila.

    // Inicializa a fila com a posição inicial do jogador.
    queue[rear].x = start_x;
    queue[rear].y = start_y;
    queue[rear].path_length = 0;
    rear++;
    visited[start_x][start_y] = 1; // Marca a posição inicial como visitada.

    // Executa BFS até que a fila esteja vazia.
    while(front < rear) {
        Node current = queue[front++]; // Defila o próximo nó.

        // Verifica se a posição atual é a saída.
        if(current.x == exit_x && current.y == exit_y) {
            // Copia o caminho encontrado para hint_moves.
            for(int i = 0; i < current.path_length; i++) {
                hint_moves[i] = current.path[i];
            }
            // Preenche o restante de hint_moves com 0.
            for(int i = current.path_length; i < MAX_MOVES; i++) {
                hint_moves[i] = 0;
            }
            return 1; // Caminho encontrado.
        }

        // Define as direções possíveis de movimento.
        MoveType directions[4] = {MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT};
        for(int d = 0; d < 4; d++) {
            int new_x = current.x;
            int new_y = current.y;
            // Atualiza as coordenadas com base na direção.
            switch(directions[d]) {
                case MOVE_UP: new_x--; break;    // Move para cima.
                case MOVE_RIGHT: new_y++; break; // Move para a direita.
                case MOVE_DOWN: new_x++; break;  // Move para baixo.
                case MOVE_LEFT: new_y--; break;  // Move para a esquerda.
                default: break;
            }

            // Verifica se a nova posição está dentro dos limites e não é uma parede.
            if(new_x >=0 && new_x < game->rows && new_y >=0 && new_y < game->cols &&
               game->maze[new_x][new_y] != 0 && !visited[new_x][new_y]) {
                visited[new_x][new_y] = 1; // Marca a nova posição como visitada.
                Node next = current;        // Cria um novo nó baseado no atual.
                next.x = new_x;             // Atualiza a posição X.
                next.y = new_y;             // Atualiza a posição Y.
                if(next.path_length < MAX_MOVES -1){
                    next.path[next.path_length] = directions[d]; // Adiciona a direção ao caminho.
                    next.path_length++;                           // Incrementa o comprimento do caminho.
                }
                queue[rear++] = next; // Enfila o novo nó.
                if(rear >= MAX_SIZE * MAX_SIZE) break; // Evita overflow da fila.
            }
        }
    }

    // Nenhum caminho encontrado, preenche hint_moves com 0.
    for(int i = 0; i < MAX_MOVES; i++) {
        hint_moves[i] = 0;
    }
    return 0; // Caminho não encontrado.
}

/**
 * Função para enviar uma mensagem de vitória para o cliente.
 *
 * @param client_fd Descritor do socket do cliente.
 * @param game Ponteiro para a estrutura Game que representa o estado do jogo.
 */
void send_win(int client_fd, Game *game) {
    struct action msg; // Estrutura para a mensagem a ser enviada.
    memset(&msg, -1, sizeof(msg)); // Inicializa msg.board com -1.
    msg.type = ACTION_WIN;          // Define o tipo da ação como vitória.

    // Preenche o tabuleiro com o labirinto completo.
    for(int i = 0; i < game->rows; i++) {
        for(int j = 0; j < game->cols; j++) {
            msg.board[i][j] = game->maze[i][j];
        }
    }

    // Envia a mensagem de vitória para o cliente.
    send(client_fd, &msg, sizeof(msg), 0);
}

/**
 * Função para enviar uma mensagem vazia para o cliente, evitando bloqueios.
 *
 * @param client_fd Descritor do socket do cliente.
 */
void send_nothing(int client_fd) {
    struct action msg; // Estrutura para a mensagem a ser enviada.
    memset(&msg, -1, sizeof(msg)); // Inicializa msg.board com -1.
    msg.type = -1; // Define um tipo inválido para indicar ausência de ação válida.
    send(client_fd, &msg, sizeof(msg), 0); // Envia a mensagem vazia.
}

/**
 * Função para lidar com as interações do cliente. Recebe ações do cliente,
 * atualiza o estado do jogo e envia respostas apropriadas.
 *
 * @param client_fd Descritor do socket do cliente.
 * @param game Ponteiro para a estrutura Game que representa o estado do jogo.
 */
void handle_client(int client_fd, Game *game) {
    struct action msg;               // Estrutura para armazenar a mensagem recebida.
    ssize_t bytes_received;          // Número de bytes recebidos.
    int game_over = 0;               // Flag para indicar se o jogo foi concluído.

    // Loop principal para receber mensagens do cliente.
    while ((bytes_received = recv(client_fd, &msg, sizeof(msg), 0)) > 0) {
        // Processa comandos de início, reset e exit primeiro.
        if (msg.type == ACTION_START) { // Cliente solicita iniciar um novo jogo.
            printf("starting new game\n");
            initialize_game(game);      // Inicializa o estado do jogo.
            send_update(client_fd, game); // Envia a atualização do jogo para o cliente.
            game_over = 0;               // Reseta o estado de game_over.
            continue;                    // Continua para a próxima iteração.
        }

        if (msg.type == ACTION_RESET) { // Cliente solicita resetar o jogo.
            initialize_game(game);       // Re-inicializa o estado do jogo.
            printf("starting new game\n");
            send_update(client_fd, game); // Envia a atualização do jogo para o cliente.
            game_over = 0;               // Reseta o estado de game_over.
            continue;                    // Continua para a próxima iteração.
        }

        if (msg.type == ACTION_EXIT) { // Cliente solicita encerrar a conexão.
            printf("client disconnected\n");
            close(client_fd);          // Fecha o socket do cliente.
            return;                    // Sai da função handle_client.
        }

        // Após o jogo terminar, apenas processa reset ou exit.
        if (game_over) {
            if (msg.type == ACTION_RESET || msg.type == ACTION_EXIT) {
                // Comandos reset ou exit já são tratados acima.
                continue;
            } else {
                // Ignora outros comandos e envia uma mensagem vazia.
                send_nothing(client_fd);
                continue;
            }
        }

        // Processa comandos enquanto o jogo está em andamento.
        else if (msg.type == ACTION_MOVE) { // Cliente realiza um movimento.
            MoveType direction = msg.moves[0];      // Obtém a direção do movimento.
            int new_x = game->player_x;        // Nova posição X do jogador.
            int new_y = game->player_y;        // Nova posição Y do jogador.
            int old_x = game->player_x;        // Posição X anterior do jogador.
            int old_y = game->player_y;        // Posição Y anterior do jogador.

            // Atualiza a posição do jogador com base na direção.
            switch (direction) {
                case MOVE_UP: new_x--; break;    // Move para cima.
                case MOVE_RIGHT: new_y++; break; // Move para a direita.
                case MOVE_DOWN: new_x++; break;  // Move para baixo.
                case MOVE_LEFT: new_y--; break;  // Move para a esquerda.
            }

            // Atualiza a posição do jogador no estado do jogo.
            game->player_x = new_x;
            game->player_y = new_y;

            // Atualiza o estado do jogo na posição anterior do jogador.
            game->game_state[old_x][old_y] = game->maze[old_x][old_y];

            // Revela as células ao redor da nova posição do jogador.
            reveal_cells(game);

            // Marca a nova posição do jogador no estado do jogo.
            game->game_state[new_x][new_y] = 5; // 5 representa o jogador.

            // Verifica se o jogador alcançou a saída.
            if(game->player_x == game->exit_x && game->player_y == game->exit_y) {
                send_win(client_fd, game); // Envia a mensagem de vitória para o cliente.
                game_over = 1;             // Define game_over como verdadeiro.
                continue;                  // Continua para a próxima iteração.
            }

            // Envia a atualização do estado do jogo para o cliente.
            send_update(client_fd, game);
        }
        else if(msg.type == ACTION_MAP) { // Cliente solicita o mapa do jogo.
            send_map(client_fd, game);       // Envia o mapa para o cliente.
        }
        else if(msg.type == ACTION_HINT) { // Cliente solicita uma dica.
            send_hint(client_fd, game);      // Envia a dica para o cliente.
        }
    }

    // Se a conexão for encerrada ou ocorrer um erro, fecha o socket.
    close(client_fd);
}

/**
 * Função principal do servidor. Configura o socket, lê o labirinto e
 * aguarda conexões de clientes.
 *
 * @param argc Número de argumentos da linha de comando.
 * @param argv Vetor de argumentos da linha de comando.
 * @return Retorna 0 em caso de execução bem-sucedida.
 */
int main(int argc, char *argv[]) {
    // Verifica se os argumentos fornecidos são suficientes.
    if(argc != 5) {
        fprintf(stderr, "Uso: %s <v4|v6> <porta> -i <arquivo_labirinto>\n", argv[0]);
        exit(1);
    }

    char *ip_version = argv[1];    // Versão do IP (v4 ou v6).
    char *port = argv[2];           // Porta para escutar.
    char *input_flag = argv[3];     // Flag de entrada (espera-se "-i").
    char *maze_file = argv[4];      // Arquivo que contém o labirinto.

    // Verifica se a flag de entrada está correta.
    if(strcmp(input_flag, "-i") != 0) {
        fprintf(stderr, "Uso: %s <v4|v6> <porta> -i <arquivo_labirinto>\n", argv[0]);
        exit(1);
    }

    Game game;                       // Estrutura para armazenar o estado do jogo.
    memset(&game, 0, sizeof(game));  // Inicializa a estrutura com zeros.

    read_maze(maze_file, &game);     // Lê o labirinto a partir do arquivo.

    int listen_fd = setup_server_socket(ip_version, port); // Configura o socket de escuta.

    // Loop infinito para aceitar conexões de clientes.
    while(1) {
        struct sockaddr_storage client_addr; // Estrutura para armazenar o endereço do cliente.
        socklen_t addr_size = sizeof(client_addr); // Tamanho do endereço.
        int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &addr_size); // Aceita a conexão.

        printf("client connected\n"); // Informa que um cliente se conectou.
        handle_client(client_fd, &game); // Lida com as interações com o cliente.
    }

    close(listen_fd); // Fecha o socket de escuta (nunca alcançado neste loop infinito).
    return 0;         // Retorna 0 para indicar sucesso.
}
