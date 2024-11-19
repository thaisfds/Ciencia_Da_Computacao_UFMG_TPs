#include "Drone.hpp"
#include "Ponto2D.hpp"

using namespace std;

Drone::Drone(int id, Ponto2D ponto, double raio){
    this->id = id;
    this->ponto = ponto;
    this->raio = raio;
}

void Drone::mover(double v, double th, double t){
    double distancia = v*t;

    double fx = distancia * cos(th);
    double fy = distancia * sin(th);

    this->energia -= distancia;
    if(this->energia <= 50){cout << "Alerta, energia baixa!" << endl;}

    this->ponto.x += fx;
    this->ponto.y += fy;
}

double Drone::calcular_distancia(Drone* drone){
    double distancia = this->ponto.calcular_distancia(&(drone->ponto));
    return distancia;
}

void Drone::broadcast_mensagem(Drone** drones, int n){
    string mensagem;

    for(int i=0; i<n; i++){
        if(this->id != i){
            if(this->calcular_distancia(drones[i]) <= (this->raio)){
                mensagem = "Drone: " + to_string(this->id) + ", Posição: " + this->ponto.get_dados();
                drones[i]->salvar_mensagem(mensagem);
                drones[i]->numeroMensagens++;
                if(drones[i]->numeroMensagens > 4){drones[i]->numeroMensagens = 0;}
            }
        }
    }
}

void Drone::salvar_mensagem(string mensagem){
    this->mensagensSalvas[this->numeroMensagens] = mensagem;
}

void Drone::imprimir_mensagens_recebidas(){
    cout << "Mensagens de " << this->id << ":" << endl;
    for(int i = 0; i < 5; i++){
        if(this->mensagensSalvas[i] != "vazio"){
            cout << this->mensagensSalvas[i] << endl;
        }
    }
}

void Drone::imprimir_status(){
    cout << this->id << "\t" << this->ponto.x << "\t" << this->ponto.y << "\t" << this->energia << endl;
}