#include <iostream>
#include <string>
using namespace std;

//*p = variavel
// p = endereco
//&p = ??

int main()
{
    // 1) Declare uma variavel do tipo inteiro e preencha com o valor informado na entrada
    int inteiro;
    cin >> inteiro;

    // 2) Declare um ponteiro para inteiros e inicialize com valor nulo
    int *ponteiro = nullptr;

    // 3) Declare um vetor de inteiros com tamanho informado na entrada e preencha com os dados passados
    int n;
    cin >> n;
    int vetor[n];
    for (int i = 0; i < n; i++){
        cin >> vetor[i];
    }

    // 4) Imprima o ENDERECO da variavel declarada em (1)
    cout << &inteiro << endl;

    // 5) Imprima o VALOR da variavel declarada em (1)
    cout << inteiro << endl;

    // 6) Imprima o ENDERECO da variavel declarada em (2)
    cout << &ponteiro << endl;

    // 7) Imprima o VALOR da variavel declarada em (2)
    cout << ponteiro << endl;

    // 8) Imprima o ENDERECO da variavel declarada em (3)
    cout << &vetor << endl;

    // 9) Imprima o ENDERECO da primeira posicao da variavel declarada em (3)
    cout << &vetor[0] << endl;

    // 10) Imprima o VALOR da primeira posicao da variavel declarada em (3)
    cout << vetor[0] << endl;

    // 11) Atribua o ENDERECO da variavel declarada em (1) a variavel declarada em (2)
    ponteiro = &inteiro;

    // 12) Imprima o VALOR da variavel declarada em (2)
    cout << ponteiro << endl;

    // 13) Imprima o VALOR guardado no ENDERECO apontado por (2)
    cout << *ponteiro << endl;

    // 14) Imprima o resultado da comparacao do ENDERECO de (1) e do VALOR de (2)
    if(&inteiro == ponteiro){
        cout << "1" << endl;
    }

    // 15) Coloque o VALOR '5' no ENDERECO apontado por (2)
    *ponteiro = 5;

    // 16) Imprima o VALOR da variavel declarada em (1)
    cout << inteiro << endl;

    // 17) Atribua o ENDERECO da variavel (3) a variavel declarada em (2)
    ponteiro = vetor;

    // 18) Imprima o VALOR da variavel declarada em (2)
    cout << ponteiro << endl;

    // 19) Imprima o VALOR guardado no ENDERECO apontado por (2)
    cout << *ponteiro << endl;

    // 20) Atribua o ENDERECO da primeira posicao de (3) a variavel declarada em (2)
    ponteiro = &vetor[0];

    // 21) Imprima o VALOR da variavel declarada em (2)
    cout << ponteiro << endl;

    // 22) Imprima o VALOR guardado no ENDERECO apontado por (2)
    cout << *ponteiro << endl;

    // 23) Multiplique todos os valores do vetor declarado em (3) por '10', porem manipulando apenas a variavel (2)
    for (int i = 0; i < n; i++){
        ponteiro = &vetor[i];
        *ponteiro = *ponteiro * 10;
    }

    // 24) Imprima os elementos de (3) a partir variavel do vetor utilizando a notacao [] (colchetes)
    for (int i = 0; i < n; i++){
        if(i == n-1){
            cout << vetor[i];
        }
        else{
            cout << vetor[i] << " ";
        }
    }
    cout << "\n";

    // 25) Imprima os elementos de (3) a partir variavel do vetor utilizando a notacao ponteiro/deslocamento
    // Ou seja, voce NAO deve efetivamente alterar o valor do ponteiro inicial de (3)
    for (int i = 0; i < n; i++){
        if(i == n-1){
            cout << *(vetor+i);
        }
        else{
            cout << *(vetor+i) << " ";
        }
    }
    cout << "\n";

    // 26) Imprima os elementos de (3) utilizando a variavel (2) e a notacao ponteiro/deslocamento
    // Ou seja, voce NAO deve efetivamente alterar o valor do ponteiro inicial de (3)
    ponteiro = &vetor[0];
    for (int i = 0; i < n; i++){
        if(i == n-1){
            cout << *ponteiro;
        }
        else{
        cout << *ponteiro << " ";
        }
        (ponteiro)++;
    }
    cout << "\n";

    // 27) Atribua o ENDERECO da quinta posicao de (3) a variavel declarada em (2)
    ponteiro = &vetor[4];

    // 28) Imprima o VALOR da variavel declarada em (2)
    cout << ponteiro << endl;

    // 29) Imprima o VALOR guardado no ENDERECO apontado por (2)
    cout << *ponteiro << endl;

    // 30) Imprima o VALOR guardado no ENDERECO do ponteiro (2) decrementado de 4
   cout << *(ponteiro-4) << endl;

    // 31) Declare um ponteiro para ponteiro e o inicialize com o ENDERECO da variavel (2)
    int **ponteiro2 = &ponteiro;

    // 32) Imprima o VALOR da variavel declarada em (31)
    cout << ponteiro2 << endl;

    // 33) Imprima o ENDERECO da variavel declarada em (31)
    cout << &ponteiro2 << endl;

    // 34) Imprima o VALOR guardado no ENDERECO apontado por (31)
    cout << *ponteiro2 << endl;

    // 35) Imprima o VALOR guardado no ENDERECO do ponteiro apontado por (31)
    cout << **ponteiro2 << endl;

    return 0;
}