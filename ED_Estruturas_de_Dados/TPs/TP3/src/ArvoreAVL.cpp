#include "ArvoreAVL.h"

//FUNCOES NODEALV **********************************************************
NodeAVL::NodeAVL(){
    this->verb = nullptr;
    this->esq = nullptr;
    this->dir = nullptr;
}

NodeAVL::NodeAVL(Verbete *v){
    this->verb = v;
    this->esq = nullptr;
    this->dir = nullptr;
}

NodeAVL::~NodeAVL(){
    delete verb;
}

//FUNCOES DE ROTACAO, BALANCEAMENTO, E RECURSIVIDADE ARVOREALV ****************

int ArvoreAVL::FatorBalanceamento(NodeAVL *&no){
    //Retorna 0 se o nodulo nao existe
    if(!no)
        return 0;
    
    int Aesq = (!no->esq) ? 0 : (1 + Altura(no->esq));
    int Adir = (!no->dir) ? 0 : (1 + Altura(no->dir));

    return Aesq - Adir;
}

int ArvoreAVL::Altura(NodeAVL *&no){
    //Retorna 1 se o nodulo nao existe
    if(!no) 
        return 1;
    //Retorna 0 se os filhos do nodulo nao existem
    if(!no->esq && !no->dir)
        return 0;

    return 1 + std::max(Altura(no->esq),Altura(no->dir));
}

//Rotacao pra direita
void ArvoreAVL::RotacaoDireita(NodeAVL *&no){
    if(no->esq){
        NodeAVL *aux = no->esq->dir;
        no->esq->dir = no;
        no = no->esq;
        no->dir->esq = aux;
    }
}

//Rotacao pra esquerda
void ArvoreAVL::RotacaoEsquerda(NodeAVL *&no){
    if(no->dir){
        NodeAVL *aux = no->dir->esq;
        no->dir->esq = no;
        no = no->dir;
        no->esq->dir = aux;
    }
}

//Rota duplamente para a direia
void ArvoreAVL::RotacaoDDireita(NodeAVL *&no){
    RotacaoEsquerda(no->esq);
    RotacaoDireita(no);
}

//Rota duplamente para a esquerda
void ArvoreAVL::RotacaoDEsquerda(NodeAVL *&no){
    RotacaoDireita(no->dir);
    RotacaoEsquerda(no);
}

void ArvoreAVL::Balancear(){
    BalancearRecursivo(raiz);
}

//Balanceia recursivamenta a arvore
void ArvoreAVL::BalancearRecursivo(NodeAVL *&no){
    if(!no) return;
    int coeficiente = FatorBalanceamento(no); //Calcula o fator de balanceamento
    //Se o fator for 2 rota pra direita, -2 rota pra esquerda
    //Se o fator do filho a direita ou esquerda for -1, rota duplamento
    if(std::abs(coeficiente) == 2){
        if(coeficiente == 2){
            if(FatorBalanceamento(no->esq) == -1)
                RotacaoDDireita(no);
            else
                RotacaoDireita(no);
        }else if(coeficiente == -2){
            if(FatorBalanceamento(no->dir) == -1)
                RotacaoDEsquerda(no);
            else
                RotacaoEsquerda(no);
        }
    }
}

//Percorre a arvore e retorna o verbete se for encontrado
Verbete* ArvoreAVL::PesquisaRecursivo(char tipo, std::string palavra, NodeAVL *&no){
    if(no){
        PesquisaRecursivo(tipo, palavra, no->esq);
        PesquisaRecursivo(tipo, palavra, no->dir);
        if(no->verb->getTipo() == tipo && no->verb->getPalavra() == palavra)
            return no->verb;
    }
    return nullptr;

}

//Percorre toda a arvore para encontrar onde inserir o verbete
void ArvoreAVL::InsereRecursivo(Verbete *v, NodeAVL *&no){
    bool novo = false;

    if(!no){
        //Cria o no e balanceia
        no = new NodeAVL(v);
        novo = true;
        Balancear();
    }else{
        //Caso a palavra a ser inserida seja maior entra pra direita
        //Caso a palavra seja menor entra pra esquerda
        //Caso a palavra seja igual, e o tipo for igual adiciona um significado
        if(v->getPalavra() > no->verb->getPalavra()){
            InsereRecursivo(v,no->dir);
        }else if(v->getPalavra() < no->verb->getPalavra()){
            InsereRecursivo(v,no->esq);
        }else{
            if(v->getTipo() == no->verb->getTipo()){
                if(!novo)
                    no->verb->addSignificado(v->getPrimeiroSignificado());
            }else
                InsereRecursivo(v,no->dir);
        }
    }
}

