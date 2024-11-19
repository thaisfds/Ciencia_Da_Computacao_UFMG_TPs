#include <stdio.h>

int main(void) {
    int numero1;
    int numero2;
    int numero3;

    scanf("%i",&numero1);
    scanf("%i",&numero2);
    scanf("%i",&numero3);

    int maior = numero1;

    if(maior < numero2){
        maior = numero2;
    }
    
    if(maior < numero3){
        maior = numero3;
    }
    printf("%i ", maior);
    return 0;
}