#include <iostream>

void imprimir(int x, int y, int r){
    std::cout << x << " " << y << " " << r << std::endl;
}

void estrela(int x, int y, int r){
    if (r > 0) {
        estrela(x-r, y+r, r / 2);
        estrela(x+r, y+r, r / 2);
        estrela(x-r, y-r, r / 2);
        estrela(x+r, y-r, r / 2);
        imprimir(x, y, r);
    }
}

int main(){
    int x = 0;
    int y = 0;
    int r = 2;
    estrela(x,y,r);
}