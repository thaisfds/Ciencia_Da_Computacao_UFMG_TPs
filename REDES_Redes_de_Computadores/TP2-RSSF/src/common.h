#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//Comunicação entre servidore e cliente
struct sensor_message {
    char type [12]; // temperature, humidity or air_quality
    int coords [2]; //grid 10x10 -> linha e coluna
    float measurement; // valor da medição do sensor
};

void logexit(const char *msg);

int addrparse (const char *addrstr, const char *portstr, struct sockaddr_storage *storage);

void addrtostr (const struct sockaddr *addr, char *str, size_t strsize);

int server_sockaddr_init (const char *proto, const char *portstr, struct sockaddr_storage *storage);