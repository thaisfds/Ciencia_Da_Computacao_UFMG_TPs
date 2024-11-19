#include "Hash.h"

//Funcao hash
int Hash::FuncHash(std::string palavra){
    int pos = int(tolower(palavra[0])) - 97;
    if(int(palavra[0]) > 96)
        pos += 26;
    return pos;
}

//Contrutor do hash
Hash::Hash(){
    
}

//Destrutor do hash
Hash::~Hash(){
    Limpar();
}

//Pesquisa uma palavra no hash
Verbete* Hash::Pesquisa(char tipo, std::string palavra){
    int pos;
    Node<Verbete*> *aux;

    pos = FuncHash(palavra);
    
    //Entra na posicao na tabela do hash
    if(pos >= 0 && pos < 52){
        for(aux = Tabela[pos].getHead(); aux != nullptr; aux = aux->next){
            if(aux->date->getTipo() == tipo && aux->date->getPalavra() == palavra){
                return aux->date;
            }
        }
    }
    return nullptr;
}

//Insere uma palvra no hash
void Hash::Insere(Verbete *verb){
    Verbete *aux;
    int pos;

    //Recebe a posicao na tabela
    aux = Pesquisa(verb->getTipo(), verb->getPalavra());
    
    if(aux == nullptr){
        pos =  FuncHash(verb->getPalavra());
       //Tabela[pos].adicionarNaPosicao(verb,0);
        int i = 0;
        for(Node<Verbete*> *v = Tabela[pos].getHead(); v != nullptr; v = v->next){
            if(v->date->getPalavra() < verb->getPalavra())
                i++;
            if(v->date->getPalavra() == verb->getPalavra() && v->date->getTipo() < verb->getTipo())
                i++;
        }
        Tabela[pos].adicionarNaPosicao(verb,i);
    }else{
        aux->addSignificado(verb->getPrimeiroSignificado());
        delete verb;
    }
}

//Remove uma palvra do hash
void Hash::Remove(char tipo, std::string palavra){
    Node<Verbete*> *aux;
    Node<Verbete*> *aux2;
    for(int i = 0; i < 52; i++){
        int posicao = 0;
        aux = Tabela[i].getHead();
        if(aux != nullptr)
            aux2 = aux->next;

        while(aux != nullptr){
            aux2 = aux->next;
            if(aux->date->getTipo() == tipo && aux->date->getPalavra() == palavra){
                Verbete *a = Tabela[i].removerNaPosicao(posicao); 
                a->limpar();
                delete a;
                posicao--;
            }
            aux = aux2;
            posicao++;
        };

    }
}

void Hash::RemoveComSignificado(){
    Node<Verbete*> *aux;
    Node<Verbete*> *aux2;
    //Percorre todas as tabelas do hash
    for(int i = 0; i < 52; i++){
        int posicao = 0;
        aux = Tabela[i].getHead();
        //Percorre todos os elementos da tabela
        if(aux != nullptr)
            aux2 = aux->next;

        while(aux != nullptr){
            aux2 = aux->next;
            if(aux->date->temSignificados()){
                Verbete *a = Tabela[i].removerNaPosicao(posicao); 
                a->limpar();
                delete a;
                posicao--;
            }
            aux = aux2;
            posicao++;
        };

    }
}

//Imprime as palavras do hash
void Hash::Imprimir(){
    Node<Verbete*> *aux;
    //Percorre todas as tabelas do hash
    for(int i = 0; i < 52; i++){
        for(aux = Tabela[i].getHead(); aux != nullptr; aux = aux->next){
            aux->date->imprimirSignificados();
        }   
    }
}

//Limpa o hash no destrutor
void Hash::Limpar(){
    Node<Verbete*> *aux;
    //Percorre todas as tabelas do hash
    for(int i = 0; i < 52; i++){
        aux = Tabela[i].getHead();
        while(aux != nullptr){
            Verbete *a = Tabela[i].remover();
            a->limpar();
            aux = Tabela[i].getHead();
            delete a;
        };
    }
}