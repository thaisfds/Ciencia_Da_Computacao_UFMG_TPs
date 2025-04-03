#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "bib.h"

#define BUFSZ 1024
#define BOARDSZ 10

typedef struct posicao{
	int lin, col;
} posicao_t;

void usage(int argc, char **argv){
	fprintf(stderr, "Uso: %s <v4|v6> <port> -i <input file>\n", argv[0]);
	exit(EXIT_FAILURE);
}

int** leTabuleiro(char *input_file, posicao_t *posicao_inicial){
	FILE *file = fopen(input_file, "r");
	if(!file) logexit("fopen");

	// inicializa o tabuleiro
	int **tabuleiro = (int **)malloc(BOARDSZ * sizeof(int *));
	for(int i=0; i<BOARDSZ; i++) tabuleiro[i] = (int *)malloc(BOARDSZ * sizeof(int));
	for(int i=0; i<BOARDSZ; i++) for(int j=0; j<BOARDSZ; j++) tabuleiro[i][j] = (enum Labirinto)LIMITE;

	// agora lê o tabuleiro para preencher a matriz
	rewind(file);

	char linha[100];
	int lin = 0;
	while (fgets(linha, sizeof(linha), file)) {
		int col = 0;
		char* token = strtok(linha, "\t");
		while (token) {
			tabuleiro[lin][col] = atoi(token);
			if(tabuleiro[lin][col] == (enum Labirinto)ENTRADA){
				posicao_inicial->lin = lin;
				posicao_inicial->col = col;
			}
			token = strtok(NULL, "\t");
			col++;
		}
		lin++;
    }

	fclose(file);
	return tabuleiro;
}

void revela_posicao(action_t* act, posicao_t pos, int** tabuleiro){
	memset(act->moves, 0, 100 * sizeof(int));
	int next_available_move = 0;

	// Revela a posição atual
	act->board[pos.lin][pos.col] = (enum Labirinto)JOGADOR;
	
	// Para cada direção, confere se entá dentro dos limites
	// Se sim, revela a posição e, se não é muro, adiciona como possível movimento
	if (pos.lin>0) {
		act->board[pos.lin-1][pos.col] = tabuleiro[pos.lin-1][pos.col];
		if (act->board[pos.lin-1][pos.col] != (enum Labirinto)MURO && act->board[pos.lin-1][pos.col] != (enum Labirinto)LIMITE) {
			act->moves[next_available_move++] = (enum Move)UP;
		}
	}
	
	if (pos.col<BOARDSZ-1) {
		act->board[pos.lin][pos.col+1] = tabuleiro[pos.lin][pos.col+1];
		if (act->board[pos.lin][pos.col+1] != (enum Labirinto)MURO && act->board[pos.lin][pos.col+1] != (enum Labirinto)LIMITE) {
			act->moves[next_available_move++] = (enum Move)RIGHT;
		}
	}

	if (pos.lin<BOARDSZ-1){
		act->board[pos.lin+1][pos.col] = tabuleiro[pos.lin+1][pos.col];
		if (act->board[pos.lin+1][pos.col] != (enum Labirinto)MURO && act->board[pos.lin+1][pos.col] != (enum Labirinto)LIMITE) {
			act->moves[next_available_move++] = (enum Move)DOWN;
		}
	}

	if (pos.col>0) {
		act->board[pos.lin][pos.col-1] = tabuleiro[pos.lin][pos.col-1];
		if (act->board[pos.lin][pos.col-1] != (enum Labirinto)MURO && act->board[pos.lin][pos.col-1] != (enum Labirinto)LIMITE) {
			act->moves[next_available_move++] = (enum Move)LEFT;
		}
	}
}	

void inicializa_jogo(action_t* act, posicao_t inicio, int** tabuleiro){
	act->type = (enum Type)UPDATE;
	for(int i = 0; i < BOARDSZ; i++){
		for(int j = 0; j < BOARDSZ; j++){
			act->board[i][j] = (tabuleiro[i][j] == (enum Labirinto)LIMITE) ? (enum Labirinto)LIMITE : (enum Labirinto)OCULTO;
		}
	}
	revela_posicao(act, inicio, tabuleiro);
	printf("starting new game\n");
}

