#include <iostream>
using namespace std;

class Node{
    public:
    int chave;
    Node *esq;
    Node *dir;
    int altura;
};

int max(int a, int b);

// Calculate altura
int altura(Node *N){
    if (N == NULL)
        return 0;
    return N->altura;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

// New node creation
Node *newNode(int chave){
    Node *node = new Node();
    node->chave = chave;
    node->esq = NULL;
    node->dir = NULL;
    node->altura = 1;
    return (node);
}

// Rotate dir
Node *dirRotate(Node *y){
    Node *x = y->esq;
    Node *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = max(altura(y->esq),altura(y->dir)) + 1;
    x->altura = max(altura(x->esq),altura(x->dir)) + 1;
    return x;
}

// Rotate esq
Node *esqRotate(Node *x){
    Node *y = x->dir;
    Node *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max(altura(y->esq), altura(y->dir)) + 1;
    return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node *N){
    if (N == NULL)
        return 0;
    return altura(N->esq) - altura(N->dir);
}

// Insert a node
Node *insertNode(Node *node, int chave){
    
    if (node == NULL)
        return (newNode(chave));
    if (chave < node->chave)
        node->esq = insertNode(node->esq, chave);
    else
        node->dir = insertNode(node->dir, chave);
    
    return node;
    
    node->altura = 1 + max(altura(node->esq), altura(node->dir));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1){
        if (chave < node->esq->chave){
            return dirRotate(node);
        }
        else if (chave > node->esq->chave){
            node->esq = esqRotate(node->esq);
            return dirRotate(node);
        }
    }
    if (balanceFactor < -1){
        if (chave > node->dir->chave){
            return esqRotate(node);
        }
        else if (chave < node->dir->chave){
            node->dir = dirRotate(node->dir);
            return esqRotate(node);
        }
    }
    return node;
}

// Limpa os nodes
void limpa(Node *root){
    if(root != nullptr){
        limpa(root->esq);
        limpa(root->dir);
        delete root;
    }
}

void pegarPosicao(Node *root, int numero, int *inicio, int *fim, int *i){
    if (root != nullptr){
        pegarPosicao(root->esq, numero, inicio, fim, i);
        if(root->chave == numero && *inicio == -1)
            *inicio = *i;
        if(root->chave == numero)
            *fim = *i;
        (*i)++;
        pegarPosicao(root->dir, numero, inicio, fim, i);
    }
}

int main(){
    int n,numero, inicio, fim, i;
    while(cin>>n){
        i = 0;
        Node *root = NULL;
        for(int i=0; i<n; i++){
            cin >> inicio;
            cin >> fim;
            int j = inicio;
            while(j <= fim){
                root = insertNode(root, j);
                j++;
            }
        }

        inicio = -1; fim = -1;
        cin >> numero;

        pegarPosicao(root,numero, &inicio, &fim, &i);

        if(inicio != -1)
            cout << numero << " found from " << inicio << " to " << fim << endl;
        else
            cout << numero << " not found" << endl;

        limpa(root);
    }
}