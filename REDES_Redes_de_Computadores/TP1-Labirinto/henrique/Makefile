# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = src
BIN_DIR = bin
INPUT_DIR = input

# Alvo padrão (compila tudo)
all: $(BIN_DIR)/server $(BIN_DIR)/client

# Compilar o servidor
$(BIN_DIR)/server: $(SRC_DIR)/server.c $(SRC_DIR)/game_logic.c $(SRC_DIR)/protocol.h $(SRC_DIR)/game_logic.h
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/server.c $(SRC_DIR)/game_logic.c

# Compilar o cliente
$(BIN_DIR)/client: $(SRC_DIR)/client.c $(SRC_DIR)/game_logic.c $(SRC_DIR)/protocol.h $(SRC_DIR)/game_logic.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/client.c $(SRC_DIR)/game_logic.c


# Limpeza de arquivos binários
clean:
	rm -rf $(BIN_DIR)/*

# Regra para rodar o servidor
run-server: $(BIN_DIR)/server
	./$(BIN_DIR)/server v4 8080 -i $(INPUT_DIR)/in.txt

# Regra para rodar o cliente
run-client: $(BIN_DIR)/client
	./$(BIN_DIR)/client 127.0.0.1 8080