void atualiza_posicao(enum Move direcao, posicao_t* pos, int** tabuleiro){
	if(direcao == 0) logexit("não tem pra onde ir");

	// Confere se o movimento é válido antes de realizar. Se for um muro, não realiza o movimento
	switch(direcao){
		case (enum Move)UP:
			if(tabuleiro[pos->lin-1][pos->col] == (enum Labirinto)MURO) break;
			pos->lin--;
			break;
		case (enum Move)RIGHT:
			if(tabuleiro[pos->lin][pos->col+1] == (enum Labirinto)MURO) break;
			pos->col++;
			break;
		case (enum Move)DOWN:
			if(tabuleiro[pos->lin+1][pos->col] == (enum Labirinto)MURO) break;
			pos->lin++;
			break;
		case (enum Move)LEFT:
			if(tabuleiro[pos->lin][pos->col-1] == (enum Labirinto)MURO) break;
			pos->col--;
			break;
		default:
			logexit("jogada inválida");
	}
}

void revela_tabuleiro(action_t* act, int** tabuleiro){
	// Quando o jogador ganha, o tabuleiro completo é enviado
	for(int i = 0; i < BOARDSZ; i++){
		for(int j = 0; j < BOARDSZ; j++){
			act->board[i][j] = tabuleiro[i][j];
		}
	}
}

void realiza_movimento(action_t* act, enum Move direcao, posicao_t* pos, int** tabuleiro){
	atualiza_posicao(direcao, pos, tabuleiro);
	revela_posicao(act, *pos, tabuleiro);
	if(tabuleiro[pos->lin][pos->col] == (enum Labirinto)SAIDA){
		act->type = (enum Type)WIN;
		revela_tabuleiro(act, tabuleiro);
	}
}

/// @brief Preenche possiveis_movimentos com 1 (true) nas direções que o jogador pode ir (em sentido horário, iniciando com CIMA)
/// @param tabuleiro tabuleiro completo
/// @param pos posição atual do jogador
/// @param possiveis_movimentos vetor de 4 posições que será preenchido com 1 nas direções possíveis
void encontra_possiveis_movimentos(int **tabuleiro, posicao_t pos, int possiveis_movimentos[4]){
	enum Labirinto vizinho;

	if (pos.lin>0) {
		vizinho = tabuleiro[pos.lin-1][pos.col];
		possiveis_movimentos[0] = (vizinho != (enum Labirinto)MURO && vizinho != (enum Labirinto)LIMITE);
	}
	
	if (pos.col<BOARDSZ-1) {
		vizinho = tabuleiro[pos.lin][pos.col+1];
		possiveis_movimentos[1] = (vizinho != (enum Labirinto)MURO && vizinho != (enum Labirinto)LIMITE);
	}

	if (pos.lin<BOARDSZ-1) {
		vizinho = tabuleiro[pos.lin+1][pos.col];
		possiveis_movimentos[2] = (vizinho != (enum Labirinto)MURO && vizinho != (enum Labirinto)LIMITE);
	}

	if (pos.col>0) {
		vizinho = tabuleiro[pos.lin][pos.col-1];
		possiveis_movimentos[3] = (vizinho != (enum Labirinto)MURO && vizinho != (enum Labirinto)LIMITE);
	}
}

