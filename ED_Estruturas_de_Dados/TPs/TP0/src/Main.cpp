#include <unistd.h>
#include <string.h>
#include "PPM.h"


//GPROGF
// make
// ./bin/run.out -i ./imagens/lagoa.ppm -o ./obj/lagoa.pgm -p log.out -l
// gprof bin/run.out gmon.out > analise.txt


/*
ANALISAMEM
1° Adiciona a pasta analisamem no tp
2° No terminal entra no ./analisamem
    Comando: make bin
3° Volta para a pasta do tp e compila o programa
    Comando: cd ..
    Comando: make
    Comando: ./bin/run.out -i ./imagens/lagoa.ppm -o ./obj/lagoa.pgm -p ./analisamem/bin/log.out -l
4° Entra na analisamem.bin e gera os gráficos
    Comando: cd analisamem/bin/
    Comando: ./analisamem -i log.out -p saida
    Comando: gnuplot *.gp
*/

// make
// ./bin/run.out -i ./imagens/lagoa.ppm -o ./obj/lagoa.pgm -p ./analisamem/bin/log.out -l
// ./analisamem -i log.out -p saida
//  gnuplot *.gp

//sudo apt-get  update
//sudo apt-get  upgrade
//sudo apt-get install gnuplot

static bool extensionChecker(string& name, string extension){
    return name.size() >= extension.size() && 0 == name.compare(name.size()-extension.size(), extension.size(), extension);
}

int main(int argc, char* argv[]) {
    int opt;
    bool access = false;
    string nameIn, nameOut, nameReg;

    while((opt = getopt(argc, argv, "i:o:p:l"))!=-1){
        switch(opt){
            case 'i':
                //target de entrada
                nameIn = optarg;
                erroAssert((nameIn.size() > 0),"Nome de Entrada Invalida");
                erroAssert((extensionChecker(nameIn, ".ppm")),"Extensao do arquivo de Entrada Invalida (precisa ser .ppm)");
                break;

            case 'o':
                //target de saida
                nameOut = optarg;
                erroAssert((nameOut.size() > 0),"Nome de Saida Invalida");
                avisoAssert((extensionChecker(nameOut, ".pgm")),"Extensao do arquivo de Saida Invalida (foi alterada pra .pgm)");
                if(extensionChecker(nameOut, ".pgm") ==  false)
                    nameOut += ".pgm";
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

    //Criacao do nosso ppm
    PPM *entrada = new PPM();

    //Le o arquivo PPM
    defineFaseMemLog(0);
    entrada->PPMreader(nameIn);

    //Converte o arquivo de PPM pra PGM
    defineFaseMemLog(1);
    entrada->PPMtoPGM();

    //Escreve o arquivo PGM
    entrada->PGMwrite(nameOut);


    finalizaMemLog(); //Finaliza o MemLog
    return 0;
}