#include "pokebola.hpp"
int Pokebola::count = -1;

Pokebola::Pokebola(){
    count++;
    this->id = count;
    this->pokemon = nullptr;
}

Pokebola::~Pokebola(){
    if(this->pokemon != nullptr){
        delete(this->pokemon);
    }
}

int Pokebola::getCount(){
    return this->count;
}

int Pokebola::getId(){
    return this->id;
}

PokemonCapturado* Pokebola::getPokemonCap(){
    return this->pokemon;
}

void Pokebola::guardarPokemon(){
    if(this->pokemon != nullptr){
        this->pokemon->setDormindo(true);
    }
}

Pokemon* Pokebola::liberarPokemon(){
    if(this->pokemon != nullptr){
        this->pokemon->setDormindo(false);
        return this->pokemon;
    }
    return nullptr;
}

bool Pokebola::capturar(Pokemon& pokemon){
    float capturado = static_cast<float>(rand()/RAND_MAX);
    
    if (capturado > 0.5){
        this->pokemon = new PokemonCapturado(pokemon);
        return true;
    }else{
        this->pokemon = nullptr;
        return false;
    }
}