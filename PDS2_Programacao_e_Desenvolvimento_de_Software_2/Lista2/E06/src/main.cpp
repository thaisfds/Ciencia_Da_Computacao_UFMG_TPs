// NÃO ALTERE ESSA LINHA
#include "avaliacao_basica_excecoes.hpp"
#include "LimitedQueue.hpp"

int main() {

    LimitedQueue *fila = nullptr;
  
    int k, max_size;
    char data;
    while (cin >> data) {   // Lendo o caractere que define o comando

        // Executando o comando informado
        switch (data) {
            
            // comando para inicializar a fila com um certo tamanho maximo
            case 'i':
                cin >> max_size;
                try{
                    fila = new LimitedQueue(max_size);
                }catch(Exceptions& e){
                    cout << e.name << endl;
                }
                break;

            // comando para inserir o inteiro k no final da fila
            case 'p': 
                cin >> k;
                try{
                    fila->push_back(k);
                }catch(Exceptions& e){
                    cout << e.name << endl;
                }
                break;

            // comando para remover o primeiro elemento da fila
            case 'o':                  
                try{
                    fila->pop_front();
                }catch(Exceptions& e){
                    cout << e.name << endl;
                }
                break;     

            // comando para imprimir o primeiro elemento da fila
            case 'f':                  
                try{
                    cout << fila->front();
                }catch(Exceptions& e){
                    cout << e.name << endl;
                }
                break;     

            // comando  imprimir o ultimo elemento da fila
            case 'l':                  
                try{
                    cout << fila->back() << endl;
                }catch(Exceptions& e){
                    cout << e.name << endl;
                }
                break;  

            // comando  imprimir toda a fila
            case 'm':                  
                try{
                    fila->print();
                }catch(Exceptions& e){
                    cout << e.name << endl;
                }
                break; 

            // comando  que busca o interiro k na fila e imprime a sua posiçao
            case 'd': 
                cin >> k;                 
                try{
                    cout << fila->find(k) << endl;
                }catch(Exceptions& e){
                    cout << e.name << endl;
                }
                break;  

            // deve chamar a funcao avaliacao_basica()
            case 'b':                  
                try{
                    avaliacao_basica();
                }catch(Exceptions& e){
                    cout << e.name << endl;
                }
                break;                              

        }
    }
    delete fila;
    return 0;
}
