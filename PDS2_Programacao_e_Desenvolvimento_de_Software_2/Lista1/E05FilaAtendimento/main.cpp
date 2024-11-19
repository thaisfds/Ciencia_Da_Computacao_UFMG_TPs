// NÃO ALTERE ESSA LINHA
#include "avaliacao_basica_atendimento.hpp"
#include "Cliente.hpp"
#include "FilaAtendimento.hpp"

int main() {

    //
    // Adicione seu código aqui e faça as demais alterações necessárias
    //

    char data;
    int idade, senha;
    FilaAtendimento fila;
    string nome;

    
    while (cin >> data) {   // Lendo o caractere que define o comando

        // Executando o comando informado
        switch (data) {
            
            // 'a nome idade' adiciona um novo cliente na fila
            case 'a':                 
                cin >> nome >> idade;
                fila.adicionar_cliente(nome,idade);
                break;

            // 'c' chamar ou remover um cliente da fila
            case 'c':
                fila.chamar_cliente();
                break;

            // 'e senha' imprime a estimativa de tempo de espera
            case 'e':                  
                cin >> senha;
                fila.estimativa_tempo_espera(senha);
                break;     

            // 'p' imprime a situacao da fila
            case 'p':                  
                fila.imprimir_fila();
                break;     

            // 'b' chama a funcao avaliacao_basica()
            case 'b':                  
                avaliacao_basica();
                break;                                

        }
    }
    

    return 0;
}