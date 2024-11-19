#ifndef LISTA_H
#define LISTA_H

#include<iostream>

//Lista generia
template <typename T> struct Node{
    T date;
    Node *next;
};

template <typename T> class Lista{
    private:
        Node<T>* head;
        Node<T>* tail;
        int tamanho;

    public:

        Lista(){
            head = nullptr;
            tail = nullptr;
            tamanho = 0;
        }
        
        ~Lista(){
            while(!(tamanho == 0))
                remover();

        }

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

        void adicionarFinal(T date){
            Node<T> *newNode = new Node<T>();   
            newNode->date = date;             
            newNode->next = nullptr;  

            if(head == nullptr){
                //Verifica se a lista esta vazia
                head = newNode;
                tail = newNode;
            }else{
                //Adiciona ao final da fila
                tail->next = newNode;
                tail = newNode;
            }
            tamanho++;
        }

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

        bool pesquisar(T date){
            Node<T> *auxiliar = head;
            while(auxiliar->next){
                if(auxiliar->data == date){
                    delete auxiliar;
                    return true;
                }else{
                    auxiliar = auxiliar->next;
                }
            }
            delete auxiliar;
            return false;
        }
        
        T remover(){
            Node<T> *removido = head;
            if(head) {
                T first = head->date;
                head = head->next;
                tamanho--;
                delete removido;
                return first;
            }
            return nullptr;
        }

        T removerNaPosicao(int posicao){
            int i = 0;
            
            T removido;
                
            if(posicao == 0){
                return remover();
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
                delete analise;
                tamanho--;
                return removido;
            }
        }

        Node<T>* getHead(){
            return head;
        }

        Node<T>* getTail(){
            return tail;
        }
};
#endif