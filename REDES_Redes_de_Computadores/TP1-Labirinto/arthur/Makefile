CC = gcc
CFLAGS = -Wall -O2
BIN_DIR = bin

all: $(BIN_DIR)/server $(BIN_DIR)/client

$(BIN_DIR)/server: server.c common.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/server server.c

$(BIN_DIR)/client: client.c common.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/client client.c

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(BIN_DIR)/server $(BIN_DIR)/client