int encontra_caminho_saida_recursivo(enum Type* moves, int** tabuleiro, int** visitados, enum Move direcao, int passo, posicao_t pos_atual){
	if (visitados[pos_atual.lin][pos_atual.col]) return 0;
	visitados[pos_atual.lin][pos_atual.col] = 1;

	if (tabuleiro[pos_atual.lin][pos_atual.col] == (enum Labirinto)SAIDA) {
		moves[passo] = direcao;
		return 1;
	}
	
	int movimentos[4] = {0,0,0,0}, encontrado = 0;
	encontra_possiveis_movimentos(tabuleiro, pos_atual, movimentos);

	if (movimentos[0] && encontra_caminho_saida_recursivo(moves, tabuleiro, visitados, (enum Move)UP, passo+1, (posicao_t){pos_atual.lin-1, pos_atual.col})) encontrado = 1;
	else if (movimentos[1] && encontra_caminho_saida_recursivo(moves, tabuleiro, visitados, (enum Move)RIGHT, passo+1, (posicao_t){pos_atual.lin, pos_atual.col+1})) encontrado = 1;
	else if (movimentos[2] && encontra_caminho_saida_recursivo(moves, tabuleiro, visitados, (enum Move)DOWN, passo+1, (posicao_t){pos_atual.lin+1, pos_atual.col})) encontrado = 1;
	else if (movimentos[3] && encontra_caminho_saida_recursivo(moves, tabuleiro, visitados, (enum Move)LEFT, passo+1, (posicao_t){pos_atual.lin, pos_atual.col-1})) encontrado = 1;

	if (encontrado){
		moves[passo] = direcao;
	}

	return encontrado;
}

void encontra_caminho_saida(enum Type *moves, posicao_t pos, int** tabuleiro){
	int **visitados = (int **)malloc(BOARDSZ * sizeof(int *));
	for(int i=0; i<BOARDSZ; i++) visitados[i] = (int *)malloc(BOARDSZ * sizeof(int));

	for(int i = 0; i < BOARDSZ; i++){
		for(int j = 0; j < BOARDSZ; j++){
			if (tabuleiro[i][j] == (enum Labirinto)LIMITE || tabuleiro[i][j] == (enum Labirinto)MURO) {
				visitados[i][j] = 1;
			} else visitados[i][j] = 0;
		}
	}

	visitados[pos.lin][pos.col] = 1;

	int movimentos[4] = {0,0,0,0};
	for(int i=0; i<4; i++) if (moves[i] != 0) movimentos[moves[i]-1] = 1;

	memset(moves, 0, 100 * sizeof(int));

	if (movimentos[0] && encontra_caminho_saida_recursivo(moves, tabuleiro, visitados, (enum Move)UP, 0, (posicao_t){pos.lin-1, pos.col})) return;
	else if (movimentos[1] && encontra_caminho_saida_recursivo(moves, tabuleiro, visitados, (enum Move)RIGHT, 0, (posicao_t){pos.lin, pos.col+1})) return;
	else if (movimentos[2] && encontra_caminho_saida_recursivo(moves, tabuleiro, visitados, (enum Move)DOWN, 0, (posicao_t){pos.lin+1, pos.col})) return;
	else if (movimentos[3] && encontra_caminho_saida_recursivo(moves, tabuleiro, visitados, (enum Move)LEFT, 0, (posicao_t){pos.lin, pos.col-1})) return;
}

void processa_comando(action_t* act, posicao_t* pos_atual, posicao_t pos_inicial, int** tabuleiro, int* game_on){
	switch(act->type){
		case (enum Type)MOVE:
			realiza_movimento(act, act->moves[0], pos_atual, tabuleiro);
			break;
		case (enum Type)MAP:
			revela_posicao(act, *pos_atual, tabuleiro);
			break;
		case (enum Type)HINT:
			encontra_caminho_saida((enum Type *)act->moves, *pos_atual, tabuleiro);
			break;
		case (enum Type)RESET:
			*pos_atual = pos_inicial;
			inicializa_jogo(act, pos_inicial, tabuleiro);
			break;
		case (enum Type)EXIT:
			*game_on = 0;
			break;
		default:
			logexit("jogada inválida");
	}
}

