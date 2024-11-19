#include <iostream>
#include "memlog.h"
#include "msgassert.h"

namespace entradas{
    inline int versao = 0, seed = 0, k = 3, m = 10;
    inline std::string inputName, outputName, regName = "log.out";
    inline bool access = false;

}

namespace analise{
    inline int comparacoes = 0;
    inline int copias = 0;
    inline double tempoInicial = 0;
    inline double tempoFinal = 0;
    inline double tempoTotal = 0;
}

namespace Geral{
    inline std::string versionName[7] = {   "QUICKSORT RECURSIVO",
                                            "QUICKSORT MEDIANA",
                                            "QUICKSORT SELECAO",
                                            "QUICKSORT NAO RECURSIVO",
                                            "QUICKSORT INTELIGENTE",
                                            "MERGESORT",
                                            "HEAPSORT"};
    inline std::string arquivos[7] = {  "1QuickSortRecursivo.txt",
                                        "2QuickSortMediana.txt",
                                        "3QuickSortSelcao.txt",
                                        "4QuickSortNaoRecursivo.txt",
                                        "5QuickSortEmpilhaInteligente.txt",
                                        "6MergeSort.txt",
                                        "7HeapSort.txt"};
    inline double tempo = 0;
    inline double tempoTotal = 0;
    inline double mediaComparacoes[7] = {0,0,0,0,0,0,0};
    inline double mediaCopias[7] = {0,0,0,0,0,0,0};
    inline double mediaTempo[7] = {0,0,0,0,0,0,0};
    inline double medias[7][3]; //versao e medias
    
}