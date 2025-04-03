#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include <arpa/inet.h>

/// @brief Dados que serão passados entre server e client
/// @param type Tipo de ação, define a comunicação entre server e client
/// @param moves Possíveis movimentos do jogador, sendo 1,2,3,4 para cima, baixo, esquerda e direita respectivamente
/// @param board Tabuleiro do jogo, sendo de 5x5 a 10x10
typedef struct action{
	int type;
	int moves[100];
	int board[10][10];
} action_t;

enum Type{
	START,
	MOVE,
	MAP,
	HINT,
	UPDATE,
	WIN,
	RESET,
	EXIT
};

enum Move{
	UP = 1,
	RIGHT,
	DOWN,
	LEFT
};

enum Labirinto{
	LIMITE = -1,
	MURO,
	CAMINHO,
	ENTRADA,
	SAIDA,
	OCULTO,
	JOGADOR
};

/// @brief Imprime um erro e encerra o programa
/// @param msg Mensagem de erro
void logexit(const char* msg);

/// @brief Converte um endereço e porta para uma estrutura de endereço
/// @param storage Estrutura de endereço que será preenchida
/// @return 0 se sucesso, -1 se erro
int addrparse(const char* addrstr, const char* portstr, struct sockaddr_storage* storage);

/// @brief Converte uma estrutura de endereço para uma string
void addrtostr(const struct sockaddr* addr, char* str, size_t strsize);

/// @brief Inicializa um socket para o servidor
/// @param server_storage Estrutura de endereço que será preenchida
/// @return 0 se sucesso, -1 se erro
int server_sockaddr_init(const char* protocol, const char* portstr, struct sockaddr_storage* server_storage);
