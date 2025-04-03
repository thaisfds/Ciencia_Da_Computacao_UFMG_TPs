#include "common.h"
#define BUFSZ 1024

int labirinto_completo[10][10];
int labirinto_enviado[10][10];
int input[100];
int tamanho_labirinto;
int posicao_jogador[2];
int venceu;
int comecou;

void usage(int argc, char **argv) {
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

// ==============================================
// ============= FUNÇÕES AUXILIARES =============
// ==============================================

//pilha do bfs
typedef struct {
    int x, y;
    int moves[100];
    int contador_de_movimentos;
} Node;

// Limpar visão do jogador
void limpar_area_ao_redor(int x, int y) {
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < tamanho_labirinto && j >= 0 && j < tamanho_labirinto) {
                if (labirinto_enviado[i][j] == 4) {
                    labirinto_enviado[i][j] = labirinto_completo[i][j];
                }
            }
        }
    }
}

void preencher_labirinto(){
    int k = 0;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (i < tamanho_labirinto && j < tamanho_labirinto){
                labirinto_completo[i][j] = input[k];
                labirinto_enviado[i][j] = 4;
                if (labirinto_completo[i][j] == 2){
                    posicao_jogador[0] = i;
                    posicao_jogador[1] = j;
                    labirinto_enviado[i][j] = 5;
                }
                k++;
            } else {
                labirinto_completo[i][j] = 8;
                labirinto_enviado[i][j] = 8;
            }
        }
    }
    limpar_area_ao_redor(posicao_jogador[0], posicao_jogador[1]);
}

void print_labirintos(){
    printf("Labirinto Completo:\n");
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            printf("%d ", labirinto_completo[i][j]);
        }
        printf("\n");
    }

    printf("\nLabirinto Enviado:\n");
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            printf("%d ", labirinto_enviado[i][j]);
        }
        printf("\n");
    }
}

void carregar_labirinto(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo do labirinto");
        exit(EXIT_FAILURE);
    }

    char linha[BUFSZ];
    int tamanho_input = 0;

    // Lê o arquivo e preenche o vetor de entrada
    while (fgets(linha, BUFSZ, file)) {
        char *token = strtok(linha, " \n");
        while (token) {
            if (tamanho_input < 100) { // Garantir que não exceda o limite
                input[tamanho_input++] = atoi(token);
            }
            token = strtok(NULL, " \n");
        }
    }

    fclose(file);

    // Calcular o tamanho do labirinto
    int tamanhos[] = {25, 5, 36, 6, 49, 7, 64, 8, 81, 9, 100, 10};
    for (int i = 0; i < 12; i++) {
        if (tamanho_input == tamanhos[i]) {
            tamanho_labirinto = tamanhos[i + 1];
            break;
        }
    }

    preencher_labirinto();

}

void verificar_movimentos_validos(int x, int y, struct action *acao) {
    // Movimentos possíveis: cima (1), direita (2), baixo (3), esquerda (4)

    // Limpeza do vetor de movimentos
    for (int i = 0; i < 100; i++) {acao->moves[i] = 0;}
    int i = 0;

    // Cima
    if (x > 0 && (labirinto_completo[x - 1][y] == 1 || labirinto_completo[x - 1][y] == 2 || labirinto_completo[x - 1][y] == 3)) {
        acao->moves[i] = 1;
        i++;
    }

    // Direita
    if (y < tamanho_labirinto - 1 && (labirinto_completo[x][y + 1] == 1 || labirinto_completo[x][y + 1] == 2 || labirinto_completo[x][y + 1] == 3)) {
        acao->moves[i] = 2;
        i++;
    }

    // Baixo
    if (x < tamanho_labirinto - 1 && (labirinto_completo[x + 1][y] == 1 || labirinto_completo[x + 1][y] == 2 || labirinto_completo[x + 1][y] == 3)) {
        acao->moves[i] = 3;
        i++;
    }

    // Esquerda
    if (y > 0 && (labirinto_completo[x][y - 1] == 1 || labirinto_completo[x][y - 1] == 2 || labirinto_completo[x][y - 1] == 3)) {
        acao->moves[i] = 4;
    }
}

