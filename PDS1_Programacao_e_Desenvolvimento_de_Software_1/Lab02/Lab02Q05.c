#include <stdio.h>

int main(void) {
    int n, soma=0;

    scanf("%i",&n);

    for(int i=1; i<=n; i++){
        soma += i;
    }

    printf("Soma: %i\n",soma);

    return 0;
}