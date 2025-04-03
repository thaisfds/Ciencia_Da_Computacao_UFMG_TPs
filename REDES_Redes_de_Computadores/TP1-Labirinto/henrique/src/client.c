#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "protocol.h"
#include "game_logic.h"

void start_game(int client_fd);
void print_moves(int *moves);
void print_board(int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE]);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        return 1;
    }

    int client_fd;
    int port = atoi(argv[2]);

    // Determina se o IP é IPv4 ou IPv6
    int family = strchr(argv[1], ':') ? AF_INET6 : AF_INET;

    // Criação do socket
    if ((client_fd = socket(family, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar o socket");
        return 1;
    }

    // Configuração do endereço do servidor
    if (family == AF_INET) {
        struct sockaddr_in addr_v4 = {0};
        addr_v4.sin_family = AF_INET;
        addr_v4.sin_port = htons(port);

        if (inet_pton(AF_INET, argv[1], &addr_v4.sin_addr) <= 0) {
            fprintf(stderr, "Endereço IPv4 inválido\n");
            close(client_fd);
            return 1;
        }

        if (connect(client_fd, (struct sockaddr *)&addr_v4, sizeof(addr_v4)) < 0) {
            perror("Erro ao conectar ao servidor IPv4");
            close(client_fd);
            return 1;
        }
    } else {
        struct sockaddr_in6 addr_v6 = {0};
        addr_v6.sin6_family = AF_INET6;
        addr_v6.sin6_port = htons(port);

        if (inet_pton(AF_INET6, argv[1], &addr_v6.sin6_addr) <= 0) {
            fprintf(stderr, "Endereço IPv6 inválido\n");
            close(client_fd);
            return 1;
        }

        if (connect(client_fd, (struct sockaddr *)&addr_v6, sizeof(addr_v6)) < 0) {
            perror("Erro ao conectar ao servidor IPv6");
            close(client_fd);
            return 1;
        }
    }

    start_game(client_fd);
    close(client_fd);
    return 0;
}

void start_game(int client_fd) {
    Action action;
    char command[16];
    int game_started = 0; // Flag para verificar se o jogo foi iniciado
    int game_won = 0;     // Flag para verificar se o jogador venceu

    while (1) {
        printf("> ");
        scanf("%s", command);

        // Valida se o jogo foi iniciado antes de aceitar comandos
        if (!game_started && strcmp(command, "start") != 0) {
            printf("error: start the game first\n");
            continue; // Ignora outros comandos antes do jogo ser iniciado
        }

        // Se o jogo foi vencido, aceita apenas reset ou exit
        if (game_won && strcmp(command, "reset") != 0 && strcmp(command, "exit") != 0) {
            printf("error: only 'reset' or 'exit' are allowed after winning the game\n");
            continue;
        }

        if (strcmp(command, "start") == 0) {
            action.type = 0; // Start
            if (send(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error sending start command\n");
                break;
            }
            if (recv(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error receiving response from server\n");
                break;
            }
            game_started = 1; // Marca que o jogo foi iniciado
            print_moves(action.moves); // Apenas imprime os movimentos possíveis

        } else if (strcmp(command, "up") == 0 || strcmp(command, "down") == 0 ||
                   strcmp(command, "left") == 0 || strcmp(command, "right") == 0) {
            action.type = 1; // Movimento

            // Mapeia o comando para a direção numérica
            if (strcmp(command, "up") == 0) {
                action.moves[0] = 1;
            } else if (strcmp(command, "right") == 0) {
                action.moves[0] = 2;
            } else if (strcmp(command, "down") == 0) {
                action.moves[0] = 3;
            } else if (strcmp(command, "left") == 0) {
                action.moves[0] = 4;
            }

            // Verifica se o movimento é válido com base nos possíveis movimentos
            int valid_move = 0;
            for (int i = 0; i < MAX_MOVES && action.moves[i] != 0; i++) {
                if (action.moves[i] == action.moves[0]) {
                    valid_move = 1;
                    break;
                }
            }

            if (!valid_move) {
                printf("error: you cannot go this way\n");
                continue; // Ignora o comando
            }

            if (send(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error sending move command\n");
                break;
            }
            if (recv(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error receiving response from server\n");
                break;
            }

            if (action.type == 5) { // Win
                printf("You escaped!\n");
                print_board(action.board);
                game_won = 1; // Marca que o jogador venceu
            } else {
                print_moves(action.moves);
            }

        } else if (strcmp(command, "map") == 0) {
            action.type = 2; // Solicita o mapa
            if (send(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error sending map command\n");
                break;
            }
            if (recv(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error receiving map from server\n");
                break;
            }
            print_board(action.board);

        } else if (strcmp(command, "hint") == 0) {
            action.type = 3; // Hint
            if (send(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error sending hint command\n");
                break;
            }
            if (recv(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error receiving hint from server\n");
                break;
            }
            print_moves(action.moves);

        } else if (strcmp(command, "reset") == 0) {
            action.type = 6; // Reset
            if (send(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error sending reset command\n");
                break;
            }
            if (recv(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error receiving reset response\n");
                break;
            }
            print_moves(action.moves); // Apenas imprime os movimentos possíveis
            game_won = 0; // Reinicia o estado do jogo

        } else if (strcmp(command, "exit") == 0) {
            action.type = 7; // Exit
            if (send(client_fd, &action, sizeof(Action), 0) <= 0) {
                printf("Error sending exit command\n");
            }
            printf("Disconnecting from server...\n");
            break;

        } else {
            printf("error: command not found\n");
        }
    }
}

void print_moves(int *moves) {
    printf("Possible moves: ");
    for (int i = 0; i < MAX_MOVES && moves[i] != 0; i++) {
        switch (moves[i]) {
            case 1: printf("up"); break;
            case 2: printf("right"); break;
            case 3: printf("down"); break;
            case 4: printf("left"); break;
            default: printf("unknown"); break;
        }
        if (moves[i + 1] != 0) printf(", ");
    }
    printf(".\n");
}

void print_board(int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE]) {
    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        int empty = 1; // Assume que a linha é vazia
        int first_printed = 0; // Flag para gerenciar espaços entre valores

        for (int j = 0; j < MAX_BOARD_SIZE; j++) {
            if (board[i][j] != -1) {
                empty = 0; // A linha contém pelo menos um valor válido

                // Imprime um espaço antes do valor, exceto para o primeiro elemento válido
                if (first_printed) {
                    printf(" ");
                }

                first_printed = 1; // Marca que já imprimimos pelo menos um valor

                switch (board[i][j]) {
                    case 0: printf("#\t"); break;  // Muro
                    case 1: printf("_\t"); break;  // Caminho livre
                    case 2: printf(">\t"); break;  // Entrada
                    case 3: printf("X\t"); break;  // Saída
                    case 4: printf("?\t"); break;  // Não descoberto
                    case 5: printf("+\t"); break;  // Jogador
                    default: printf("?\t"); break; // Valor desconhecido
                }
                
            }
        }

        // Imprime o \n apenas se a linha não for composta apenas por -1
        if (!empty) {
            printf("\n");
        }
    }
}
