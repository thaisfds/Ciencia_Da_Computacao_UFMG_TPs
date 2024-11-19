#include <stdio.h>

int main(void) {
    float M[3][3] = {{8,1,32},{9,2,4},{5,6,0}};
    int n=3;
    float soma =0.0;

    for(int i=0; i<n; i++){
        soma = soma +M[i][i];
        printf("soma diagonal = %.2f \n",soma);
    }
    
    return 0;
}