#include <iostream>

//Registro solicitado para implementaçao do código
class Registro{
    private:
        float numeros[10];
        char reg[15][200];

    public:
        int chave;
        Registro(): chave(-1){};
        Registro(int c): chave(c){};
};