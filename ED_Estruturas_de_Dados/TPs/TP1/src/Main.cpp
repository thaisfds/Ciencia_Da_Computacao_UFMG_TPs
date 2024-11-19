#include <unistd.h>
#include <string.h>
#include "Servidor.h"

static bool extensionChecker(std::string& name, std::string extension){
        return name.size() >= extension.size() && 0 == name.compare(name.size()-extension.size(), extension.size(), extension);
}

int main(int argc, char* argv[]) {
    int opt;
    bool access = false;
    std::string nameIn, nameReg;

    while((opt = getopt(argc, argv, "i:p:l"))!=-1){
        switch(opt){
            case 'i':
                //target de entrada
                nameIn = optarg;
                erroAssert((nameIn.size() > 0),"Nome de Entrada Invalida");
                erroAssert((extensionChecker(nameIn, ".txt")),"Extensao do arquivo de Entrada Invalida");
                break;

            case 'p':
                //Reg desempenho
                nameReg = optarg;
                erroAssert((nameReg.size() > 0),"Nome de Saida Invalida");
                break;

            case 'l':
                //Log de acesso
                access = true;
                break;

            default:

                break;
        }
    }
    //transformar nome registro em char
    char* nameRegChar = new char[nameReg.size() + 1];
    strcpy(nameRegChar, nameReg.c_str());

    iniciaMemLog(nameRegChar);
    access? ativaMemLog() : desativaMemLog();

    //Criacao do servidor
    Servidor *google = new Servidor();
    google->gerenciarServidor(nameIn);
    finalizaMemLog(); //Finaliza o MemLog
    
    delete google;
    return 0;
}
