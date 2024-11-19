#include "Registro.h"
#include "Globais.h"
void Ordenar(Registro *vetor, int tam); //Metodo que chama as ordenaçoes de acordo com a versao
void SwapReg(Registro *reg1, Registro *reg2); //Funcao que realiza a troca de posição entre os regitros
int Mediana(Registro *vetor, int inicio, int fim); //Funcao utilizada para achar a mediana
void Particao(Registro *vetor, int esq, int dir, int *i, int *j); //pariçao comum
void ParticaoMediana(Registro *vetor, int esq, int dir, int *i, int *j); //paricao para o quick mediana
void Selection(Registro *vetor, int esq, int dir); // Selection Sort
void QuicksortRecursivo(Registro *vetor, int esq, int dir); // Quicksort Recursivo
void QuicksortMediana(Registro *vetor, int esq, int dir); // Quicksort Mediana
void QuicksortSelecao(Registro *vetor, int esq, int dir); // Quicksort Selecao
void QuicksortNaoRecursivo(Registro *vetor, int esq, int dir); // Quicksort Nao Recursivo
void QuicksortInteligente(Registro *vetor, int esq, int dir); // Quicksort Empilha Inteligente
void Merge(Registro *vetor, int const esq, int const meio, int const dir); //Merge do MergeSorte
void Mergesort(Registro *vetor, int const inicio, int const fim); // Mergesort
void Heap(Registro *vetor, int tam, int raiz); // Heap do Heapsort
void Heapsort(Registro *vetor, int tam); //Heapsort

/*
Todos os quicksorts foram implementados utilizando como base os slides apresentados em sala de aula
enquanto no mergesort e o heapsort utilizei como base os códigos encontrados no geeksforgeeks
*/