#ifndef LISTA_H
#define LISTA_H

#include "Globais.h"

//Node da lista negerica
template <typename T> struct Node{
    T date;
    Node *next;
};

//Lista generia com template
template <typename T> class Lista{
    private:
        Node<T>* head; //Primeiro da lista
        Node<T>* tail; //Ultimo da lista
        int tamanho; //Tamanho da lista

    public:

        //Contrutor da lista que inicia tudo como nullptr e 0
        Lista(){
            head = nullptr;
            tail = nullptr;
            tamanho = 0;
        }

        //Adiciona no final da lista
        void adicionarFinal(T date){
            Node<T> *newNode = new Node<T>();   
            newNode->date = date;             
            newNode->next = nullptr; 
            if(head == nullptr){
                //Verifica se a lista esta vazia
                head = newNode;
                tail = newNode;
            }else{
                tail->next = newNode;
                tail = newNode;
            }
            tamanho++;
        }

        //Adiciona no inicio da lista
        void adicionarInicio(T date){
            Node<T> *newNode = new Node<T>();   
            newNode->date = date;             
            newNode->next = nullptr;  

            if(head == nullptr){
                //Verifica se a lista esta vazia
                head = newNode;
                tail = newNode;
            }else{
                //Adiciona ao inicio da fila
                newNode->next = head;
                head = newNode;
            }
            tamanho++;
        }

        //Adiciona em qualquer posicao da lista
        void adicionarNaPosicao(T date, int posicao){
            Node<T> *newNode = new Node<T>();   
            newNode->date = date;             
            newNode->next = nullptr;
            
            int i = 0;  

            if(head == nullptr){
                //Verifica se a lista esta vazia
                head = newNode;
                tail = newNode;
            }else if(posicao == 0){
                newNode->next = head;
                head = newNode;
            }else if(posicao >= tamanho){
                tail->next = newNode;
                tail = newNode;
            }else{
                //Adiciona ao final da fila
                Node<T> *ultimaAnalise = head;
                Node<T> *analise = head;
                
                while(analise != nullptr && i<posicao){
                    ultimaAnalise = analise;
                    analise = analise->next;
                    i++;
                }

                newNode->next = analise;
                ultimaAnalise->next = newNode;

            }
            tamanho++;
        }

        //Remove o primeiro da lista
        T remover(){
            if(head) {
                Node<T> *removido = head;
                T first = head->date;
                head = head->next;
                tamanho--;
                delete removido;
                return first;
            }
            return nullptr;
        }

        //Remove em qualquer posicao da lista
        T removerNaPosicao(int posicao){
            int i = 0; 
            T removido; 
            if(posicao == 0){
                removido = remover();
            }else{
                Node<T> *ultimaAnalise = head;
                Node<T> *analise = head;
                
                while(analise != nullptr && i<posicao){
                    ultimaAnalise = analise;
                    analise = analise->next;
                    i++;
                }

                ultimaAnalise->next = analise->next;
                removido = analise->date;
                tamanho--;
                delete analise;
            }
            return removido;
        }

        //Gets
        Node<T>* getHead(){
            return head;
        }

        Node<T>* getTail(){
            return tail;
        }

        int getTamanho(){
            return tamanho;
        }
};
#endif