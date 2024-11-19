#include <stdio.h>

int main(void) {
    int n1,n2;

    scanf("%i",&n1);
    int AEDS1[n1];

    for(int i=0; i<n1; i++){
        scanf("%i",&AEDS1[i]);
    }

    scanf("%i",&n2);
    int calculo1[n2];

    for(int i=0; i<n2; i++){
        scanf("%i",&calculo1[i]);
    }

    for(int i=0; i<n1; i++){
        for(int j=0; j<n2; j++){
            if(AEDS1[i]==calculo1[j]){printf("%i\n",AEDS1[i]);}
        }
    }
    
    return 0;
}