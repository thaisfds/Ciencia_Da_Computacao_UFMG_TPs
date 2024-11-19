#include <stdio.h>

int main(void) {
    int x[10], y[10];

    for(int i=0; i<10; i++){
        scanf("%i",&x[i]);
    }

    for(int i=0,j=9; i<10; i++,j--){
        y[i] = x[j];
    }

    for(int i=0; i<10; i++){
        printf("%i\n",y[i]);
    }
    
    return 0;
}