void enviar_movimentos_validos(struct action *acao) {
    //enviar o labirinto_enviado
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            acao->board[i][j] = labirinto_enviado[i][j];
        }
    }

    // Verifica os movimentos válidos a partir da posição do jogador (posicao_jogador[0], posicao_jogador[1])
    verificar_movimentos_validos(posicao_jogador[0], posicao_jogador[1], acao);
}

void start(struct action *acao) {
    comecou = 1;
    printf("starting new game\n");
    acao->type = 4; // Definir como update
    enviar_movimentos_validos(acao); // Envia os movimentos válidos
}

void reset(struct action *acao) {
    venceu = 0; // Reseta o estado do jogo
    comecou = 1;
    acao->type = 4; // Definir como update

    printf("starting new game\n");
    preencher_labirinto();
    enviar_movimentos_validos(acao); // Envia os movimentos válidos
}

void resetExit() {
    venceu = 0; // Reseta o estado do jogo
    comecou = 1;
    
    printf("client disconnected\n");
    preencher_labirinto();
}

void map(struct action *acao) {
    // Retornar o labirinto_enviado
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            acao->board[i][j] = labirinto_enviado[i][j];
        }
    }

    // Zerando respostas.moves
    for (int i = 0; i < 100; i++) {acao->moves[i] = 0;}
    acao->type = 4; // Definir como update
}

int movimento_valido(int x, int y) {
    // Verifica se a posição está dentro dos limites do labirinto -> invalido
    if (x < 0 || x >= tamanho_labirinto || y < 0 || y >= tamanho_labirinto) {return 0;}
    // Verifica se a posição destino é transitável (1 ou 3) -> valido
    if (labirinto_completo[x][y] == 1 || labirinto_completo[x][y] == 2 || labirinto_completo[x][y] == 3) {return 1;}
    return 0; // Movimento inválido
}

void move(struct action *acao) {
    acao->type = 4; // Definir como update
    int direcao = acao->moves[0]; // O cliente define a direção aqui
    int novo_x = posicao_jogador[0];
    int novo_y = posicao_jogador[1];    

    // Determina a nova posição com base na direção
    switch (direcao) {
        case 1: novo_x -= 1; break; //Cima
        case 2: novo_y += 1; break; //Direita
        case 3: novo_x += 1; break; //Baixo
        case 4: novo_y -= 1; break; //Esquerda
        default: return;
    }

    // Atualiza a posição do jogador
    labirinto_enviado[posicao_jogador[0]][posicao_jogador[1]] = labirinto_completo[posicao_jogador[0]][posicao_jogador[1]];
    labirinto_enviado[novo_x][novo_y] = 5; // Marca a nova posição do jogador
    posicao_jogador[0] = novo_x;
    posicao_jogador[1] = novo_y;

    limpar_area_ao_redor(novo_x, novo_y);

    // Verifica se o jogador chegou à saída
    if (labirinto_completo[novo_x][novo_y] == 3) {
        venceu = 1; // Atualiza o estado global
        acao->type = 5; // Define a mensagem como tipo "win"

        // Revela todo o labirinto
        for (int i = 0; i < tamanho_labirinto; i++) {
            for (int j = 0; j < tamanho_labirinto; j++) {
                labirinto_enviado[i][j] = labirinto_completo[i][j];
            }
        }

    }

    enviar_movimentos_validos(acao);
}

int validar_move_hint(int x, int y, int visitado[10][10]) {
    return x >= 0 && y >= 0 && x < tamanho_labirinto && y < tamanho_labirinto &&
           labirinto_completo[x][y] != 0 && !visitado[x][y];
}

