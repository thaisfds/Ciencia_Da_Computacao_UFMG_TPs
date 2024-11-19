#ifndef LIMITEDQUEUE_H
#define LIMITEDQUEUE_H

#include "Exceptions.hpp"


// Fila de números inteiros de tamanho limitado
class LimitedQueue {

    private:
        int max_size;
        list<int>fila;

    public:

        int get_max_size();

        // Construtor da fila.
        // Lança a exceção InvalidSizeException se max_size <= 0.
        // O tamanho máximo da fila deve ser acessível por um método 'get_max_size()'. 
        LimitedQueue(int max_size);

        // Insere um elemento no final da fila.
        // Lança a exceção QueueFullException se a fila estiver cheia.
        void push_back(int k);

        // Retira o elemento do início da fila.
        // Lança a exceção QueueEmptyException se a fila estiver vazia.
        void pop_front();

        // Retorna (sem retirar) o primeiro elemento (início da fila).
        // Lança uma exceção QueueEmptyException se a fila estiver vazia.
        int front();

        // Retorna (sem retirar) o último elemento (final da fila).
        // Lança a exceção QueueEmptyException se a fila estiver vazia.
        int back();

        // Verifica se um elemento está na fila e retorna a posição dele (começando de 0).
        // Lança a exceção QueueEmptyException se a fila estiver vazia.
        // Lança a exceção ItemNotFoundException se o elemento não estiver na fila.
        int find(int k);

        // Imprime todos os elementos da fila em ordem, sendo um por linha.
        // Lança a exceção QueueEmptyException se a fila estiver vazia.
        void print();

};

#endif
