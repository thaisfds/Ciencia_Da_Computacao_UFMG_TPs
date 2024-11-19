//1861 - O Hall dos Assassinos
#include <iostream>

using namespace std;

class TipoNo{
    public:
        TipoNo(){
            nome = "";
            kills = 0;
            morto = false;
            esq = nullptr;
            dir = nullptr;
        }

    private:
        string nome;
        int kills;
        bool morto;
        TipoNo *esq;
        TipoNo *dir;
        friend class ArvoreBinaria;
};

class ArvoreBinaria{
    public:
        ArvoreBinaria() { raiz = nullptr; }
        ~ArvoreBinaria() { Limpa(); }
        void Insere(string nome, int kills, bool morto){
            InsereRecursivo(raiz, nome, kills, morto);
        }
        void Limpa(){
            ApagaRecursivo(raiz);
            raiz = nullptr;
        }
        void Imprime(){
            InOrdem(raiz);
        }

    private:
        TipoNo *raiz;
        void InsereRecursivo(TipoNo *&p, string nome, int kills, bool morto){
            if (p == nullptr){
                p = new TipoNo();
                p->nome = nome;
                p->kills = kills;
                p->morto = morto;
            }
            else{
                if(nome == p->nome){
                    if(kills == 1)
                        p->kills++;
                    else
                        p->morto = true;

                }else if (nome < p->nome)
                    InsereRecursivo(p->esq, nome, kills, morto);
                else
                    InsereRecursivo(p->dir, nome, kills, morto);
            }
        }
        void ApagaRecursivo(TipoNo *p){
            if (p != nullptr){
                ApagaRecursivo(p->esq);
                ApagaRecursivo(p->dir);
                delete p;
            }
        }
        void InOrdem(TipoNo * p){
            if (p != nullptr){
                InOrdem(p->esq);
                if(p->morto == false)
                    cout << p->nome << " " << p->kills << endl;
                InOrdem(p->dir);
            }
        }
        
};

int main(){
    std::string nome;
    ArvoreBinaria T;
    TipoNo *pessoa;

    while (std::cin >> nome){
        T.Insere(nome,1,false);
        std::cin >> nome;
        T.Insere(nome,0,true);
    }

    cout << "HALL OF MURDERERS" << endl;
    T.Imprime();
    T.Limpa();
    delete pessoa;
    
    return 0;   
}