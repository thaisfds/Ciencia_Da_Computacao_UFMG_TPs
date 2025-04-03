#include "common.h"

#define BUFSZ 1024
int venceu;
int comecou;

void usage (int argc, char **argv){
    printf("usage: %s <server IP> <server port>", argv[0]);
    printf("example: %s 127.0.0.1 51511", argv[0]);
    exit(EXIT_FAILURE);
}

// ==============================================
// ============= FUNÇÕES AUXILIARES =============
// ==============================================

//imprimir possiveis movimentos
void print_moves(struct action *act){
    int i = 0;
    while (act->moves[i] != 0) {
        if (act->moves[i] == 1){ printf("up"); } 
        else if (act->moves[i] == 2){ printf("right"); } 
        else if (act->moves[i] == 3){ printf("down"); } 
        else if (act->moves[i] == 4){ printf("left"); }

        if(act->moves[i+1] != 0){ printf(", ");}
        else{printf(".");}
        i++;
    }
    printf("\n");
}

//imprimir labirinto do jogador
void map(struct action *act) {
    // Percorrer o labirinto (armazenado em act->board) e imprimir a visão do jogador
    int fim = 0;
    int chegou_no_fim = 0;

    for (int i = 0; i < 10; i++) {
        int tamanho_maximo = 0;
        for (int j = 0; j < 10; j++) {
            tamanho_maximo++;
            if(act->board[i][j] == 0){ printf("#\t"); } 
            else if(act->board[i][j] == 1){ printf("_\t"); } 
            else if(act->board[i][j] == 2){ printf(">\t"); } 
            else if(act->board[i][j] == 3){ printf("X\t"); } 
            else if(act->board[i][j] == 4){ printf("?\t"); } 
            else if(act->board[i][j] == 5){ printf("+\t"); } 
            else{
                tamanho_maximo--;
                if(chegou_no_fim == 0){
                    chegou_no_fim = 1;
                    fim = j;
                }
                j = 10;
            }
        }
        if (i < fim || tamanho_maximo == 10){ printf("\n"); }
        else{ i = 10; }
    }
}

//Adiciona em action o movimento do jogador
void move(struct action *act, const char *direction) {
    if (strcmp(direction, "up") == 0) { act->moves[0] = 1; } 
    else if (strcmp(direction, "right") == 0) { act->moves[0] = 2; } 
    else if (strcmp(direction, "down") == 0) { act->moves[0] = 3;  } 
    else if (strcmp(direction, "left") == 0) { act->moves[0] = 4; } 
    else { act->moves[0] = 0; }
}

//Fim de jogo
void win(struct action *act) {
    printf("You escaped!\n");
    map(act);
    venceu = 1;
}

//Atualiza o estado do jogo de acordo com a resposta do servidor
void update(struct action *act, int client_command) {
    switch (client_command) {
        case 0: // Start
            comecou = 1;
            printf("Possible moves: ");
            print_moves(act);
            break;
        case 1: // Move
        printf("Possible moves: ");
            print_moves(act);
            break;
        case 2: // Map
            map(act);
            break;
        case 3: // Hint
            printf("Hint: ");
            print_moves(act);
            break;
        case 6: // Reset
            venceu = 0; // Resetar o estado global
            printf("Possible moves: ");
            print_moves(act);
            break;
        default:
            printf("Invalid Update received: %d\n", act->type);
            break;
    }
    
}

//analisa se o movimento é valido de acordo com a resposta do servidor
int validar_movimento(struct action *act, int *movimento){
    for (int i = 0; i < 4; i++){
        if (act->moves[0] == movimento[i]){
            return 1;
        }
    }
    return 0;
}


