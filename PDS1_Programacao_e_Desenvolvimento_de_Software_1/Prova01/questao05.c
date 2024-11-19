#include <stdio.h>
int main(void) {
    int x, a=2, b=1;

    x = (a&&b)&(a||b);
    
    printf ("%d", x);
    
    return 0;
}