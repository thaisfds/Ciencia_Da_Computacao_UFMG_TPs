//2136 - Amigos do Habay
#include<iostream>
#include<string>

#define MAX_LISTA 10000

void quicksort(std::string vetor[], int tamanho, int inicio, int fim) {
    int i = inicio, j = fim;
    std::string pivot = vetor[(inicio+fim)/2];
    std::string temp;

    while (i <= j) {
        while (vetor[i] < pivot) i++;
            while (vetor[j] > pivot) j--;
                if (i <= j) {
                    temp = vetor[i];
                    vetor[i] = vetor[j];
                    vetor[j] = temp;
                    i++;
                    j--;
                }
    }

    if (i < fim)
        quicksort(vetor, tamanho, i, fim);
    if (j > inicio)
        quicksort(vetor, tamanho, inicio, j);
}

bool nomeExiste(std::string vetor[], std::string nome, int tam){
    for(int k=0; k<tam; k++){
        if(vetor[k] == nome)
            return true;
    }
    return false;
}

int main(){
    std::string nome, resposta, amigo = "";
    std::string sim[MAX_LISTA], nao[MAX_LISTA];
    int i = 0, j = 0, maxTam = 0;


    while(std::cin >> nome && nome != "FIM"){
        std::cin >> resposta;
        if(resposta == "YES"){
            if(nomeExiste(sim,nome,i) == false){
                sim[i] = nome;
                i++;
                if(nome.length() > maxTam){
                    amigo = nome;
                    maxTam = nome.length();
                }
            }
        }else{
            nao[j] = nome;
            j++;
        }

        quicksort(sim, i, 0, i-1);
        quicksort(nao, j, 0, j-1);    
        
    }

    for(int k=0; k<i; k++)
        std::cout << sim[k] << std::endl;
        
    for(int k=0; k<j; k++)
        std::cout << nao[k] << std::endl;

    std::cout << "\nAmigo do Habay:\n" << amigo << std::endl;

    return 0;  
}