//Percorre a arvore recursivamente para remover o nodulo
void ArvoreAVL::RemoveRecursivo(char tipo, std::string palavra, NodeAVL *&no){
    if(no){
        //Se a palavra for menor entra pra esquerda
        //Se a palavra for maior entra pra direita
        //Se a palavra for igual e o tipo for igual remove
        if(palavra < no->verb->getPalavra()){
            RemoveRecursivo(tipo,palavra,no->esq);
        }else if(palavra > no->verb->getPalavra()){
            RemoveRecursivo(tipo,palavra,no->dir);
        }else{
            if(no->verb->getTipo() == tipo){
                if(!no->esq && !no->dir){
                    delete no;
                    no = nullptr;
                }else if(no->esq && no->dir){
                    NodeAVL *aux = no->esq;
                    while(aux->dir)
                        aux = aux->dir;
                    Verbete *v = no->verb;
                    no->verb = aux->verb;
                    aux->verb = v;
                    RemoveRecursivo(tipo,palavra,no->esq);
                }else{
                    if(no->dir){
                        NodeAVL *aux = no; 
                        no = no->dir;
                        delete aux;
                    }else if(no->esq){
                        NodeAVL *aux = no; 
                        no = no->esq;
                        delete aux;
                    }
                }
            }
        }
    }
    Balancear(); //Balancea a arvore apos a remoção
}

//Percorre a arvore recursivamente para remover o nodulo
void ArvoreAVL::RemoveComSignificadoRecursivo(NodeAVL *&no){
    if(no){
        //Percorre toda a arvore pra esquerda e direita
        RemoveComSignificadoRecursivo(no->esq);
        RemoveComSignificadoRecursivo(no->dir);

        //Se o nodulo possuir significado apaga o verbete
        if(no->verb->temSignificados()){
            if(!no->esq && !no->dir){
                delete no;
                no = nullptr;
            }else if(no->esq && no->dir){
                NodeAVL *aux = no->esq;
                while(aux->dir)
                    aux = aux->dir;
                Verbete *v = no->verb;
                no->verb = aux->verb;
                aux->verb = v;
                RemoveComSignificadoRecursivo(no->esq);
            }else{
                if(no->dir){
                    NodeAVL *aux = no; 
                    no = no->dir;
                    delete aux;
                }else if(no->esq){
                    NodeAVL *aux = no; 
                    no = no->esq;
                    delete aux;
                }
            }
        }
        BalancearRecursivo(no); //Balanceia o no
    }
}

//Limpa toda a arvore deletando os seus nos
void ArvoreAVL::LimparRecursivo(NodeAVL *&no){
    if(!no) return;
    LimparRecursivo(no->esq);
    LimparRecursivo(no->dir);
    delete no;
}

//Imprime todos os verbetes com significados
void ArvoreAVL::ImprimirRecursivo(NodeAVL *&no){
    if(!no) return;
    ImprimirRecursivo(no->esq);
    no->verb->imprimirSignificados();
    ImprimirRecursivo(no->dir);
}



//FUNCOES PADROES ARVORE AVL *********************************************
ArvoreAVL::ArvoreAVL(){
    this->raiz = nullptr;
}

ArvoreAVL::~ArvoreAVL(){
    Limpar();
}

//Chama as funcoes recursivamente
Verbete* ArvoreAVL::Pesquisa(char tipo, std::string palavra){
    return PesquisaRecursivo(tipo, palavra, raiz);
}

void ArvoreAVL::Insere(Verbete *v){
    InsereRecursivo(v,raiz);
    Balancear();
}

void ArvoreAVL::Remove(char tipo, std::string palavra){
    RemoveRecursivo(tipo,palavra,raiz);
    Balancear();
} 

void ArvoreAVL::RemoveComSignificado(){
    RemoveComSignificadoRecursivo(raiz);
    Balancear();
}

void ArvoreAVL::Imprimir(){
    ImprimirRecursivo(raiz);
}

void ArvoreAVL::Limpar(){
    LimparRecursivo(raiz);
}
