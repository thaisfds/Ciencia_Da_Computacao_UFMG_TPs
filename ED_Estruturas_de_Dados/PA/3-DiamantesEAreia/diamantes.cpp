//1069 - Diamanates e Areia
#include<iostream>
#include<string>

class Caracter{
    public:
        char item;
        Caracter *prox;

        Caracter(){
            item = ' ';
            prox = nullptr;
        }
        friend class PilhaEncadeada;
};

class PilhaEncadeada{

    private:
    int tamanho;
    Caracter* topo;

    public:

    PilhaEncadeada(){
        topo = nullptr;
        tamanho = 0;
    }

    virtual ~PilhaEncadeada(){
        Limpa();
    }

    int getTamanho(){
        return tamanho;
    }

    bool Vazia(){
        return (tamanho == 0);
    }

    void Empilha(char item){
        Caracter *nova = new Caracter();
        nova->item = item;
        nova->prox = topo;
        topo = nova;
        tamanho++;
    }

    char Desempilha(){
        char aux; Caracter*p;

        if(tamanho ==0) return ' ';

        aux = topo->item;
        p = topo;
        topo = topo->prox;
        delete p;
        tamanho --;

        return aux;
    }

    void Limpa(){
        while(!Vazia())
            Desempilha();
    }

};

// int diamante(std::string mina){
//     int diamante = 0;
//     PilhaEncadeada *Garimpo = new PilhaEncadeada;

//     for(int i = 0; i < mina.length(); i++){
//         if(mina[i] == '<'){
//             Garimpo->Empilha(mina[i]);
//         }else if(mina[i] == '>'){
//             if(Garimpo->Desempilha() == '<'){
//                 diamante++;
//             }
//         }
//     }
//     delete Garimpo;
//     return diamante;
// }

int main(){
    int N;
    std::cin >> N;
    getchar();

    std::string Mina[N], aux;

    PilhaEncadeada *Garimpo = new PilhaEncadeada();

    for(int i=0; i<N; i++){
        std::getline(std::cin,Mina[i]);
    }

    for(int i=0; i<N; i++){
        aux = Mina[i];
        int diamante = 0;
        int tamanho = Mina[i].length();
        
        for(char j = 0; j < tamanho; j++){
            if(aux[j] == '<'){
                Garimpo->Empilha(aux[j]);
            }else if(aux[j] == '>'){
                if(Garimpo->Desempilha() == '<'){
                    diamante++;
                }
            }
        }
        std::cout << diamante << std::endl;
        Garimpo->Limpa();
    }

    delete Garimpo;
    return 0;
}
