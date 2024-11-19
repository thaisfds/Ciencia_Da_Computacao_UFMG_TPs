#include "Cliente.hpp"
#include "FilaAtendimento.hpp"

void FilaAtendimento::adicionar_cliente(std::string nome, int idade){
    Node* newNode = new Node;

    newNode->cliente = new Cliente(nome, idade, senhaAtual);
    newNode->next = nullptr;

    if(head == nullptr){
    //Verifica se a lista esta vazia
        head = newNode;
        tail = newNode;
    }else if(newNode->cliente->eh_prioritario()){
        //Verifica se o cliente é prioritario
        Node* analise = head;
        Node* ultimaPrioridade = head;
        //se o primeiro da fila for prioritario
        if(head->cliente->eh_prioritario()){
            while(analise != nullptr && analise->cliente->eh_prioritario()){
                ultimaPrioridade = analise;
                analise = analise->next;
            }
            if(analise == tail){tail = analise;}

            newNode->next = analise;
            ultimaPrioridade->next = newNode;

        }else{
            newNode->next = head;
            head = newNode;
        }

    }else{
        //se for um cliente comum vai para o final da fila
        tail->next = newNode;
        tail = newNode;
    }

    senhaAtual++;
}

Cliente* FilaAtendimento::chamar_cliente(){
    Node* primeiro = head;
    if(head == nullptr){
        std::cout << "Fila vazia!" << std::endl;
        return nullptr;
    }else{
        head = head->next;
        return primeiro->cliente;
    }
    
}

void FilaAtendimento::estimativa_tempo_espera(int senha){
    Node* analise = head;
    int tempo = 0;
    while(analise->cliente->senha != senha){
        tempo += analise->cliente->tempo_estimado_atendimento();
        analise = analise->next;
    }

    std::cout << "Tempo estimado para atender " << analise->cliente->nome << " eh " << tempo << " minutos." << std::endl;
}

void FilaAtendimento::imprimir_fila(){
    Node* imprimir = head;
    while(imprimir != nullptr){
        imprimir->cliente->imprimir_dados();
        imprimir = imprimir->next;
    }
}