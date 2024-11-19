#include "Lista.h"
#include <fstream>

class Verbete{
    private:
        char tipo;
        std::string palavra;
        //Lista de significados de um verbete
        Lista<std::string> significados;

    public:
        //Inicializa o tipo e a palavra como vazias
        Verbete();
        //Inicializa o tipo e a palavra com os valores da entrada
        Verbete(char tipo, std::string palavra);
        //Destutor do verbete
        ~Verbete();

        char getTipo(); //Retorna o tipo
        std::string getPalavra(); //Retorna a palavra
        void imprimirSignificados(); //Imprime todos os significaods no arquivo
        bool temSignificados();
        void setTipo(char tipo); //Seta o tipo
        void setPalavra(std::string palavra); //Seta a palavra
        void addSignificado(std::string sig); //Adiciona um significado a lista de significados
        void limpar(); //Limpa o verbete
        //Retorna apenas o primeiro verbete da lista (utilizado quando a palavra ja existe no dicionario)
        std::string getPrimeiroSignificado();

};