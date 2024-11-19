// NÃO ALTERE ESSA LINHA
#include "avaliacao_basica_imagem.hpp"
#include "Imagem.hpp"

int main() {

    //
    // Adicione seu código aqui e faça as demais alterações necessárias
    //

    char data;
    int lim, width, height;
    Imagem imagem;
    string pixel;

    while (cin >> data) {   // Lendo o caractere que define o comando

        // Executando o comando informado
        switch (data) {
            
            // 'i' inicializar uma imagem
            case 'i':                 
                cin >> width >> height;
                imagem.initialize_image(width,height);
                break;

            // 'p' preencher uma imagem de acordo com uma matriz de pixels que será informada
            case 'p':
                
                for(int row = 0; row<height; row++){
                    for(int col = 0; col<width; col++){
                        cin >> pixel;
                        imagem.fill(row, col, pixel);
                    }
                }
                break;

            // 's' exibe a imagem seguindo formato similar ao de entrada
            case 's':                  
                imagem.show();
                break;     

            // 'g' transforma a imagem original colorida em uma imagem em escala de cinza
            case 'g':                  
                imagem.to_grayscale();
                break;  

            // 't' faz a binarização de uma imagem que está em escala de cinza
            case 't': 
                cin >> lim;                 
                imagem.grayscale_thresholding(lim);
                break;    

            // 'b' chama a funcao avaliacao_basica()
            case 'b':                  
                avaliacao_basica();
                break;                                
        }
    }


    return 0;
}