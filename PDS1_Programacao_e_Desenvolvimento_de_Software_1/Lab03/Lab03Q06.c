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

    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%i ", (-1) * matriz[i][j]);
        }
        printf("\n");
    }


    
    return 0;
}