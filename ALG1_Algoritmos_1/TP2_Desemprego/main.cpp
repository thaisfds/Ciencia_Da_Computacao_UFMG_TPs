#include "linkOut.hpp"
#include <chrono> 
using namespace std;

int main(int argc, char const *argv[]) {
    // Your code here

    /* Numero de Usuários, Empregos, Qualificações */
    int U, J, E; 

    /* Nome dos Usuários e das Empresas*/
    string usuario, empresa;

    /*Leitura dos dados iniciais*/
    cin >> U >> J >> E;

    /*Inicializa os grafos*/
    Graph Rede = Graph(U, J, E); //Grafo do algoritmo guloso
    Graph Rede1 = Graph(U, J, E); //Grafo do algoritmo exato

    unordered_map<string, int> EU; //Mapa para armazenar os usuarios e as empresas

    int imap = 0, jmap = U; //Variaveis para mapear os usuarios e as empresas

    /* Adicionar Usuários e Empresas a Rede*/
    for(int i = 0; i< E; i++){
        cin >> usuario >> empresa;

        /* Se o usuario ou empresa nao esta no grafo*/
        if (EU.find(usuario) == EU.end()) {
            EU.insert({usuario, imap});
            imap++;
        }
        if (EU.find(empresa) == EU.end()) {
            EU.insert({empresa, jmap});
            jmap++;
        }

        Rede.addAresta(EU[usuario], EU[empresa] - U); //Adiciona aresta no grafo do algoritmo guloso
        Rede1.addAresta(EU[usuario], EU[empresa] - U); //Adiciona aresta no grafo do algoritmo exato
    }

    //Inicialização da rede LinkOut
    LinkOut LO1 = LinkOut(Rede);
    LinkOut LO2 = LinkOut(Rede1);

    //Execução dos algoritmos
    cout << "Guloso: " << LO1.algoritmoGuloso() << endl;
    cout << "Exato: " << LO2.algoritmoExato() << endl;




    /*Para teste de comparação dos testes descomente essa parte*/
    
    /*
    auto inicio = std::chrono::high_resolution_clock::now();

    cout << "Guloso: " << LO1.algoritmoGuloso() << endl;

    auto fim = std::chrono::high_resolution_clock::now();
    auto duracao_ex = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);
    cout << ". Tempo de execução: " << duracao_ex.count() << " ms." << endl;

    inicio = std::chrono::high_resolution_clock::now();

    cout << "Exato: " << LO2.algoritmoExato() << endl;

    fim = std::chrono::high_resolution_clock::now();
    auto duracao_guloso = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio);
    cout << ". Tempo de execução: " << duracao_guloso.count() << " ms." << endl;
    */

    return 0;
}