void bfs_hint(int x, int y, int *moves, int *found, int visitado[10][10]) {
    int direcoes[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; //diminui o tamanho do codigo

    // Fila para o BFS
    Node queue[100];
    int inicio_da_fila = 0, final_da_fila = 0;

    // Inicializa a fila
    queue[final_da_fila++] = (Node){x, y, {0}, 0};
    visitado[x][y] = 1;

    while (inicio_da_fila < final_da_fila) {

        Node atual = queue[inicio_da_fila++];
        
        // Saida??
        if (labirinto_completo[atual.x][atual.y] == 3) {
            *found = 1;
            memcpy(moves, atual.moves, atual.contador_de_movimentos * sizeof(int));
            return;
        }

        // Explora as direções possíveis
        for (int i = 0; i < 4; i++) {
            int novo_x = atual.x + direcoes[i][0];
            int novo_y = atual.y + direcoes[i][1];

            if (validar_move_hint(novo_x, novo_y, visitado)) {
                visitado[novo_x][novo_y] = 1;
                Node proximo = atual;
                proximo.x = novo_x;
                proximo.y = novo_y;
                proximo.moves[proximo.contador_de_movimentos++] = i + 1; // Armazena a direção do movimento
                queue[final_da_fila++] = proximo;
            }
        }
    }
}

void hint(struct action *acao) {
    int encontrado = 0;
    int visitado[10][10] = {0};
    for (int i = 0; i < 100; i++) acao->moves[i] = 0;
    
    bfs_hint(posicao_jogador[0], posicao_jogador[1], acao->moves, &encontrado, visitado);
    acao->type = 4;  // Atualiza o tipo da ação

    // Retornar o labirinto_enviado
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            acao->board[i][j] = labirinto_enviado[i][j];
        }
    }
}

void processar_comando(struct action *acao, int csock) {
    if (venceu && acao->type != 6 && acao->type != 7) {
        return;
    }

    switch (acao->type) {
        case 0: // start
            if (comecou == 1) {break;}
            start(acao);
            break;

        case 1: // move
            if (comecou == 0) {break;}
            move(acao);
            break;

        case 2: // map
            if (comecou == 0) {break;}
            map(acao);
            break;

        case 3: // hint
            if (comecou == 0) {break;}
            hint(acao);
            break;

        case 6: // reset
            reset(acao);
            break;

        case 7: // exit
            close(csock);
            resetExit();
            return;

        default:
            break;
    }
}

// ==============================================
// ==================== MAIN ====================
// ==============================================

// Função principal do servidor
int main(int argc, char **argv) {

    if (argc < 5) {
        usage(argc, argv);
    }

    carregar_labirinto(argv[4]); // Carrega o labirinto

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    int s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage))) {
        logexit("bind");
    }

    if (0 != listen(s, 10)) {
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);

    //inicia o loop do servidor
    while (1) {
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(s, caddr, &caddrlen);
        if (csock == -1) {
            logexit("accept");
        }

        char caddrstr[BUFSZ];
        addrtostr(caddr, caddrstr, BUFSZ);
        printf("client connected\n");

        struct action acao;
        memset(&acao, 0, sizeof(acao));

        // Inicializa o estado do jogo
        venceu = 0;
        comecou = 0; 

        // Inicia o loop cliente-servidor
        while (1) {
            //recebe o comando do cliente
            size_t count = recv(csock, &acao, sizeof(acao), 0);
            if (count <= 0 && acao.type != 7) {
                perror("Erro ao receber comando");
                close(csock);
                break;
            }

            //print_resposta(&acao);

            // Processa o comando e envia a resposta
            processar_comando(&acao, csock);

            // Envia a resposta ao cliente se não for "exit"
            //print_resposta(&acao);
            if (acao.type == 7) {
                break;
            } else {
                count = send(csock, &acao, sizeof(acao), 0);
                if (count != sizeof(acao)) {
                    logexit("send");
                }
            }
        }
        close(csock);
    }
    exit(EXIT_SUCCESS);
}