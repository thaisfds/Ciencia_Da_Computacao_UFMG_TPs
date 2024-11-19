/*
Todo programa está susceptível à presença de erros (bugs). 
Um dos problemas mais catastróficos para a estabilidade de um sistema de computador 
é o loop infinito quando esse não é o objetivo do programa. 
Esse tipo de erro pode ocorrer por diversas razões. 
Dentre as alternativas a seguir, assinale as alternativas que ocasionam um loop infinito:

a.Esquecer-se de especificar o elemento de “incremento” em um loop for (gera loop)
b.Omitir elemento condicional do loop for (gera loop)
c.Esquecer-se da inicialização de variável de controle em loop for
d.Condição em loop for nunca se torna verdadeira
e.Condição em loop while permanece verdadeira (gera loop)
*/

#include <stdio.h>

int main(void) {

    for( int i=0; ; i++){
        printf("Loop\n");
    }
    
    return 0;
}