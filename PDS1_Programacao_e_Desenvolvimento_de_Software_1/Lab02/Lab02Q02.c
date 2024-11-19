#include <stdio.h>
#include <math.h>

int main(void) {
    int i = 0;
    double pi = 0;
    double precisao;

    scanf("%lf",&precisao);
    do{
        pi += pow(-1,i) * 4/(2*i + 1);
        i++;
    }while(fabs(pi-M_PI) > precisao);

    printf("%i",i);

    return 0;
}