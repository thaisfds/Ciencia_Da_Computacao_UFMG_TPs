#include <stdio.h>

int main(void) {
    int n = 233;

    do{
        printf("%i\n",n);
        n = (n>=300 && n<=400)? n+3 : n+5;
    }while(n<=457);

    return 0;
}