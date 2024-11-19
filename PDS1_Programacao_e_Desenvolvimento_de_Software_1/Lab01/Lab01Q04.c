#include <stdio.h>

int main(void) {
    int reais;
    float resto;

    scanf("%i",&reais);

    if(reais/100 >= 1){
        resto = reais/100;
        printf("100: %g\n",resto);
        reais -= 100*resto;
    } else{printf("100: 0\n");}
    if(reais/50 >= 1){
        resto = reais/50;
        printf("50: %g\n",resto);
        reais -= 50*resto;
    }else{printf("50: 0\n");}
    if(reais/20 >= 1){
        resto = reais/20;
        printf("20: %g\n",resto);
        reais -= 20*resto;
    }else{printf("20: 0\n");}
    if(reais/10 >= 1){
        resto = reais/10;
        printf("10: %g\n",resto);
        reais -= 10*resto;
    }else{printf("10: 0\n");}
    if(reais/5 >= 1){
        resto = reais/5;
        printf("5: %g\n",resto);
        reais -= 5*resto;
    }else{printf("5: 0\n");}
    if(reais/2 >= 1){
        resto = reais/2;
        printf("2: %g\n",resto);
        reais -= 2*resto;
    }else{printf("2: 0\n");}
    if(reais/1 >= 1){
        resto = reais/1;
        printf("1: %g\n",resto);
        reais -= 1*resto;
    }else{printf("1: 0\n");}

    return 0;
}