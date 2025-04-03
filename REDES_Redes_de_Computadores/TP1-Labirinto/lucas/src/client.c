#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "bib.h"

#define BUFSZ 1024

void usage(int argc, char **argv) {
	fprintf(stderr, "Uso: %s <server_ip> <port>\n", argv[0]);
	exit(EXIT_FAILURE);
}

void imprime_movimentos(int *moves, int *possiveis_movimentos, int hint){
	if(hint) printf("Hint: ");
	else printf("Possible moves: ");
	for(int i=0; moves[i] != 0; i++){
		switch(moves[i]){
			case (enum Move)UP:
				printf("up");
				possiveis_movimentos[0] = 1;
				break;
			case (enum Move)RIGHT:
				printf("right");
				possiveis_movimentos[1] = 1;
				break;
			case (enum Move)DOWN:
				printf("down");
				possiveis_movimentos[2] = 1;
				break;
			case (enum Move)LEFT:
				printf("left");
				possiveis_movimentos[3] = 1;
				break;
		}
		if(moves[i+1] != 0) printf(", ");
		else printf(".\n");
	}
}

int is_a_valid_move(int *moves, char *buf, int *possiveis_movimentos){
	if(strcmp(buf, "up\n") == 0){
		if(possiveis_movimentos[0]) return (enum Move)UP;
		else return -1;
	}
	else if(strcmp(buf, "right\n") == 0){
		if(possiveis_movimentos[1]) return (enum Move)RIGHT;
		else return -1;
	}
	else if(strcmp(buf, "down\n") == 0){
		if(possiveis_movimentos[2]) return (enum Move)DOWN;
		else return -1;
	}
	else if(strcmp(buf, "left\n") == 0){
		if(possiveis_movimentos[3]) return (enum Move)LEFT;
		else return -1;
	}
	else return 0;
}

void imprime_mapa(int board[10][10]){
	char *tiles = {"#_>X?+"};

	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			if(board[i][j] == (enum Labirinto)LIMITE) break;
			printf("%c\t", tiles[board[i][j]]);
		}
		if (board[i][0] != (enum Labirinto)LIMITE) printf("\n");
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	if (argc < 3) usage(argc, argv);

	struct sockaddr_storage server_storage;
	if (addrparse(argv[1], argv[2], &server_storage) != 0) usage(argc, argv);

	int s = socket(server_storage.ss_family, SOCK_STREAM, 0);
	if (s == -1) logexit("socket");

	struct sockaddr* addr = (struct sockaddr *)&server_storage;
	if (connect(s, addr, sizeof(server_storage)) != 0) logexit("connect");

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	// printf("[log] Connected to %s\n", addrstr);

	action_t *act = (action_t *)malloc(sizeof(action_t));
	memset(act, 0, sizeof(action_t));

	char buf[BUFSZ];
	
	while(1){
		memset(buf, 0, BUFSZ);
		fgets(buf, BUFSZ, stdin);
		if(strcmp(buf, "start\n") == 0){
			break;
		}
		printf("error: start the game first\n");
	}

	act->type = START;
	size_t count = send(s, act, sizeof(action_t), 0);
	if (count != sizeof(action_t)) logexit("send");

	int game_on = 1;

	count = recv(s, act, sizeof(action_t), 0);
	if (count != sizeof(action_t)) logexit("recv");

	int hint = 0;

	while(game_on){
		int possiveis_movimentos[4] = {0, 0, 0, 0};
		if (act->type != (enum Type)WIN) imprime_movimentos(act->moves, possiveis_movimentos, hint);
		hint = 0;
		
		memset(buf, 0, BUFSZ);
		fgets(buf, BUFSZ, stdin);

		if(act->type == (enum Type)WIN){
			if(strcmp(buf, "reset\n") && strcmp(buf, "exit\n")){
				// fprintf(stderr, "error: only reset or exit\n");
				continue;
			}
		}

		int move;
		if((move = is_a_valid_move(act->moves, buf, possiveis_movimentos))){
			if (move == -1){
				printf("error: you cannot go this way\n");
				continue;
			}
			act->type = MOVE;
			act->moves[0] = move;
		}

		else if(strcmp(buf, "map\n") == 0){
			imprime_mapa(act->board);
			act->type = MAP;
		}

		else if(strcmp(buf, "hint\n") == 0){
			act->type = HINT;
			hint = 1;
		}

		else if(strcmp(buf, "reset\n") == 0){
			act->type = RESET;
		}

		else if(strcmp(buf, "exit\n") == 0){
			act->type = EXIT;
			game_on = 0;
		}

		else{
			printf("error: command not found\n");
			continue;
		}
		
		count = send(s, act, sizeof(action_t), 0);
		if (count != sizeof(action_t)) logexit("send");

		if(game_on == 0) break;
		count = recv(s, act, sizeof(action_t), 0);
		if (count != sizeof(action_t)) logexit("recv");

		// printf("[log] jogada recebida: %d\n", act->type);

		if(act->type == WIN){
			printf("You escaped!\n");
			imprime_mapa(act->board);
		}
	}

	close(s);

	free(act);
	
	return EXIT_SUCCESS;
}