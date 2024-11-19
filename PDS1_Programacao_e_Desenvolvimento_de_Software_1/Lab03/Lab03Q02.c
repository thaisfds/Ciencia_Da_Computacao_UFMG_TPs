#include <stdio.h>

int main(void) {
    int n, fib[800];
    fib[0] = 0;
    fib[1] = 1;
    fib[2] = 1;

    scanf("%i",&n);

    while(n>=0 && n<=800){
        if(n>2){
            for(int i = 3; i <= n; i++){
                fib[i] = fib[i-1] + fib[i-2];  
            }     
        }
        printf("%i\n",fib[n]);
        scanf("%i",&n);
    }
    
    return 0;
}