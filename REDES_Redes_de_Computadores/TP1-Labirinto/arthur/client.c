// Este é o cliente do jogo de labirinto. Ele permite que o usuário interaja com o servidor,
// envie comandos e visualize o estado do jogo.

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

// Prototipação das funções utilizadas no cliente.
int setup_client_socket(const char *ip, const char *port);
const char* move_to_string(MoveType move);
void display_possible_moves(MoveType *moves);
void display_map(int board[MAX_SIZE][MAX_SIZE], int rows, int cols);
void display_hint(MoveType *moves);
void send_action(int sockfd, struct action *msg);
int all_moves_zero(MoveType *moves);
void handle_response(struct action *response, MoveType *current_possible_moves);
int is_move_possible(MoveType move, MoveType *current_possible_moves);

// Flag para indicar se o jogo foi vencido.
int game_won = 0;

/**
 * Função principal do cliente. Conecta ao servidor, lê comandos do usuário e interage com o servidor.
 *
 * @param argc Número de argumentos da linha de comando.
 * @param argv Vetor de argumentos da linha de comando.
 * @return Retorna 0 em caso de execução bem-sucedida.
 */
int main(int argc, char *argv[]) {
    // Verifica se os argumentos fornecidos são suficientes.
    if(argc != 3) {
        fprintf(stderr, "Uso: %s <IP_servidor> <porta>\n", argv[0]);
        exit(1);
    }

    char *server_ip = argv[1]; // Endereço IP do servidor.
    char *port = argv[2];      // Porta do servidor.

    int sockfd = setup_client_socket(server_ip, port); // Configura o socket do cliente.

    struct action msg;           // Estrutura para a mensagem a ser enviada.
    memset(&msg, 0, sizeof(msg)); // Inicializa a estrutura com zeros.

    char input[100];             // Buffer para armazenar a entrada do usuário.
    int game_started = 0;        // Flag para indicar se o jogo foi iniciado.

    // Estrutura para armazenar os movimentos possíveis atuais.
    MoveType current_possible_moves[MAX_MOVES];
    memset(current_possible_moves, 0, sizeof(current_possible_moves));

    // Loop principal para ler comandos do usuário.
    while(1) {
        printf("> ");             // Prompt para o usuário.
        fflush(stdout);          // Garante que o prompt seja exibido imediatamente.
        if(fgets(input, sizeof(input), stdin) == NULL) {
            break; // Sai do loop se não houver mais entrada.
        }

        // Remove o caractere de nova linha da entrada.
        input[strcspn(input, "\n")] = 0;

        // Processa o comando "start" para iniciar um novo jogo.
        if(strcmp(input, "start") == 0) {
            msg.type = ACTION_START; // Define o tipo da ação como iniciar.
            send_action(sockfd, &msg); // Envia a ação para o servidor.
            game_started = 1;           // Define que o jogo foi iniciado.
            memset(current_possible_moves, 0, sizeof(current_possible_moves)); // Reseta os movimentos possíveis.
        }

        // Se o jogo ainda não foi iniciado, exibe uma mensagem de erro.
        else if(game_started == 0) {
            printf("error: start the game first\n");
            continue; // Continua para a próxima iteração.
        }

        // Processa o comando "reset" para reiniciar o jogo.
        else if(strcmp(input, "reset") == 0) {
            msg.type = ACTION_RESET; // Define o tipo da ação como resetar.
            send_action(sockfd, &msg); // Envia a ação para o servidor.
            game_won = 0;               // Reseta a flag de vitória.
            memset(current_possible_moves, 0, sizeof(current_possible_moves)); // Reseta os movimentos possíveis.
        }

        // Processa o comando "exit" para encerrar a conexão.
        else if(strcmp(input, "exit") == 0) {
            msg.type = ACTION_EXIT; // Define o tipo da ação como sair.
            send_action(sockfd, &msg); // Envia a ação para o servidor.
            break; // Sai do loop principal.
        }

        // Processa o comando "map" para solicitar o mapa do jogo.
        else if(strcmp(input, "map") == 0) {
            msg.type = ACTION_MAP; // Define o tipo da ação como mapa.
            send_action(sockfd, &msg); // Envia a ação para o servidor.
        }

        // Processa o comando "hint" para solicitar uma dica de movimento.
        else if(strcmp(input, "hint") == 0) {
            msg.type = ACTION_HINT; // Define o tipo da ação como dica.
            send_action(sockfd, &msg); // Envia a ação para o servidor.
        }

        // Processa comandos de movimento: "up", "right", "down", "left".
        else if(strcmp(input, "up") == 0 || strcmp(input, "right") == 0 ||
                strcmp(input, "down") == 0 || strcmp(input, "left") == 0) {
            MoveType requested_move; // Variável para armazenar o movimento solicitado.

            // Converte o comando de string para o tipo MoveType correspondente.
            if(strcmp(input, "up") == 0) {
                requested_move = MOVE_UP;
            }
            else if(strcmp(input, "right") == 0) {
                requested_move = MOVE_RIGHT;
            }
            else if(strcmp(input, "down") == 0) {
                requested_move = MOVE_DOWN;
            }
            else { // "left"
                requested_move = MOVE_LEFT;
            }

            // Verifica se o movimento solicitado está entre os movimentos possíveis.
            if(!is_move_possible(requested_move, current_possible_moves) && !game_won) {
                printf("error: you cannot go this way\n"); // Exibe mensagem de erro.
                continue; // Continua para a próxima iteração.
            }

            // Se o movimento for possível, define o tipo da ação e envia para o servidor.
            msg.type = ACTION_MOVE;        // Define o tipo da ação como movimento.
            msg.moves[0] = requested_move; // Armazena o movimento solicitado.
            send_action(sockfd, &msg);      // Envia a ação para o servidor.
        }

        // Se o comando não for reconhecido, exibe uma mensagem de erro.
        else {
            printf("error: command not found\n");
            continue; // Continua para a próxima iteração.
        }

        // Recebe a resposta do servidor após enviar uma ação.
        struct action response;                // Estrutura para armazenar a resposta.
        memset(&response, 0, sizeof(response)); // Inicializa a estrutura com zeros.
        ssize_t bytes_received = recv(sockfd, &response, sizeof(response), 0); // Recebe a mensagem.

        // Verifica se a conexão foi encerrada pelo servidor.
        if(bytes_received <= 0) {
            printf("Conexão encerrada pelo servidor.\n");
            break; // Sai do loop principal.
        }

        // Trata a resposta recebida do servidor e atualiza os movimentos possíveis.
        handle_response(&response, current_possible_moves);
    }

    close(sockfd); // Fecha o socket do cliente.
    return 0;      // Retorna 0 para indicar sucesso.
}

