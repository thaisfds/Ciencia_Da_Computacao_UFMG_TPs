#include "Hash.h"
#include <unistd.h>

//Chega se a extensao do arquivo e a esperada
bool extensionChecker(std::string& name, std::string extension){
    return name.size() >= extension.size() && 0 == name.compare(name.size()-extension.size(), extension.size(), extension);
}

//Recebe os argumentos e seta as entradas
void Argumentos(int argc, char* argv[]){
    int opt;
    while((opt = getopt(argc, argv, "i:o:t:"))!=-1){
        switch(opt){
            case 'i':
                //recebe o nome do arquivo de entrada
                entradas::inputName = optarg;
                erroAssert((entradas::inputName.size() > 0), "Nome de Entrada Invalido");
                erroAssert((extensionChecker(entradas::inputName, ".txt")), "Extensao do arquivo incompativel");
                
                break;
            
            case 'o':
                //recebe o nome do arquivo de saida
                entradas::outputName = optarg;
                erroAssert((entradas::outputName.size() > 0), "Nome de Saida Invalido");
                avisoAssert((extensionChecker(entradas::outputName, ".txt")), "Extensao do arquivo incompativel");
                if(extensionChecker(entradas::outputName, ".txt") == false)
                    entradas::outputName += ".txt";
                break;
            
            case 't':
                //recebe o tipo
                entradas::tipoDicionario = optarg;
                avisoAssert((entradas::tipoDicionario == "hash" || entradas::tipoDicionario == "arv"), "Modo nao existente, o programa será executado no modo arv");
                if(entradas::tipoDicionario != "hash" || entradas::tipoDicionario != "arv")
                    entradas::tipoDicionario  = "arv";
                break;

            default:
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    Argumentos(argc, argv); //Seta os argumentos
    
    std::ifstream input(entradas::inputName);
    std::string linha;

    //1. Criar um dicionario ***********
    Dicionario *dic;

    if(entradas::tipoDicionario == "hash")
        dic = new Hash();
    else
        dic = new ArvoreAVL();

    //2. Inseir no dicionario os verbetes do arquivi ***********
    while(getline(input, linha)){
        
        char tipo = linha[0];
        std::string palavra, sig;
        int inicio = linha.find("[");
        inicio++;
        int fim = linha.find("]");
        palavra = linha.substr(inicio, fim - inicio);
        inicio = fim + 2;

        //Verifica se o tipo e palavra inserido é valido
        if((tipo == 'a' || tipo == 'n' || tipo == 'v') && palavra != ""){
            Verbete *v = new Verbete(tipo, palavra);
            if((int) linha.length()-1 > inicio){
                sig = linha.substr(inicio);
                v->addSignificado(sig);
            }
            dic->Insere(v);
        }
        
        
    }

    //3. Imprimir o dicionario em ordem alfabetica
    dic->Imprimir();
    
    //4. Remover os verbetes que possuem significados
    dic->RemoveComSignificado();

    //5. Imprimir novamente o dicionario
    dic->Imprimir();
    
    //6. Destruir o dicionario
    delete dic;


    input.close();
}