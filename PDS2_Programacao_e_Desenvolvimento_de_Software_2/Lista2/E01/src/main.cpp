#include "evolutionBall.hpp"
#include "healthBall.hpp"
#include "treinador.hpp"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <string>
#include <cmath>

/**
 * @brief Adiciona N pokebolas para o treinador, onde metade serão
 * HealthBall e a outra metade EvolutionBall
 * @param t Treinador que será atualizado com novas pokebolas
 * @param numHealthBalls O número de evolution balls adicionadas
 * @param numEvolBalls O número de health balls adicionadas
 */
void adicionarPokebolas(Treinador& t, int numHealthBalls, int numEvolBalls) {
    for(int i = 0; i < numHealthBalls; i++) {
        HealthBall* m =  new HealthBall(i + 1);
        t.adicionarPokebola(m);
    }

    for(int i = 0; i < numEvolBalls; i++) {
        double taxaPoder = 1.0/(i + 1);
        EvolutionBall* e = new EvolutionBall(taxaPoder);
        t.adicionarPokebola(e);
    }
}

/**
 * @brief Recebe a entrada do usuário para criar uma nova instância de 
 * pokémon
 * @return Pokemon criado com as entradas do usuário
 */
Pokemon criarPokemon() {
    std::string pokName;
    std::string pokTipo;
    std::string pokEvol;
    double pokAtaque;
    double pokDefesa;
    double saude;

    std::cin >> pokName >> pokTipo >> pokAtaque >> pokDefesa >> pokEvol >> saude;
    return Pokemon(pokName, pokTipo, pokEvol, pokAtaque, pokDefesa, saude);
}

/**
 * @brief Tenta capturar um pokemon específico
 * @param pokebola Pokebola que será usada
 * @param pokemon Pokemon que será capturado
 */
void capturarPokemon(Pokebola* pokebola, Pokemon& pokemon) {
    if (pokebola->capturar(pokemon))
        std::cout << "Pokémon " << pokemon.getNome() << " capturado." << std::endl;
    else
        std::cout << "Pokémon " << pokemon.getNome() << " NÃO capturado." << std::endl;
}

/**
 * @brief Tenta capturar uma sequencia de pokemons criados
 * @param t Treinador que será atualizado com novos pokemons nas pokebolas
 * caso capturados
 */
void adicionarPokemons(Treinador& t) {
    bool continuar = true;
    int id;

    while (continuar) {
        char command;
        std::cin >> command;

        switch (command) {
            case 'e': { // Usa uma evolution ball para capturar
                std::cin >> id;
                Pokemon pokemon = criarPokemon();
                Pokebola* pok = t.selecionarEvolBall(id);
                capturarPokemon(pok, pokemon);
                break;
            }        
            case 'h': { // Usa uma health ball para capturar
                std::cin >> id;
                Pokemon pokemon = criarPokemon();
                Pokebola* pok = t.selecionarHealthBall(id);
                capturarPokemon(pok, pokemon);
                break;
            }
            case 'q': { // Encerra o processo de captura
                continuar = false;
                break;
            }
        }
    }
}

/**
 * @brief Tenta evoluir um pokémon de uma EvolutionBall
 * @param pokebola EvolutionBall
 */
void evoluirPokemon(EvolutionBall* pokebola) {
    std::cout << "EvolutionBall " << pokebola->getId() << std::endl;
    if (pokebola->evoluirPokemon()) {
        Pokemon* pokemon = pokebola->liberarPokemon();
        pokemon->info();
        pokebola->guardarPokemon();
    }
    else {
        std::cout << "Pokémon NÃO evoluído." << std::endl;
    }
}

/**
 * @brief Tenta recupear um polémon de uma HealthBall
 * @param pokebola HealthBall
 */
void recuperarPokemon(HealthBall* pokebola) {
    std::cout << "HealthBall " << pokebola->getId() << std::endl;
    if (pokebola->recuperarPokemon()) {
        Pokemon* pokemon = pokebola->liberarPokemon();
        pokemon->info();
        pokebola->guardarPokemon();
    }
    else
        std::cout << "Pokémon NÃO recuperado." << std::endl;
}

/**
 * @brief Utiliza as ações das pokebolas
 * @param t Treinador que possui as pokebolas
 */
void acoes(Treinador& t) {
    bool continuar = true;
    int id;

    while (continuar) {
        char command;
        std::cin >> command;
        
        switch (command) {
            case 'e': { // Evolui um pokémon de uma evolution ball
                std::cin >> id;
                EvolutionBall* pokebola = t.selecionarEvolBall(id);
                evoluirPokemon(pokebola);
                break;
            }   

            case 'h': { // Recupera a saúde de um pokémon de uma health ball
                std::cin >> id;
                HealthBall* pokebola = t.selecionarHealthBall(id);
                recuperarPokemon(pokebola);
                break;
            }

            case 'i': { // Pausa o programa por M milisegundos (M é definido pelo "interval")
                int intervalMilisseg;
                std::cin >> intervalMilisseg;
                std::cout << "Intervalo " << intervalMilisseg << " milisegundos" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(intervalMilisseg));
                break;
            }

            case 'q': { // Encerra o processo de ações com as pokébolas
                continuar = false;
                break;
            }
        }
    }
}

int main() {
    // Seta a seed para gerar sempre os mesmos números "aleatórios"
    srand(5201);
    
    std::string nome;
    int numEvolBalls;
    int numHealthBalls;

    std::cin >> nome >> numHealthBalls >> numEvolBalls;

    Treinador t(nome);

    adicionarPokebolas(t, numHealthBalls, numEvolBalls);
    t.listarPokemons();
    std::cout << "-------------" << std::endl;
    adicionarPokemons(t);
    std::cout << "-------------" << std::endl;
    t.listarPokemons();
    std::cout << "-------------" << std::endl;
    acoes(t);

    return 0;
}