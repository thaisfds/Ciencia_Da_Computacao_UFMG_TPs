// NÃO ALTERE ESSA LINHA
#include "avaliacao_basica_nba.hpp"
#include "RegistroNBA.hpp"
#include "Time.hpp"
#include "Jogador.hpp"

int main() {
    char data;
    int salario;
    RegistroNBA registro;
    string nome_time, nome_jogador, posicao;

    
    while (cin >> data) {   // Lendo o caractere que define o comando

        // Executando o comando informado
        switch (data) {
            
            // 't' adiciona um time
            case 't':                 
                cin >> nome_time;
                registro.adicionar_time(nome_time);
                break;

            // 'j' adiciona um jogador
            case 'j':
            cin >> nome_time >> nome_jogador >> posicao >> salario;
                registro.adicionar_jogador(nome_time, nome_jogador, posicao, salario);
                break;

            // 'l' lista de jogadores de um time
            case 'l':                  
                cin >> nome_time;
                registro.imprimir_lista_jogadores_time(nome_time);
                break;     

            // 'f' imprime a folha salarial consolidade de um time
            case 'f':                  
                registro.imprimir_folha_consolidada_time(nome_time);
                break;  

            // 'g' imprime a folha salarial geral
            case 'g':                  
                registro.imprimir_folha_salarial_geral();
                break;    

            // 'b' chama a funcao avaliacao_basica()
            case 'b':                  
                avaliacao_basica();
                break;                                

        }
    }

    return 0;
}