/**
 * Função para configurar o socket do cliente e conectar ao servidor.
 *
 * @param ip Endereço IP do servidor.
 * @param port Porta do servidor.
 * @return Retorna o descritor do socket conectado.
 */
int setup_client_socket(const char *ip, const char *port) {
    struct addrinfo hints, *res, *p;
    int status, sockfd;

    memset(&hints, 0, sizeof hints); // Zera a estrutura hints.
    hints.ai_family = AF_UNSPEC;     // Permite IPv4 ou IPv6.
    hints.ai_socktype = SOCK_STREAM; // Define tipo de socket como TCP.

    // Obtém as informações de endereço para o servidor.
    if((status = getaddrinfo(ip, port, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo erro: %s\n", gai_strerror(status));
        exit(1);
    }

    // Itera sobre os resultados e tenta conectar.
    for(p = res; p != NULL; p = p->ai_next) {
        // Cria o socket.
        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("Erro ao criar socket");
            continue; // Tenta o próximo endereço.
        }

        // Tenta conectar ao servidor.
        if(connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            perror("Erro no connect");
            close(sockfd); // Fecha o socket em caso de erro.
            continue;       // Tenta o próximo endereço.
        }

        break; // Sai do loop se a conexão for bem-sucedida.
    }

    // Verifica se a conexão foi bem-sucedida.
    if(p == NULL) {
        fprintf(stderr, "Falha em conectar ao servidor\n");
        exit(2);
    }

    freeaddrinfo(res); // Libera a estrutura de endereços.
    return sockfd;     // Retorna o descritor do socket conectado.
}

/**
 * Função para converter um movimento do tipo MoveType para sua representação em string.
 *
 * @param move Tipo de movimento (MoveType).
 * @return Retorna uma string representando o movimento.
 */
const char* move_to_string(MoveType move) {
    switch(move) {
        case MOVE_UP: return "up";
        case MOVE_RIGHT: return "right";
        case MOVE_DOWN: return "down";
        case MOVE_LEFT: return "left";
        default: return "";
    }
}

/**
 * Função para exibir os movimentos possíveis disponíveis para o jogador.
 *
 * @param moves Array de movimentos possíveis.
 */
void display_possible_moves(MoveType *moves) {
    printf("Possible moves: ");
    int first = 1; // Flag para formatação da saída.
    for(int i = 0; i < MAX_MOVES && moves[i] != 0; i++) {
        if(!first) {
            printf(", ");
        }
        printf("%s", move_to_string(moves[i])); // Converte o movimento para string e exibe.
        first = 0;
    }
    printf(".\n");
}

/**
 * Função para exibir o mapa do labirinto.
 *
 * @param board Matriz que representa o estado do labirinto.
 * @param rows Número de linhas no labirinto.
 * @param cols Número de colunas no labirinto.
 */
void display_map(int board[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(board[i][j] == -1) {
                // Célula não utilizada, exibe espaço.
                printf(" \t");
                continue;
            }
            char c; // Caractere representando o conteúdo da célula.
            switch(board[i][j]) {
                case 0: c = '#'; break; // Parede.
                case 1: c = '_'; break; // Caminho livre.
                case 2: c = '>'; break; // Entrada.
                case 3: c = 'X'; break; // Saída.
                case 4: c = '?'; break; // Célula desconhecida.
                case 5: c = '+'; break; // Jogador.
                default: c = ' ';       // Outros casos.
            }
            printf("%c\t", c); // Exibe o caractere seguido de uma tabulação.
        }
        printf("\n"); // Nova linha após cada linha do labirinto.
    }
}

