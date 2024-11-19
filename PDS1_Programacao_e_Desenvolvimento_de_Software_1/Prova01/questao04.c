#include <stdio.h>
int main(void) {
    int x = 0, a=4, b=2;

    x = (a&1)|(b|2);
    
    printf ("%d", x);
    
    return 0;
}