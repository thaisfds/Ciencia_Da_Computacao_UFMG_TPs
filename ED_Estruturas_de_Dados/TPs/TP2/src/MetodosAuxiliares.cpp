#include "MetodosAuxiliares.h"

bool extensionChecker(std::string& name, std::string extension){
    return name.size() >= extension.size() && 0 == name.compare(name.size()-extension.size(), extension.size(), extension);
}

double Timer(){
    struct rusage resources;
    int rc;
    double utime, stime, total_time;
    /* do some work here */
    if((rc = getrusage(RUSAGE_SELF, &resources)) != 0)
    perror("getrusage failed");
    utime = (double) resources.ru_utime.tv_sec+ 1.e-6 * (double) resources.ru_utime.tv_usec;
    stime = (double) resources.ru_stime.tv_sec+ 1.e-6 * (double) resources.ru_stime.tv_usec;
    total_time = utime+stime;
    return total_time;
}

void Argumentos(int argc, char* argv[]){
    int opt;
    while((opt = getopt(argc, argv, "v:s:k:m:i:o:p:l"))!=-1){
        switch(opt){
            case 'v':
                entradas::versao = atoi(optarg);
                if(entradas::versao < 0 || entradas::versao>7){
                    avisoAssert(false, "Versao nao disponivel. O codigo sera rodado com a versao 1");
                    entradas::versao = 1;
                }
                    
                break;

            case 's':
                entradas::seed = atoi(optarg);
                if(entradas::seed < 0){
                    avisoAssert(false, "Seed negativa detectada, o codigo rodara com o seu valor positivo");
                    entradas::seed *= -1;
                }
                break;

            case 'k':
                entradas::k = atoi(optarg);
                if(entradas::k < 0){
                    avisoAssert(false, "k negativo detectado, o codigo rodara com o seu valor positivo");
                    entradas::k *= -1;
                }
                break;

            case 'm':
                entradas::m = atoi(optarg);
                if(entradas::m < 0){
                    avisoAssert(false, "m negativo detectado, o codigo rodara com o seu valor positivo");
                    entradas::m *= -1;
                }
                break;
            
            case 'i':
                entradas::inputName = optarg;
                erroAssert((entradas::inputName.size() > 0), "Nome de Entrada Invalido");
                erroAssert((extensionChecker(entradas::inputName, ".txt")), "Extensao do arquivo incompativel");
                break;
            
            case 'o':
                entradas::outputName = optarg;

                erroAssert((entradas::outputName.size() > 0), "Nome de Saida Invalido");
                avisoAssert((extensionChecker(entradas::outputName, ".txt")), "Extensao do arquivo incompativel");
                if(extensionChecker(entradas::outputName, ".txt") == false)
                    entradas::outputName += ".txt";
                break;

            case 'p':
                entradas::regName = optarg;
                erroAssert((entradas::regName.size() > 0), "Nome de Saida Invalido");
                
                break;

            case 'l':
                entradas::access = true;
                break;

            default:
                break;
        }
    }
}

/*
Esse método não foi solicitado para o tp, mas tomei a liberdade de construir uma funcao
que testa para uma mesma entrada todos os métodos de ordenaçao
gerando um arquivo padrao com todas as médias
e um arquivo separado com os dados detalhados de cada um dos metodos
para isso apenas adicionei o parametro k que escolhe o metodo analisado
*/
void AnaliseGeral(std::ifstream& input,std::ofstream& output){
    int N;
    input >> N;

    //Cria o vetor de tamanhos
    int tamanhos[N];

    //Pega o valor de todos os tamanhos
    for(int i = 0; i<N; i++)
        input >> tamanhos[i];

    for(int k = 0; k<7; k++){
        entradas::versao++;
        std::ofstream outputIndividual((entradas::outputName += Geral::arquivos[k]), std::ios::app | std::ios::out);
        ZeraMedias();
        for(int i = 0; i < N; i++){
            ImprimeCabecalho(tamanhos[i],outputIndividual);

            for(int l=0; l<5; l++){
                srand48(entradas::seed);
                analise::comparacoes = 0;
                analise::copias = 0;
                
                Registro *vetorAleatorio = new Registro[tamanhos[i]];

                for(int j=0; j<tamanhos[i]; j++)
                    vetorAleatorio[j].chave = lrand48() % 1000;

                analise::tempoInicial = Timer();
                Ordenar(vetorAleatorio, tamanhos[i]);
                analise::tempoFinal = Timer();
                analise::tempoTotal = analise::tempoFinal - analise::tempoInicial;

                ImprimeSaida(tamanhos[i], outputIndividual);

                delete[] vetorAleatorio;

                Geral::mediaComparacoes[i] += analise::comparacoes;
                Geral::mediaCopias[i] += analise::copias;
                Geral::mediaTempo[i] += analise::tempoTotal;
                entradas::seed += 5;

            }
            Geral::mediaComparacoes[i] /= 5;
            Geral::mediaCopias[i] /= 5;
            Geral::mediaTempo[i] /= 5;

            ImprimeMedia(i,outputIndividual);
            entradas::seed -= 25;
        }
        outputIndividual.close();
        ImprimeGeral(output);
        ImprimeMediaGeral(tamanhos, N, output);

    }

}


//Funçoes de impressao
void ImprimeCabecalho(int tamanho, std::ofstream& output){
    output << "----------------------------------------------------------------------------------------\n";
    output << Geral::versionName[entradas::versao-1] << " - TAMANHO: " << tamanho << "\n\n";
    output.width(10);
    output << "SEED";
    output.width(25);
    output << "TEMPO DE EXECUCAO";
    output.width(25);
    output << "COMPARACOES DE CHAVES";
    output.width(25);
    output << "COPIAS DE REGISTROS";
    output << std::endl;
}

void ImprimeSaida(int tamanho, std::ofstream& output){
    output.width(10);
    output << entradas::seed;
    output.width(25);
    output << analise::tempoTotal;
    output.width(25);
    output << analise::comparacoes;
    output.width(25);
    output << analise::copias;
    output << std::endl;
}

void ImprimeMedia(int n, std::ofstream& output){
    output << "MEDIA GERAL: " << std::endl;
    output.width(10);
    output << "TODAS";
    output.width(25);
    output << Geral::mediaTempo[n];
    output.width(25);
    output << Geral::mediaComparacoes[n];
    output.width(25);
    output << Geral::mediaCopias[n];
    output << std::endl;
}

void ImprimeGeral(std::ofstream& output){
    output << "----------------------------------------------------------------------------------------\n";
    output << Geral::versionName[entradas::versao-1] << "\n\n";
    output.width(10);
    output << "TAMANHO";
    output.width(25);
    output << "TEMPO DE EXECUCAO";
    output.width(25);
    output << "COMPARACOES DE CHAVES";
    output.width(25);
    output << "COPIAS DE REGISTROS";
    output << std::endl;
}

void ImprimeMediaGeral(int *tamanhos, int n, std::ofstream& output){
    for(int i = 0; i<n; i++){
        output.width(10);
        output << tamanhos[i];
        output.width(25);
        output << Geral::mediaTempo[i];
        output.width(25);
        output << Geral::mediaComparacoes[i];
        output.width(25);
        output << Geral::mediaCopias[i];
        output << std::endl;
    }
}

void ZeraMedias(){
    for(int i = 0; i<7; i++){
        Geral::mediaComparacoes[i] = 0;
        Geral::mediaCopias[i] = 0;
        Geral::mediaTempo[i] = 0;
    }
}