/**
 * Função para exibir uma dica de movimento para o jogador.
 *
 * @param moves Array de movimentos que formam a dica.
 */
void display_hint(MoveType *moves) {
    printf("Hint: ");
    int first = 1; // Flag para formatação da saída.
    for(int i = 0; i < MAX_MOVES && moves[i] != 0; i++) {
        if(!first) {
            printf(", ");
        }
        printf("%s", move_to_string(moves[i])); // Converte o movimento para string e exibe.
        first = 0;
    }
    printf(".\n");
}

/**
 * Função para enviar uma ação para o servidor.
 *
 * @param sockfd Descritor do socket conectado ao servidor.
 * @param msg Ponteiro para a estrutura action que representa a ação a ser enviada.
 */
void send_action(int sockfd, struct action *msg) {
    // Envia a estrutura action para o servidor.
    if(send(sockfd, msg, sizeof(*msg), 0) == -1) {
        perror("Erro ao enviar ação"); // Exibe mensagem de erro em caso de falha.
    }
}

/**
 * Função para verificar se todos os movimentos no array são zero.
 *
 * @param moves Array de movimentos a ser verificado.
 * @return Retorna 1 se todos os movimentos forem zero, 0 caso contrário.
 */
int all_moves_zero(MoveType *moves) {
    for(int i = 0; i < MAX_MOVES; i++) {
        if(moves[i] != 0) {
            return 0; // Encontrou um movimento diferente de zero.
        }
    }
    return 1; // Todos os movimentos são zero.
}

/**
 * Função para verificar se um movimento específico está entre os movimentos possíveis.
 *
 * @param move Movimento a ser verificado.
 * @param current_possible_moves Array de movimentos possíveis.
 * @return Retorna 1 se o movimento for possível, 0 caso contrário.
 */
int is_move_possible(MoveType move, MoveType *current_possible_moves) {
    for(int i = 0; i < MAX_MOVES && current_possible_moves[i] != 0; i++) {
        if(current_possible_moves[i] == move) {
            return 1; // Movimento encontrado entre os possíveis.
        }
    }
    return 0; // Movimento não está entre os possíveis.
}

/**
 * Função para tratar a resposta recebida do servidor e atualizar os movimentos possíveis.
 *
 * @param response Ponteiro para a estrutura action que representa a resposta do servidor.
 * @param current_possible_moves Array para armazenar os movimentos possíveis atualizados.
 */
void handle_response(struct action *response, MoveType *current_possible_moves) {
    if(response->type == ACTION_UPDATE) { // Tipo de ação: atualização.
        // Copia os movimentos possíveis da resposta para current_possible_moves.
        memcpy(current_possible_moves, response->moves, sizeof(MoveType) * MAX_MOVES);
        display_possible_moves(current_possible_moves); // Exibe os movimentos possíveis.
    }
    else if(response->type == ACTION_MAP || response->type == ACTION_WIN) { // Tipo de ação: mapa ou vitória.
        // Determina o tamanho do mapa recebendo o número de linhas e colunas válidas.
        int rows = 0, cols = 0;
        for(int i = 0; i < MAX_SIZE; i++) {
            int has_valid_cell = 0;
            for(int j = 0; j < MAX_SIZE; j++) {
                if(response->board[i][j] != -1) {
                    has_valid_cell = 1;
                    if(j + 1 > cols) {
                        cols = j + 1; // Atualiza o número máximo de colunas.
                    }
                }
            }
            if(has_valid_cell) {
                rows++; // Incrementa o número de linhas válidas.
            } else {
                break; // Sai do loop se não houver mais células válidas.
            }
        }

        if(response->type == ACTION_WIN) { // Se o tipo da ação for vitória.
            game_won = 1;                // Define a flag de vitória.
            printf("You escaped!\n");    // Exibe mensagem de vitória.
        }
        
        display_map(response->board, rows, cols); // Exibe o mapa do labirinto.
    }
    else if(response->type == ACTION_HINT) { // Tipo de ação: dica.
        if(!all_moves_zero(response->moves)) { // Verifica se a dica contém movimentos válidos.
            display_hint(response->moves); // Exibe a dica de movimento.
        }
    }
}
