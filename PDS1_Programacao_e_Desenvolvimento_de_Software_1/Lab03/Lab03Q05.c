#include <stdio.h>

int main(void) {
    int linhas, colunas, maior;

    scanf("%i",&linhas);
    scanf("%i",&colunas);
    
    int matriz[linhas][colunas];

    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            scanf("%i", &matriz[i][j]);
        }
    }

    maior = matriz[0][0];

    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            if(maior < matriz[i][j]){maior = matriz[i][j];}
        }
    }

    printf("%i",maior);
    
    return 0;
}