#include <stdio.h>

int main(void) {
    int i=2, x=0;
    printf("i1 = {");
    do{
        if(!(i%15)){
            x++;
            printf("%d ",x);
        }
        ++i;
    }while(i<50);

    printf("\b}\n");

    i=0; 
    x=0;
    printf("i2 = {");
    while(i<22){
        if(!(i%8)){
            x+=1;
            printf("%d ",x);
        }
        ++i;
    }

    printf("\b}\n");

    i=0; 
    x=0;
    printf("i3 = {");
    for(i=1;i<10;i*=3){
        x++;
        printf("%d ",x);
    }

    printf("\b}\n");

    return 0;
}