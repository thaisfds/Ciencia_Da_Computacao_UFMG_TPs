//1030 - A Lenda de Flavious Josephus
#include <iostream>

int sobrevive(int n, int k){
    if(n == 1){
        return 0;
    }else{
        int s = sobrevive(n - 1, k);
        return ((s + k) % n);
    }
}


int main(){
    int NC, n, k, sobrevivente;
    std::cin >> NC;

    for(int i=0 ; i<NC ; i++){
        std::cin >> n >> k;
        sobrevivente = sobrevive(n,k);
        std::cout << "Case " << i+1 << ": " << sobrevivente+1 << std::endl;
    }
}