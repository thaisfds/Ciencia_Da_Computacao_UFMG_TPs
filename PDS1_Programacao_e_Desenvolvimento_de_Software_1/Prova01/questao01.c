#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int i, a=-1, b=-1, c=0, d, e=0;
    for(i=0;i<=8;i++){
        scanf("%d", &d);
        if(a==-1 || d>a){a=d;}
        if(b==-1 || d<b){b = d;}
        e = e+1;
        c = c+d;
    }
    printf("%d %d %f",a,b, (float)c/e);
    
    return 0;
}