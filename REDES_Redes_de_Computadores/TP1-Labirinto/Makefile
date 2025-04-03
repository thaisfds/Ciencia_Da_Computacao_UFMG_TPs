BIN_DIR = bin
SRC_DIR = src

all: $(BIN_DIR) client server

# Cria o diretório bin, se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compila o código comum (gera o .o dentro de /bin)
$(BIN_DIR)/common.o: $(SRC_DIR)/common.c
	gcc -Wall -c $(SRC_DIR)/common.c -o $(BIN_DIR)/common.o

# Compila o cliente (gera o executável na pasta bin)
client: $(SRC_DIR)/client.c $(BIN_DIR)/common.o
	gcc -Wall $(SRC_DIR)/client.c $(BIN_DIR)/common.o -o $(BIN_DIR)/client

# Compila o servidor (gera o executável na pasta bin)
server: $(SRC_DIR)/server.c $(BIN_DIR)/common.o
	gcc -Wall $(SRC_DIR)/server.c $(BIN_DIR)/common.o -o $(BIN_DIR)/server

clean:
	rm -f $(BIN_DIR)/common.o $(BIN_DIR)/client $(BIN_DIR)/server
	rmdir $(BIN_DIR) 2>/dev/null || true