int main(int argc, char *argv[]) {
	int opt;
	char *input_file = NULL, *ip_version = NULL, *port = NULL;

	while((opt = getopt(argc, argv, "i:")) != -1){
		switch(opt){
			case 'i':
				input_file = optarg;
				break;
			default:
				fprintf(stderr, "opção inválida");
				usage(argc, argv);
		}
	}

	if(optind + 2 != argc) usage(argc, argv);

	ip_version = argv[optind];
	port = argv[optind+1];

	if (strcmp(ip_version, "v4") != 0 && strcmp(ip_version, "v6") != 0) {
        fprintf(stderr, "Erro: versão IP inválida. Use 'v4' ou 'v6'.\n");
        usage(argc, argv);
    }

	posicao_t posicao_inicial, posicao_atual;
	int **tabuleiro = leTabuleiro(input_file, &posicao_atual);
	posicao_inicial = posicao_atual;

	struct sockaddr_storage server_storage;
	if (server_sockaddr_init(ip_version, port, &server_storage) != 0) usage(argc, argv);

	int s = socket(server_storage.ss_family, SOCK_STREAM, 0);
	if (s == -1) logexit("socket");

	int option = 1;
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) != 0) logexit("setsockopt");

	struct sockaddr* server_addr = (struct sockaddr *)&server_storage;
	if(bind(s, server_addr, sizeof(server_storage)) != 0) logexit("bind");

	if(listen(s, 10) != 0) logexit("listen");

	char server_addrstr[BUFSZ];
	addrtostr(server_addr, server_addrstr, BUFSZ);
	// printf("[log] bound em %s, esperando conexão...\n", server_addrstr);

	while(1){
		// conexão
		struct sockaddr_storage client_storage;
		struct sockaddr *client_addr = (struct sockaddr *)(&client_storage);

		socklen_t client_storage_len = sizeof(client_storage);
		int client_socket = accept(s, client_addr, &client_storage_len);
		if (client_socket == -1) logexit("accept");

		char client_addrstr[BUFSZ];
		addrtostr(server_addr, client_addrstr, BUFSZ);
		printf("client connected\n");
		// conectado

		action_t *act = (action_t *)malloc(sizeof(action_t));
		
		// recebe jogada inicial (deve ser start)
		size_t count = recv(client_socket, act, sizeof(action_t), 0);
		if (count != sizeof(action_t)) logexit("recv");
		if(act->type != (enum Type)START) logexit("jogada inválida");
		// jogada inicial recebida
		
		// arruma o tabuleiro para retornar
		inicializa_jogo(act, posicao_inicial, tabuleiro);
		count = send(client_socket, act, sizeof(action_t), 0);
		if (count != sizeof(action_t)) logexit("send");
		// retornou tabuleiro

		// que comece o jogo
		int game_on = 1;
		while(game_on){
			size_t count = recv(client_socket, act, sizeof(action_t), 0);
			if (count != sizeof(action_t)) logexit("recv");
			
			// printf("[log] jogada recebida: %d\n", act->type);

			switch(act->type){
				case (enum Type)MOVE:
					// printf("[log] move %d\n", act->moves[0]);
					atualiza_posicao(act->moves[0], &posicao_atual, tabuleiro);
					revela_posicao(act, posicao_atual, tabuleiro);
					if (tabuleiro[posicao_atual.lin][posicao_atual.col] == (enum Labirinto)SAIDA){
						act->type = (enum Type)WIN;
						revela_tabuleiro(act, tabuleiro);
					}
					break;
				case (enum Type)MAP:
					revela_posicao(act, posicao_atual, tabuleiro);
					break;
				case (enum Type)HINT:
					encontra_caminho_saida((enum Type *)act->moves, posicao_atual, tabuleiro);
					break;
				case (enum Type)RESET:
					posicao_atual = posicao_inicial;
					inicializa_jogo(act, posicao_inicial, tabuleiro);
					break;
				case (enum Type)EXIT:
					posicao_atual = posicao_inicial;
					game_on = 0;
					break;
				default:
					logexit("jogada inválida");
			}

			if (!game_on) break;
			
			if (act->type != (enum Type)WIN) act->type = (enum Type)UPDATE;
			count = send(client_socket, act, sizeof(action_t), 0);
			if (count != sizeof(action_t)) logexit("send");
		}

		close(client_socket);
		printf("client disconnected\n");
	}

	return EXIT_SUCCESS;
}
