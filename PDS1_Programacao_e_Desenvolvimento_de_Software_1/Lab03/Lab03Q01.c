#include <stdio.h>

int main(void) {
    int A, B, n, d, primo;

    while(A<=0 || A>=10000 || B<=0 || B>=10000){
        scanf("%i",&A);
        scanf("%i",&B);
    }
    
    for(n = A; n <= B; n++){
        primo = 0;
        for(d = 2; d < n; d++){
            if(n%d == 0){primo++;}
        }
        if(primo==0 && n!=1){printf("%i\n",n);}
    }
    
    return 0;
}