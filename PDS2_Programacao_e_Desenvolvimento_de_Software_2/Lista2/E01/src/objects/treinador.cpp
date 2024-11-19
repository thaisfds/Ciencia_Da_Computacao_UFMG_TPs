#include "treinador.hpp"

Treinador::Treinador(string nome){
    this->nome = nome;
}

Treinador::~Treinador(){
    for(HealthBall* &hb : health_balls) 
        delete hb;
    for(EvolutionBall* &eb : evolution_balls)
        delete eb;
}


HealthBall* Treinador::selecionarHealthBall(int id){
    for(HealthBall* &hb : health_balls){
        if(hb->getId() == id)
            return hb;
    }
    return nullptr;
}


EvolutionBall* Treinador::selecionarEvolBall(int id){
    for(EvolutionBall* &eb : evolution_balls){
        if(eb->getId() == id)
            return eb;
    }
    return nullptr;
}


void Treinador::adicionarPokebola(HealthBall* pokebola){
    health_balls.push_back(pokebola);
}


void Treinador::adicionarPokebola(EvolutionBall* pokebola){
    evolution_balls.push_back(pokebola);
}


void Treinador::listarPokemons(){

    cout << "Treinador: " << this->nome << endl;

    if(health_balls.empty() == true && evolution_balls.empty() == true){
        cout << "O treinador não possui pokebolas" << endl;
    }else{
        if(health_balls.empty() == false){
            for(HealthBall* &hb : health_balls){
                cout << "HealthBall ID: " << hb->getId() << endl;
                if(hb->getPokemonCap() != nullptr){
                    hb->getPokemonCap()->info();
                }else{cout << "A pokebola não possui um pokemon" << endl;}
            }
        }

        if(evolution_balls.empty() == false){
            for(EvolutionBall* &eb : evolution_balls){
                cout << "EvolutionBall ID: " << eb->getId() << endl;
                if(eb->getPokemonCap() != nullptr){
                    eb->getPokemonCap()->info();
                }else{cout << "A pokebola não possui um pokemon" << endl;}
            }
        }
    }
        
}

