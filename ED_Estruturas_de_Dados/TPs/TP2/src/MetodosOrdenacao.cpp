#include "MetodosOrdenacao.h"
#include "Pilha.h"

//Funcao que chama um tipo de ordenção dependendo da versao escolhida
void Ordenar(Registro *vetor, int tam){
    switch(entradas::versao){
        case 1:
            QuicksortRecursivo(vetor, 0, tam-1);
            break;

        case 2:
            QuicksortMediana(vetor, 0, tam-1);
            break;

        case 3:
            QuicksortSelecao(vetor, 0, tam-1);
            break;

        case 4:
            QuicksortNaoRecursivo(vetor, 0, tam-1);
            break;

        case 5:
            QuicksortInteligente(vetor, 0, tam-1);
            break;

        case 7:
            Mergesort(vetor, 0, tam-1);
            break;

        case 6:
            Heapsort(vetor, tam);
            break;

        default:
            break;
    }
}

//Realiza a troca de registros no vetor
void SwapReg(Registro *reg1, Registro *reg2){
    analise::copias += 3;
    Registro aux = *reg1;
    LEMEMLOG((long int)(reg1),sizeof(Registro),0);

    *reg1 = *reg2;
    ESCREVEMEMLOG((long int)(reg1),sizeof(Registro),0);
    LEMEMLOG((long int)(reg2),sizeof(Registro),0);

    *reg2 = aux;
    ESCREVEMEMLOG((long int)(reg2),sizeof(Registro),0);
}

