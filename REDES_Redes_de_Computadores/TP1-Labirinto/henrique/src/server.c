#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "protocol.h"
#include "game_logic.h"

char *input_file;

void handle_client(int client_socket);

int main(int argc, char *argv[]) {
    if (argc != 5 || (strcmp(argv[1], "v4") != 0 && strcmp(argv[1], "v6") != 0)) {
        fprintf(stderr, "Usage: %s <v4|v6> <port> -i <input_file>\n", argv[0]);
        return 1;
    }

    int server_fd, client_socket;
    struct sockaddr_storage address;
    socklen_t addr_len;
    int opt = 1;

    input_file = argv[4];
    int port = atoi(argv[2]);

    // Determina o tipo de socket (IPv4 ou IPv6)
    int family = (strcmp(argv[1], "v4") == 0) ? AF_INET : AF_INET6;

    // Criação do socket
    if ((server_fd = socket(family, SOCK_STREAM, 0)) == -1) {
        perror("Erro ao criar o socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("Erro ao configurar o socket");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Configuração do endereço (IPv4 ou IPv6)
    if (family == AF_INET) {
        struct sockaddr_in addr_v4 = {0};
        addr_v4.sin_family = AF_INET;
        addr_v4.sin_addr.s_addr = INADDR_ANY;
        addr_v4.sin_port = htons(port);

        if (bind(server_fd, (struct sockaddr *)&addr_v4, sizeof(addr_v4)) < 0) {
            perror("Erro no bind IPv4");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
    } else {
        struct sockaddr_in6 addr_v6 = {0};
        addr_v6.sin6_family = AF_INET6;
        addr_v6.sin6_addr = in6addr_any;
        addr_v6.sin6_port = htons(port);

        if (bind(server_fd, (struct sockaddr *)&addr_v6, sizeof(addr_v6)) < 0) {
            perror("Erro no bind IPv6");
            close(server_fd);
            exit(EXIT_FAILURE);
        }
    }

    // Escuta por conexões
    if (listen(server_fd, 1) < 0) {
        perror("Erro no listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("[INFO] Servidor escutando na porta %s em %s\n", argv[2], argv[1]);

    while (1) {
        addr_len = sizeof(address);
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, &addr_len)) < 0) {
            perror("Erro ao aceitar conexão");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        printf("client connected\n");
        load_maze(input_file);
        handle_client(client_socket);
        close(client_socket);
    }

    close(server_fd);
    return 0;
}

void handle_client(int client_socket) {
    Action action;
    int moves[MAX_MOVES];

    while (1) {
        // Lê a mensagem do cliente
        if (recv(client_socket, &action, sizeof(Action), 0) <= 0) {
            perror("[ERROR] Error reading from socket or connection closed");
            return;
        }

        switch (action.type) {
            case 0: // Start
                load_maze(input_file); // Carrega o labirinto do arquivo
                find_player_position(); // Encontra a posição inicial do jogador
                initialize_visible_maze(); // Inicializa o labirinto visível
                update_visible_maze(); // Atualiza o estado visível

                get_possible_moves(moves);
                action.type = 4; // Update
                memcpy(action.moves, moves, sizeof(moves));
                get_visible_maze(action.board); // Preenche o estado visível no Action
                if (send(client_socket, &action, sizeof(Action), 0) <= 0) {
                    perror("[ERROR] Error sending start response to client");
                }
                printf("starting new game\n");
                break;

            case 1: // Move
                // Processa o movimento do jogador
                if (move_player(action.moves[0]) == 2) { // Vitória
                    reveal_full_maze(); // Revela o labirinto completo
                    action.type = 5; // Win
                    get_visible_maze(action.board);
                    if (send(client_socket, &action, sizeof(Action), 0) <= 0) {
                        perror("[ERROR] Error sending win message to client");
                    }
                    printf("[INFO] Player won the game\n");
                    break;
                } else {
                    // Atualiza o labirinto e movimentos
                    update_visible_maze();
                    get_possible_moves(moves);
                    action.type = 4; // Update
                    memcpy(action.moves, moves, sizeof(moves));
                    get_visible_maze(action.board);
                    if (send(client_socket, &action, sizeof(Action), 0) <= 0) {
                        perror("[ERROR] Error sending update message to client");
                    }
                }
                break;

            case 2: // Map
                update_visible_maze(); // Atualiza o estado visível
                action.type = 4;
                get_visible_maze(action.board); // Envia o labirinto visível
                if (send(client_socket, &action, sizeof(Action), 0) <= 0) {
                    perror("[ERROR] Error sending map to client");
                }
                break;

            case 3: // Hint
                calculate_hint(player_x, player_y, maze, moves);
                action.type = 4; // Update
                memcpy(action.moves, moves, sizeof(moves));
                if (send(client_socket, &action, sizeof(Action), 0) <= 0) {
                    perror("[ERROR] Error sending hint to client");
                }
                break;

            case 6: // Reset
                load_maze(input_file); // Recarrega o labirinto do arquivo
                find_player_position(); // Encontra a posição inicial do jogadorS
                initialize_visible_maze(); // Inicializa o labirinto visível
                update_visible_maze();
                get_possible_moves(moves);
                action.type = 4; // Update

                memcpy(action.moves, moves, sizeof(moves));
                get_visible_maze(action.board);

                if (send(client_socket, &action, sizeof(Action), 0) <= 0) {
                    perror("[ERROR] Error sending reset response to client");
                } else {
                    printf("starting new game\n");
                }
                break;

            case 7: // Exit
                printf("client disconnected\n");
                return; // Finaliza a conexão

            default:
                printf("[ERROR] Unknown action type received: %d\n", action.type);
                break;
        }
    }
}
