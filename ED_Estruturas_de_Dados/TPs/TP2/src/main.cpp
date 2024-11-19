#include "MetodosAuxiliares.h"

int main(int argc, char* argv[]){
    //Pega os argumentos da compilacao
    Argumentos(argc, argv);

    //abre o arquivo de leitura e escrita
    std::ifstream input(entradas::inputName);
    std::ofstream output (entradas::outputName, std::ios::app | std::ios::out);

    if(entradas::versao == 0){
        AnaliseGeral(input,output); //Metodo que testa todos os tipos de ordenacao
    }else{
        //pega o numero de tamanhos
        int N;
        input >> N;

        //Cria o vetor de tamanhos
        int tamanhos[N];

        //Pega o valor de todos os tamanhos
        for(int i = 0; i<N; i++)
            input >> tamanhos[i];
    
        iniciaMemLog(entradas::regName.c_str());
        
        //Ativa o memlog
        (entradas::access)? ativaMemLog() : desativaMemLog();
        defineFaseMemLog(0);
        for(int i = 0; i < N; i++){

            ImprimeCabecalho(tamanhos[i],output);
            
            for(int l=0; l<5; l++){
                //inicia a seed do vetor aleatorio
                srand48(entradas::seed);
                analise::comparacoes = 0;
                analise::copias = 0;
                
                //Cria o vetor aleatorio
                Registro *vetorAleatorio = new Registro[tamanhos[i]];

                //Preenche o vetor aleatório
                for(int j=0; j<tamanhos[i]; j++)
                    vetorAleatorio[j].chave = lrand48() % 1000;

                //Ordena o vetor e pega os tempos
                analise::tempoInicial = Timer();
                Ordenar(vetorAleatorio, tamanhos[i]);
                analise::tempoFinal = Timer();
                analise::tempoTotal = analise::tempoFinal - analise::tempoInicial;

                ImprimeSaida(tamanhos[i], output);

                delete[] vetorAleatorio;

                //soma os valores na média
                Geral::mediaComparacoes[i] += analise::comparacoes;
                Geral::mediaCopias[i] += analise::copias;
                Geral::mediaTempo[i] += analise::tempoTotal;
                entradas::seed += 5; //modifica a seed em 5 unidades

            }
            //calcula a média dividindo os valores por 5
            Geral::mediaComparacoes[i] /= 5;
            Geral::mediaCopias[i] /= 5;
            Geral::mediaTempo[i] /= 5;

            ImprimeMedia(i,output);
            entradas::seed -= 25; //volta a seed para o valor padrão
        }
        finalizaMemLog();
    }
    input.close();
    output.close();
    
    return 0;
}