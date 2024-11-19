#include <stdio.h>

int main(void) {
    int n, x0, x1, xn1, xn2;
    int xn = 0;

    scanf("%i",&n);
    scanf("%i",&x0);
    scanf("%i",&x1);

    printf("X0: %i\n",x0);
    printf("X1: %i\n",x1);

    xn1 = x1;
    xn2 = x0;

    for(int i=2; i<=n; i++){
        xn = 4*xn1 - 2*xn2;
        xn2 = xn1;
        xn1 = xn;    
        printf("X%i: %i\n",i,xn);
    }
    return 0;
}