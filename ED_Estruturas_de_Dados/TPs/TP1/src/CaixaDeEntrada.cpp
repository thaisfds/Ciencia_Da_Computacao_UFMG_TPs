 #include"CaixaDeEntrada.h"

CaixaDeEntrada::CaixaDeEntrada(int ID){
    this->tamanho = 0;
    this->ID = ID;
}

CaixaDeEntrada::~CaixaDeEntrada(){  
    
}

int CaixaDeEntrada::getTamanho(){
    return this->tamanho;
}

void CaixaDeEntrada::adicionarEmail(std::string mensagem, int prioridade){
    int posicao = 0;
    Email *e1 = new Email(mensagem,prioridade);

    if(prioridade >= 0 && prioridade <= 9){
        for(Node<Email*> *e = caixaEmail.getHead(); e; e = e->next){
            if(e->date->getPrioridade() >= e1->getPrioridade()){
                posicao++;
            }
        }

        caixaEmail.adicionarNaPosicao(e1,posicao); 
        tamanho++;
    } 
       
}

void CaixaDeEntrada::imprimirEmail(){
    for(Node<Email*> *e = caixaEmail.getHead(); e; e = e->next) 
        std::cout << e->date->getMensagem() << std::endl;
}

std::string CaixaDeEntrada::deletarEmail(){
    tamanho--;
    return caixaEmail.remover()->getMensagem();
}

int CaixaDeEntrada::getID(){
    return this->ID;
}
