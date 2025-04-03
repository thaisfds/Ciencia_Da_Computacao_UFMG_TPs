# Compilador e flags
CC = gcc
CFLAGS = -Wall -g

# Diretórios
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

# Arquivos fonte
SERVER_SRC = $(SRC_DIR)/server.c
CLIENT_SRC = $(SRC_DIR)/client.c
BIB_SRC = $(SRC_DIR)/bib.c

# Arquivos objeto
SERVER_OBJ = $(OBJ_DIR)/server.o
CLIENT_OBJ = $(OBJ_DIR)/client.o
BIB_OBJ = $(OBJ_DIR)/bib.o

# Executáveis
SERVER_EXEC = $(BIN_DIR)/server
CLIENT_EXEC = $(BIN_DIR)/client

# Regra padrão
all: $(BIN_DIR) $(OBJ_DIR) $(SERVER_EXEC) $(CLIENT_EXEC)

# Regra para criar o diretório bin se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regra para criar o diretório obj se não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Regra para compilar o servidor
$(SERVER_EXEC): $(SERVER_OBJ) $(BIB_OBJ)
	$(CC) $(CFLAGS) -o $@ $(SERVER_OBJ) $(BIB_OBJ)

# Regra para compilar o cliente
$(CLIENT_EXEC): $(CLIENT_OBJ) $(BIB_OBJ)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_OBJ) $(BIB_OBJ)

# Regra para compilar arquivos .c em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para executar o servidor
server: $(SERVER_EXEC)
	./$(SERVER_EXEC) v4 51511 -i inputs/in.txt

# Regra para executar o cliente
client: $(CLIENT_EXEC)
	./$(CLIENT_EXEC) 127.0.0.1 51511

# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJ_DIR)/*.o $(SERVER_EXEC) $(CLIENT_EXEC)

# Regra para executar Valgrind no servidor
valgrind-server: $(SERVER_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(SERVER_EXEC) v4 51511 -i inputs/in.txt

# Regra para executar Valgrind no cliente
valgrind-client: $(CLIENT_EXEC)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(CLIENT_EXEC) 127.0.0.1 51511

# Phony targets
.PHONY: all server client clean valgrind-server valgrind-client