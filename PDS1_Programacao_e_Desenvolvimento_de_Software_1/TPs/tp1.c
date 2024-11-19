#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void) {
    //system("cls");
    int tamanho;
    scanf("%i",&tamanho);

    char tabuleiro[tamanho][tamanho];

    //leitura do tabuleiro
    for(int i=0; i<tamanho; i++){
        getchar();
        for(int j=0; j<tamanho; j++){
            tabuleiro[i][j] = getchar();
            if(tabuleiro[i][j] == 'b' && i == 0){
                tabuleiro[i][j] = 'B';
            }else if(tabuleiro[i][j] == 'p' && i == tamanho-1){
                tabuleiro[i][j] = 'P';
            }
        }
    }

    //movimentaçoes
    int x0, y0, xf, yf; //x0,y0 = inicil ----- xf,yf = final
    int pretas = 0, brancas = 0;
    
    scanf("%i %i %i %i",&x0, &y0, &xf, &yf);

    while(x0 != y0 || x0 != xf || x0 != yf){
        if(xf < tamanho && xf >= 0 && yf < tamanho && yf >= 0 && tabuleiro[xf][yf] == 'o'){ //se for um quadrado escuro
            if(tabuleiro[x0][y0] == 'b'){ //se for branca comum
                if((yf == y0+1 || yf == y0-1) && (xf == x0-1)){ //movimento basico para cima
                    tabuleiro[x0][y0] = 'o';
                    tabuleiro[xf][yf] = 'b';
                }else if((yf == y0+2 || yf == y0-2) && (xf == x0-2)){ //movimento de comer peça para cima
                    if(xf == x0-2 && yf == y0+2 && (tabuleiro[x0-1][y0+1] == 'p' || tabuleiro[x0-1][y0+1] == 'P')){ //come pra direita
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0-1][y0+1] = 'o';
                        tabuleiro[xf][yf] = 'b';
                        brancas++;
                    }
                    else if(xf == x0-2 && yf == y0-2 && (tabuleiro[x0-1][y0-1] == 'p' || tabuleiro[x0-1][y0-1] == 'P')){ //come pra esquerda
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0-1][y0-1] = 'o';
                        tabuleiro[xf][yf] = 'b';
                        brancas++;
                    }
                }
            }else if(tabuleiro[x0][y0] == 'B'){ //se for dama branca
                if((xf == x0+1 || xf == x0-1) && (yf == y0-1 || yf == y0+1)){ //movimento dama
                    tabuleiro[x0][y0] = 'o';
                    tabuleiro[xf][yf] = 'B';
                }else if((xf == x0+2 || xf == x0-2) && (yf == y0-2 || yf == y0+2)){ //movimento de comer
                    if(xf == x0-2 && (tabuleiro[x0-1][y0-1] == 'p' || tabuleiro[x0-1][y0-1] == 'P')){ //come pra esquerda cima
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0-1][y0-1] = 'o';
                        tabuleiro[xf][yf] = 'B';
                        brancas++;
                    }else if(xf == x0+2 && (tabuleiro[x0+1][y0-1] == 'p' || tabuleiro[x0+1][y0-1] == 'P')){ //come pra esquerda e baixo
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0+1][y0-1] = 'o';
                        tabuleiro[xf][yf] = 'B';
                        brancas++;
                    }else if(xf == x0-2 && (tabuleiro[x0-1][y0+1] == 'p' || tabuleiro[x0-1][y0+1] == 'P')){ //come pra direita cima
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0-1][y0+1] = 'o';
                        tabuleiro[xf][yf] = 'B';
                        brancas++;
                    }else if(xf == x0+2 && (tabuleiro[x0+1][y0+1] == 'p' || tabuleiro[x0+1][y0+1] == 'P')){ //come pra direita baixo
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0+1][y0+1] = 'o';
                        tabuleiro[xf][yf] = 'B';
                        brancas++;
                    }
                }
            }else if(tabuleiro[x0][y0] == 'p'){ //se for preta comum
                if((yf == y0+1 || yf == y0-1) && (xf == x0+1)){ //movimento basico para baixo
                    tabuleiro[x0][y0] = 'o';
                    tabuleiro[xf][yf] = 'p';
                }else if((yf == y0+2 || yf == y0-2) && (xf == x0+2)){ //movimento de comer peça para baixo
                    if(xf == x0+2 && yf == y0+2 && (tabuleiro[x0+1][y0+1] == 'b' || tabuleiro[x0+1][y0+1] == 'B')){ //come pra direita
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0+1][y0+1] = 'o';
                        tabuleiro[xf][yf] = 'p';
                        pretas++;
                    }
                    else if(xf == x0+2 && yf == y0-2 && (tabuleiro[x0+1][y0-1] == 'b' || tabuleiro[x0+1][y0-1] == 'B')){ //come pra esquerda
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0+1][y0-1] = 'o';
                        tabuleiro[xf][yf] = 'p';
                        pretas++;
                    }
                }
            }else if(tabuleiro[x0][y0] == 'P'){ //se for dama preta
                if((xf == x0+1 || xf == x0-1) && (yf == y0-1 || yf == y0+1)){ //movimento dama
                    tabuleiro[x0][y0] = 'o';
                    tabuleiro[xf][yf] = 'P';
                }else if((xf == x0+2 || xf == x0-2) && (yf == y0-2 || yf == y0+2)){ //movimento de comer
                    if(xf == x0-2 && (tabuleiro[x0-1][y0-1] == 'b' || tabuleiro[x0-1][y0-1] == 'B')){ //come pra esquerda cima
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0-1][y0-1] = 'o';
                        tabuleiro[xf][yf] = 'P';
                        pretas++;
                    }else if(xf == x0+2 && (tabuleiro[x0+1][y0-1] == 'b' || tabuleiro[x0+1][y0-1] == 'B')){ //come pra esquerda e baixo
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0+1][y0-1] = 'o';
                        tabuleiro[xf][yf] = 'P';
                        pretas++;
                    }else if(xf == x0-2 && (tabuleiro[x0-1][y0+1] == 'b' || tabuleiro[x0-1][y0+1] == 'B')){ //come pra direita cima
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0-1][y0+1] = 'o';
                        tabuleiro[xf][yf] = 'P';
                        pretas++;
                    }else if(xf == x0+2 && (tabuleiro[x0+1][y0+1] == 'b' || tabuleiro[x0+1][y0+1] == 'B')){ //come pra direita baixo
                        tabuleiro[x0][y0] = 'o';
                        tabuleiro[x0+1][y0+1] = 'o';
                        tabuleiro[xf][yf] = 'P';
                        pretas++;
                    }
                }
            }   

            //verifica se fez uma dama
            if(tabuleiro[xf][yf] == 'b' && xf == 0){
                tabuleiro[xf][yf] = 'B';
                brancas++;
            }else if(tabuleiro[xf][yf] == 'p' && xf == tamanho-1){
                tabuleiro[xf][yf] = 'P';
                pretas++;
            }

        }

        //printa o tabuleiro para verificação
        // printf("\n");
        // for(int i=0; i<tamanho; i++){
        //     for(int j=0; j<tamanho; j++){
        //         printf("%c",tabuleiro[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");

        scanf("%i %i %i %i",&x0, &y0, &xf, &yf);
    }

    //placar
    printf("PRETAS %i\n",pretas);
    printf("BRANCAS %i\n",brancas);

    if(pretas > brancas){
        printf("PRETAS VENCERAM\n");
    }else if(brancas > pretas){
        printf("BRANCAS VENCERAM\n");
    }else{
        printf("EMPATE\n");
    }


    return 0;
}