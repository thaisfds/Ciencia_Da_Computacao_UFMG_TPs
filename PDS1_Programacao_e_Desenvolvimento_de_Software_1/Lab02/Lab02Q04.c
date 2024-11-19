#include <stdio.h>

int main(void) {
    int x, m2=0, m3=0, m5=0, mt=0, i=1;

    scanf("%i",&x);

    while(i<=x){
        if(i%2 == 0){m2++;}
        if(i%3 == 0){m3++;}
        if(i%5 == 0){m5++;}
        if((i%2 == 0) && (i%3 == 0) && (i%5 == 0)){mt++;}
        i++;
    }

    printf("Múltiplos de 2: %i\n",m2);
    printf("Múltiplos de 3: %i\n",m3);
    printf("Múltiplos de 5: %i\n",m5);
    printf("Múltiplos de todos: %i\n",mt);

    return 0;
}