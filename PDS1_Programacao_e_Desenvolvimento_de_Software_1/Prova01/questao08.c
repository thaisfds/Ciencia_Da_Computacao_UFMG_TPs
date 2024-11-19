/*
Com relação aos tipos de dados int, double e float pode-se dizer

I. São capazes de representar os mesmos valores (F)

II. int e double são capazes de representar os mesmos valores (F)

III. Todo valor que pode ser armazenado em double pode ser armazenado em float (F - double maior que float)

IV. Todo valor que pode ser armazenado em float pode ser armazenado em double (V)

V. float somente pode ser usado quando os valores não são inteiros (F - precisa de um float)
*/

#include <stdio.h>
int main(void) {
    int a = 3;
    float b = 2;
    float x;

    x = a/b;
    
    printf ("%f", x);
    
    return 0;
}