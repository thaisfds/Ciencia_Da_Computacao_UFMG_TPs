#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//Comunicação entre servidore e cliente
struct action {
    int type;
    int moves[100];
    int board[10][10];
};

void logexit(const char *msg);

int addrparse (const char *addrstr, const char *portstr, struct sockaddr_storage *storage);

void addrtostr (const struct sockaddr *addr, char *str, size_t strsize);

int server_sockaddr_init (const char *proto, const char *portstr, struct sockaddr_storage *storage);

void print_resposta(struct action *act);


