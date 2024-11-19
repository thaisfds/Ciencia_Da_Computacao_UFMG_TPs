#include <stdio.h>

int main(void) {
    float celsius;
    int fahrenheit;
    float valor;

    scanf("%f",&celsius);

    valor = (1.8*celsius)+32;

    printf("%.0f ",valor);

    return 0;
}