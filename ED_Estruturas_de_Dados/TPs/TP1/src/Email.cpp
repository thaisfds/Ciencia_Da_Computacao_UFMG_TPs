#include "Email.h"
Email::Email(){
    
}

Email::Email(std::string mensagem, int prioridade){
    this->mensagem = mensagem;
    this->prioridade = prioridade;
}

Email::~Email(){
    
}

std::string Email::getMensagem(){
    return this->mensagem;
}

int Email::getPrioridade(){
    return this->prioridade;
}