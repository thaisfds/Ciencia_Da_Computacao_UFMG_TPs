#include <stdio.h>

int main(void) {
    int denominador = 1, sinal =1;
    int i;
    double soma = 0.0;

    for(i=0;i<100000;i++){
        soma = soma + (4.0/denominador*sinal);
        sinal = sinal * -1;
        denominador = (denominador +2);
    }
    printf("%f\n",soma);
    
    return 0;
}