#ifndef DRONE_H
#define DRONE_H

#include"Ponto2D.hpp"

struct Drone{
    double energia = 100, raio, v, th, t;
    int id, n, full = 0;
    int numeroMensagens = 0; //como o numero de mensagens n funcinou como deveria, ele agora guarda a posicao do ultimo vetor
    string mensagensSalvas[5] = {"vazio", "vazio", "vazio", "vazio", "vazio", };
    Ponto2D ponto;

    Drone(int id, Ponto2D ponto, double raio);
    void mover(double v, double th, double t);
    double calcular_distancia(Drone* drone);
    void broadcast_mensagem(Drone** drones, int n);
    void salvar_mensagem(string mensagem);
    void imprimir_mensagens_recebidas();
    void imprimir_status();

};

#endif