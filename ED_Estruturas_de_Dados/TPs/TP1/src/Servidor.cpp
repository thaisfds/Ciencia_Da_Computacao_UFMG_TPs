#include "Servidor.h"

Servidor::Servidor(){
    tamanho = 0;
}

Servidor::~Servidor(){
    
}

void Servidor::gerenciarServidor(std::string nameFile){
    std::ifstream input(nameFile); 
    erroAssert(input.is_open(),"Nao foi possivel abrir o arquivo");

    while(!input.eof()){
        std::string COMANDO,ID;
        
        input >> COMANDO >> ID;
        erroAssert((stoi(ID)>0 || stoi(ID)<1000000),"ID invalido, Esperado valor entre 0 e 1000000");

        if(COMANDO == "CADASTRA"){
            adicionarUsuario(stoi(ID));
        }else if(COMANDO == "REMOVE"){
            removerUsuario(stoi(ID));
        }else if(COMANDO == "ENTREGA"){
            std::string PRI, MSG = "", aux;
            input >> PRI;
            erroAssert((stoi(PRI)>0 || stoi(PRI)<9),"Prioridade invalida, Esperado valor entre 0 e 9");

            //Leitura da mensagem até o fim
            input >> aux;
            while(aux != "FIM"){
                MSG += " ";
                MSG += aux;
                input >> aux;
            };

            enviarEmail(MSG, stoi(PRI), stoi(ID));

        }else if(COMANDO == "CONSULTA"){
            lerEmail(stoi(ID));
        }
    }
    input.close();
}

void Servidor::adicionarUsuario(int ID){
    if(pesquisarPosicao(ID) == -1){
        CaixaDeEntrada *caixaU = new CaixaDeEntrada(ID);
        usuarios.adicionarInicio(caixaU);
        tamanho++;
        std::cout << "OK: CONTA " << ID << " CADASTRADA" << std::endl;

        //std::cout << "Usuario: " << ID << " Posicao: " << pesquisarPosicao(ID) << std::endl;
    }else{
        std::cout << "ERRO: CONTA " << ID << " JA EXISTENTE" << std::endl;
    }
    
}

void Servidor::removerUsuario(int ID){
    int posicaoDoUsuario = pesquisarPosicao(ID);
    if(posicaoDoUsuario != -1){
        std::cout << "OK: CONTA " << usuarios.removerNaPosicao(posicaoDoUsuario)->getID() << " REMOVIDA" << std::endl;
        //std::cout << pesquisarPosicao(ID) << std::endl;
        tamanho--;
    }else{
        std::cout << "ERRO: CONTA " << ID << " NAO EXISTE" << std::endl;
    }
}

void Servidor::enviarEmail(std::string MSG, int PRI, int ID){
    bool enviado = false;
    for(Node<CaixaDeEntrada*> *u = usuarios.getHead(); u; u = u->next){
        if(u->date->getID() == ID){
            u->date->adicionarEmail(MSG, PRI);
            enviado = true;
        }
    }

    if(enviado){
        std::cout << "OK: MENSAGEM PARA " << ID << " ENTREGUE" << std::endl;
    }else{
        std::cout << "ERRO: CONTA " << ID << " NAO EXISTE" << std::endl;
    }
}

void Servidor::lerEmail(int ID){
    bool lido = false;
    for(Node<CaixaDeEntrada*> *u = usuarios.getHead(); u; u = u->next){
        if(u->date->getID() == ID){
            lido = true;
            if(u->date->getTamanho() == 0)
                std::cout << "CONSULTA " << ID << ": CAIXA DE ENTRADA VAZIA" << std::endl;
            else
                std::cout << "CONSULTA " << ID << ":" << u->date->deletarEmail() << std::endl;
        }
    }  
    
    if(!lido){
        std::cout << "ERRO: CONTA " << ID << " NAO EXISTE" << std::endl;
    }
}

int Servidor::pesquisarPosicao(int ID){
    int posicao = 0;

    for(Node<CaixaDeEntrada*> *u = usuarios.getHead(); u; u = u->next){
        if(u->date->getID() == ID) return posicao;
        posicao++;
    }

    return -1;
}

