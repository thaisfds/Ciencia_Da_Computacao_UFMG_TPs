//1191 - Recuperacao da Arvore
#include<iostream>

class Letra{
    private:
        char item;
        Letra *esq;
        Letra *dir;
        friend class ArvoreBinaria;

    public:
        Letra(){
            item = ' ';
            esq = NULL;
            dir = NULL;
        }

        Letra(char item){
            this->item = item;
            esq = NULL;
            dir = NULL;
        }
        char getChar(){
            return item;
        }
        void setEsquerda(Letra* letra){
            this->esq = letra;
        }
        void setDireita(Letra* letra){
            this->dir = letra;
        }
        
        
};

int pesquisar(std::string palavra, int inicio, int fim, char valor){
    int i;
    for (i = inicio; i <= fim; i++){
        if (palavra[i] == valor)
            return i;
    }
}



Letra* reconstruirArvore(std::string pre, std::string in, int inicio, int final){
    static int preIndex = -1;
 
    if (inicio > final)
        return NULL;
 
    Letra *novaLetra = new Letra(pre[preIndex++]);
 
    if (inicio == final)
        return novaLetra;

    int posicaoLetra = pesquisar(in, inicio, final, novaLetra->getChar());
 
    novaLetra->setEsquerda(reconstruirArvore(in, pre, inicio, posicaoLetra - 1));
    novaLetra->setDireita(reconstruirArvore(in, pre, posicaoLetra + 1, final));
 
    return novaLetra;
}

void Imprimir(Letra* raiz){
    if (raiz == NULL)
        return;
 
    printInorder(raiz->left);
 
    std::cout << node->data << " ";
 
    printInorder(node->right);
}

int main(){
    std::string pre, in;
    
    std::cin >> pre;
    std::cin >> in;

    Letra* raiz = reconstruirArvore(pre,in,0,pre.length());

    Imprimir(raiz);

    return 0;
}