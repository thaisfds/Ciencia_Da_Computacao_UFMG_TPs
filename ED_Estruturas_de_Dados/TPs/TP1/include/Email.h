#ifndef EMAIL_H
#define EMAIL_H

#include<iostream>
#include<string>
#include "msgassert.h"
#include "memlog.h"

class Email{
    private:
        std::string mensagem;
        int prioridade;

    public:
        Email();
        Email(std::string mensagem, int prioridade);
        ~Email();
        std::string getMensagem();
        int getPrioridade();

};

#endif