//Particao utilizada na maior parte dos métodos
void Particao(Registro *vetor, int esq, int dir, int *i, int *j){
    Registro pivo;
    *i = esq; *j = dir;
    pivo = vetor[(*i + *j)/2]; // obtem o pivo x 
    LEMEMLOG((long int)(&vetor[(*i + *j)/2]),sizeof(Registro),0);

    do{
        analise::comparacoes += 2;
        while (pivo.chave > vetor[*i].chave){
            (*i)++;
            analise::comparacoes++;
        }
        while (pivo.chave < vetor[*j].chave){
            (*j)--;
            analise::comparacoes++;
        }
        if (*i <= *j){
            SwapReg(&vetor[*i],&vetor[*j]); //Troca os valores do vetor
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

//Particao modificada para o Quicksort mediana
void ParticaoMediana(Registro *vetor, int esq, int dir, int *i, int *j){
    Registro pivo;
    Registro *part = new Registro[entradas::k];

    srand48(entradas::seed);

    //K elementos do vetor aleatoriamente escolhidos
    for(int j=0; j<entradas::k; j++){
        int rand = lrand48() % (dir-esq+1);
        part[j].chave = vetor[esq + rand].chave;
        LEMEMLOG((long int)(&vetor[esq + rand].chave),sizeof(int),0);
        ESCREVEMEMLOG((long int)(&part[j].chave),sizeof(int),0);
    }
    
    //Ordena a particao
    Selection(part,0, entradas::k-1);

    *i = esq; *j = dir;
    pivo = part[entradas::k/2]; /* obtem o pivo x */
    LEMEMLOG((long int)(&part[entradas::k/2]),sizeof(Registro),0);

    do{
        analise::comparacoes += 2;
        while (pivo.chave > vetor[*i].chave){
            (*i)++;
            analise::comparacoes++;
        }
        while (pivo.chave < vetor[*j].chave){
            (*j)--;
            analise::comparacoes++;
        }
        if (*i <= *j){
            SwapReg(&vetor[*i],&vetor[*j]); //Troca os valores do vetor
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
    delete[] part;
}

//Selection Sort
void Selection(Registro *vetor, int  esq, int dir){
    int i, j, menor;
    for(i = esq; i < dir; i++){
        menor = i;
        for(j = i+1; j <= dir; j++){
            analise::comparacoes++;
            if(vetor[j].chave < vetor[menor].chave)
                menor = j;
            
        }
        SwapReg(&vetor[i], &vetor[menor]);

    }
}

//Quicksort Recursivo
void QuicksortRecursivo(Registro *vetor, int esq, int dir){
    int i, j;
    Particao(vetor, esq, dir, &i, &j);
    if(esq < j) QuicksortRecursivo(vetor, esq, j);
    if(i < dir) QuicksortRecursivo(vetor, i, dir);
}

//Quicksort Mediana
void QuicksortMediana(Registro *vetor, int esq, int dir){
    int i, j;
    ParticaoMediana(vetor, esq, dir, &i, &j); //Particao da mediana
    if(esq < j) QuicksortMediana(vetor, esq, j);
    if(i < dir) QuicksortMediana(vetor, i, dir);

}

//Quicksort Selecao
void QuicksortSelecao(Registro *vetor, int esq, int dir){
    int i, j, tam = (dir-esq)+1;
    if(tam <=  entradas::m){
        //Ordena o vetor para tamanhos pequenos
        Selection(vetor, esq, dir);
    }else{
        Particao(vetor, esq, dir, &i, &j);
        if(esq < j) QuicksortSelecao(vetor, esq, j);
        if(i < dir) QuicksortSelecao(vetor, i, dir);
    }
    
}

//Quicksort Nao recursivo
void QuicksortNaoRecursivo(Registro *vetor, int esq, int dir){
    Pilha *pilha = new Pilha();
    Item part;
    int i, j;
    part.dir = dir;
    part.esq = esq;
    pilha->Empilha(part);

    do{
        if(dir>esq){
            Particao(vetor,esq,dir,&i,&j);
            part.dir = j;
            part.esq =  esq;
            pilha->Empilha(part);
            esq = i;
        }else{
            part = pilha->Desempilha();
            dir = part.dir;
            esq = part.esq;
        }
    }while(!pilha->Vazia());
    delete pilha;
}

//Quicksort Empilha inteligente
void QuicksortInteligente(Registro *vetor, int esq, int dir){
    Pilha *pilha = new Pilha();
    Item part;
    int i, j;
    part.dir = dir;
    part.esq = esq;
    pilha->Empilha(part);

    do{
        if(dir>esq){
            Particao(vetor,esq,dir,&i,&j);
            //Parte inteligente do quicksort nao recursivo
            if((j-esq)>(dir-i)){
                part.dir = j;
                part.esq =  esq;
                pilha->Empilha(part);
                esq = i;
            }else{
                part.dir = dir;
                part.esq = i;
                pilha->Empilha(part);
                dir = j;
            }
        }else{
            part = pilha->Desempilha();
            dir = part.dir;
            esq = part.esq;
        }
    }while(!pilha->Vazia());
    pilha->Limpa();
    delete pilha;
}

//Funcao merge do mergesort
void Merge(Registro *vetor, int const esq, int const meio, int const dir){
    //tamanhos dos vetores
    int const vetor1 = meio - esq + 1;
    int const vetor2 = dir - meio;
    
    //Registros da esquerda e direita
    Registro *esqVetor = new Registro[vetor1];
    Registro *dirVetor = new Registro[vetor2];
 
    for (int i = 0; i < vetor1; i++){
        analise::copias++;
        esqVetor[i] = vetor[esq + i];
        ESCREVEMEMLOG((long int)(&esqVetor[i]),sizeof(Registro),0);
        LEMEMLOG((long int)(&vetor[esq + i]),sizeof(Registro),0);
        
    }

    for (int j = 0; j < vetor2; j++){
        analise::copias++;
        dirVetor[j] = vetor[meio + 1 + j];
        ESCREVEMEMLOG((long int)(&dirVetor[j]),sizeof(Registro),0);
        LEMEMLOG((long int)(&vetor[meio + 1 + j]),sizeof(Registro),0);
    }
 
    int indiceVetor1  = 0, indiceVetor2 = 0; 
    int indiceMerged = esq;
 
    while (indiceVetor1  < vetor1 && indiceVetor2 < vetor2) {
        if (esqVetor[indiceVetor1 ].chave <= dirVetor[indiceVetor2].chave) {
            vetor[indiceMerged] = esqVetor[indiceVetor1 ];
            ESCREVEMEMLOG((long int)(&vetor[indiceMerged]),sizeof(Registro),0);
            LEMEMLOG((long int)(&esqVetor[indiceVetor1 ]),sizeof(Registro),0);
            indiceVetor1 ++;
        }
        else {
            vetor[indiceMerged] = dirVetor[indiceVetor2];
            ESCREVEMEMLOG((long int)(&vetor[indiceMerged]),sizeof(Registro),0);
            LEMEMLOG((long int)(&dirVetor[indiceVetor2 ]),sizeof(Registro),0);
            indiceVetor2++;
        }
        indiceMerged++;
        analise::comparacoes++;
        analise::copias++;
    }

    while (indiceVetor1  < vetor1) {
        vetor[indiceMerged] = esqVetor[indiceVetor1 ];
        ESCREVEMEMLOG((long int)(&vetor[indiceMerged]),sizeof(Registro),0);
        LEMEMLOG((long int)(&esqVetor[indiceVetor1 ]),sizeof(Registro),0);
        indiceVetor1++;
        indiceMerged++;
        analise::copias++;
    }
    
    while (indiceVetor2 < vetor2) {
        vetor[indiceMerged] = dirVetor[indiceVetor2];
        ESCREVEMEMLOG((long int)(&vetor[indiceMerged]),sizeof(Registro),0);
        LEMEMLOG((long int)(&dirVetor[indiceVetor2 ]),sizeof(Registro),0);
        indiceVetor2++;
        indiceMerged++;
        analise::copias++;
    }
    delete[] esqVetor;
    delete[] dirVetor;
}

//Funcao mergesort
void Mergesort(Registro *vetor, int const inicio, int const fim){
    if (inicio >= fim)
        return;
 
    auto meio = inicio + (fim - inicio) / 2;
    Mergesort(vetor, inicio, meio);
    Mergesort(vetor, meio + 1, fim);
    Merge(vetor, inicio, meio, fim);
}

//Funcao heap so heapsort
void Heap(Registro *vetor, int tam, int raiz){
    int maior = raiz;
    int esq = 2 * raiz + 1;
    int dir = 2 * raiz + 2;

    analise::comparacoes+=2;
    if (esq < tam && vetor[esq].chave > vetor[maior].chave)
        maior = esq;
    if (dir < tam && vetor[dir].chave > vetor[maior].chave)
        maior = dir;
    if (maior != raiz) {
        SwapReg(&vetor[raiz], &vetor[maior]);
        Heap(vetor, tam, maior);
    }
}

//Heapsort
void Heapsort(Registro *vetor, int tam){
    
    for (int i = tam / 2 - 1; i >= 0; i--)
        Heap(vetor, tam, i);
 
    for (int i = tam - 1; i >= 0; i--) {
        SwapReg(&vetor[0], &vetor[i]);
        Heap(vetor, i, 0);
    }
}
