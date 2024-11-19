#include <iostream>
#include <iomanip>

#include "Drone.hpp"
#include "Ponto2D.hpp"

using namespace std;

int main() {
  
    // Lendo quantidade de drones
    int num_drones;
    cin >> num_drones;

    // Criando o vetor de ponteiros
    Drone *drones[num_drones]; 

    // Preenchendo os drones com os dados de entrada
    double x, y, raio;
    for (int i = 0; i < num_drones; i++) {
        cin >> x >> y >> raio;
        drones[i] = new Drone(i, Ponto2D(x, y), raio);
    }

    // Definindo o formato da saida
    cout << fixed << setprecision(2); 
    
    int idx;
    char data;
    while (cin >> data) {   // Lendo o caractere que define o comando

        // Executando o comando informado
        switch (data) {
            
            // Imprimindo status de todas os drones
            case 's':                 
                for (int i = 0; i < num_drones; i++)
                    drones[i]->imprimir_status();

                break;

            // Imprimindo a distancia entre todos os drones
            case 'd': 
                for (int i = 0; i < num_drones; i++)
                    for (int j = 0; j < num_drones; j++)
                        cout << drones[i]->calcular_distancia(drones[j]) << endl;
                
                break;

            // Mover drone
            case 'm':                  
                cin >> idx; // Indice da nave que vai mover

                double v, th, t; // Velocidade, Ângulo, Tempo
                cin >> v >> th >> t;

                drones[idx]->mover(v, th, t);
                
                break;     

            // Broadcast mensagem
            case 'b':                  
                cin >> idx; // Indice da nave que vai enviar mensagem
                drones[idx]->broadcast_mensagem(drones, num_drones);
                
                break;     

            // Imprimir buffer de mensagens
            case 'p':                  
                cin >> idx; // Indice da nave para recuperar mensagens
                drones[idx]->imprimir_mensagens_recebidas();
                
                break;                                

        }
    }
    
    return 0;
}