// ==============================================
// ==================== MAIN ====================
// ==============================================

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != addrparse(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    //socket TCP
    int s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }

    //Conecatar ao servidor
    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != connect(s, addr, sizeof(storage))) {
        logexit("connect");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);

    char buf[BUFSZ];
    memset(buf, 0, BUFSZ);

    //variáveis para controle do fluxo do jogo
    venceu = 0;
    comecou = 0;
    int movimentos_valido[4];
    for (int i = 0; i < 4; i++){
        movimentos_valido[i] = 0;
    }
    int valido = 0;

    //inicio do loop de comunicação
    while (1) {
        //leitura do terminal
        fgets(buf, BUFSZ - 1, stdin);
        buf[strcspn(buf, "\n")] = '\0';

        struct action act;
        memset(&act, 0, sizeof(act));

        //tratamento inicial da entrada do terminal
        if (strcmp(buf, "start") == 0 && !venceu && !comecou) {
            act.type = 0;
            comecou = 1;
        } else if ((strcmp(buf, "up") == 0 || strcmp(buf, "right") == 0 || strcmp(buf, "down") == 0 || strcmp(buf, "left") == 0) && !venceu && comecou) { //move
            act.type = 1;
            move(&act, buf); // Atualizar o vetor de movimentos
        } else if (strcmp(buf, "map") == 0 && !venceu && comecou) {
            act.type = 2;
        } else if (strcmp(buf, "hint") == 0 && !venceu && comecou) {
            act.type = 3;
        } else if (strcmp(buf, "reset") == 0) {
            act.type = 6;
        } else if (strcmp(buf, "exit") == 0) {
            act.type = 7;
        } else {
            //trata os dois tipos de erros possiveis
            if (
            strcmp(buf, "up") == 0 ||
            strcmp(buf, "right") == 0 ||
            strcmp(buf, "down") == 0 ||
            strcmp(buf, "left") == 0 ||
            strcmp(buf, "map") == 0 ||
            strcmp(buf, "hint") == 0){
                if(comecou == 0){
                    printf("error: start the game first\n");
                } 
                else if (venceu){
                    continue;
                }
            } else if (strcmp(buf, "start") == 0){
                continue;
            } else {
                printf("error: command not found\n");
            }
        }

        //tratamento de erro, se receber um move é necessário validar o movimento
        if(act.type == 1 ){ valido = validar_movimento(&act, movimentos_valido); } 
        else{ valido = 0; }

        //analisar se envia a mensagem para o servidor ou não
        if(act.type == 1 && valido == 0){
            printf("error: you cannot go this way\n");
            continue;
        } else if   ((venceu && (act.type != 6 && act.type != 7)) || 
                    (comecou == 0 && (  strcmp(buf, "up") == 0 ||
                                        strcmp(buf, "right") == 0 ||
                                        strcmp(buf, "down") == 0 ||
                                        strcmp(buf, "left") == 0 ||
                                        strcmp(buf, "hint") == 0 ||
                                        strcmp(buf, "map") == 0))){
            continue;
        }else if (act.type == 0  && comecou == 0){
            continue; //comando invalido antes do start
        }else{
            //enviar comando para o servidor
            int comando_enviado = act.type; //armazena o ultimo comando enviado para caso a mensagem atual não possa ser enviada
            size_t count = send(s, &act, sizeof(act), 0);
            if (count != sizeof(act)) {
                logexit("send");
            }

            //se o comando for exit, encerrar o programa
            if (act.type == 7) {
                break;
            }else{
                //se não, receber resposta do servidor
                size_t recv_count = recv(s, &act, sizeof(act), 0);
                if (recv_count == 0) {
                    perror("Erro ao receber resposta");
                    break;
                }

                //se for um update ou reset, atualizar o estado do jogo
                if (act.type == 4) {
                    update(&act, comando_enviado);
                    if(comando_enviado == 0 || comando_enviado == 1 || comando_enviado == 6){
                        for (int i = 0; i < 4; i++){
                            movimentos_valido[i] = act.moves[i];
                        }
                    }
                }

                //se for win, encerrar o jogo e espera o comando reset ou exit
                if (act.type == 5) {
                    win(&act);
                }
            }
        }
    }
    
    //encerrar o socket
    close(s);
    exit(EXIT_SUCCESS);
}
