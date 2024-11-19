#include "Verbete.h"

//Inicializa o tipo e a palavra como vazias
Verbete::Verbete(){
    this->tipo = ' ';
    this->palavra = "";
}

//Inicializa o tipo e a palavra com os valores da entrada
Verbete::Verbete(char tipo, std::string palavra){
    this->tipo = tipo;
    this->palavra = palavra;
}

//Destutor do verbete
Verbete::~Verbete(){
    limpar();
}

//Retorna o tipo
char Verbete::getTipo(){
    return tipo;
}

//Retorna a palavra
std::string Verbete::getPalavra(){
    return palavra;
}

//Imprime todos os significaods no arquivo
void Verbete::imprimirSignificados(){
    std::ofstream output(entradas::outputName, std::ios::app | std::ios::out);
    int contador = 1;
    output << palavra << " (" << tipo << ")" << std::endl;
    
    for(Node<std::string> *s = significados.getHead(); s; s = s->next){
        if(s->date != ""){
            output << contador << ". " << s->date << std::endl;
            contador++;
        }
    }
    output.close();
}

//verifica se o verbete tem significados
bool Verbete::temSignificados(){
    if(significados.getHead() != nullptr)
        return true;
    else
        return false;
}

//Seta o tipo
void Verbete::setTipo(char tipo){
    this->tipo = tipo;
}

//Seta a palavra
void Verbete::setPalavra(std::string palavra){
    this->palavra = palavra;
}

//Adiciona um significado a lista de significados
void Verbete::addSignificado(std::string sig){
    significados.adicionarFinal(sig);
}

//Limpa o verbete
void Verbete::limpar(){
    for(Node<std::string> *s = significados.getHead(); s; s = s->next){
        significados.remover();
    }
}

//Retorna apenas o primeiro verbete da lista (utilizado quando a palavra ja existe no dicionario)
std::string Verbete::getPrimeiroSignificado(){
    if(significados.getHead() != nullptr)
        return significados.getHead()->date;
    return "";
}