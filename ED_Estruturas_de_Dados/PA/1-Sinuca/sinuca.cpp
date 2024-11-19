//2466 - Sinuca
#include <iostream>

int main(){
    int N;
    std::cin >> N;

    int** fileira = new int*[N];

    for(int i = 0; i < N; i++){
        fileira[i] = new int[N-i];
        std::cin >> fileira[0][i];
    }

    for(int i = 1; i < N; i++){
        for(int j = 0; j < N-i; j++){
            if(fileira[i-1][j] == fileira[i-1][j+1]){
                fileira[i][j] = 1;
            }else{
                fileira[i][j] = -1;
            }
        }
    }

    if(fileira[N-1][0] == -1) std::cout << "branca" << std::endl;
    else std::cout << "preta" << std::endl;

    for(int i = 0; i < N; i++){
        delete[] fileira[i];
    }
    delete fileira;

    return 0;
}