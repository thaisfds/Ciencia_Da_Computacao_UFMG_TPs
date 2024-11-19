#include <stdio.h>

int main(void) {
    int a=22,b=6;

    a^=b;
    b^=a;
    a^=b;

    printf("%d e %d",a,b);
    printf("%d",a);
    
    return 0;
}