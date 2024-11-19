#define DOCTEST_CONFIG_IMPEMENT_WITH_MAIN

#include "mesa.hpp"
#include "doctest.h"
#include "vector"

#include "mesa.hpp"

//Testes Mesa::Mesa

//Nome dos jogadores
//Distribuiçao de 7 cartas para cada
TEST_CASE("01 - Distribuir cartas iniciais"){
    vector<Jogador*> jogadores;
    vector<Regra*> regras;

    Jogador* temp1 = new Jogador("Jogador 1");
    Jogador* temp2 = new Jogador("Jogador 2");

	jogadores.push_back(temp1);
    jogadores.push_back(temp2);

    Mesa mesa(jogadores, regras);

    CHECK(temp1->getNumeroDeCartas() == 7);

}

TEST_CASE("02 - Get Nome"){
    vector<Jogador*> jogadores;
    vector<Regra*> regras;

    Jogador* temp1 = new Jogador("Jogador 1");
    Jogador* temp2 = new Jogador("Jogador 2");

	jogadores.push_back(temp1);
    jogadores.push_back(temp2);

    Mesa mesa(jogadores, regras);

    CHECK(temp1->getNome() == "Jogador 1");

}

TEST_CASE("03 - Numero de cartas no baralho"){
    vector<Jogador*> jogadores;
    vector<Regra*> regras;

    Jogador* temp1 = new Jogador("Jogador 1");
    Jogador* temp2 = new Jogador("Jogador 2");

	jogadores.push_back(temp1);
    jogadores.push_back(temp2);

    Mesa* mesa = new Mesa(jogadores, regras);

    CHECK(mesa->getNumCartasBaralho() == 93);
    delete mesa;

}

TEST_CASE("04 - Regra ta ativa"){
    vector<Jogador*> jogadores;
    vector<Regra*> regras;

    Jogador* temp1 = new Jogador("Jogador 1");
    Jogador* temp2 = new Jogador("Jogador 2");

	jogadores.push_back(temp1);
    jogadores.push_back(temp2);

    regras.push_back(new Regra("JogarDepoisDeComprar", "Descricao 1"));
    Mesa mesa(jogadores, regras);

    CHECK(mesa.regraTaAtivada("JogarDepoisDeComprar"));

}

TEST_CASE("05 - Gerenciar partida"){
    vector<Jogador*> jogadores;
    vector<Regra*> regras;

    Jogador* temp1 = new Jogador("Jogador 1");
    Jogador* temp2 = new Jogador("Jogador 2");

	jogadores.push_back(temp1);
    jogadores.push_back(temp2);

    Mesa mesa(jogadores, regras);

    temp1->limparCartas();
    CHECK(mesa.gerenciarPartida() == temp1);

}

TEST_CASE("06 - Printar Info"){
    vector<Jogador*> jogadores;
    vector<Regra*> regras;

    Jogador* temp1 = new Jogador("Jogador 1");
    Jogador* temp2 = new Jogador("Jogador 2");

	jogadores.push_back(temp1);
    jogadores.push_back(temp2);

    Mesa mesa(jogadores, regras);

    mesa.printarInfo();

}

TEST_CASE("07 - MoverProLixo"){
    vector<Jogador*> jogadores;
    vector<Regra*> regras;

    Jogador* temp1 = new Jogador("Jogador 1");
    Jogador* temp2 = new Jogador("Jogador 2");

    CartaEspecial* c1 = new CartaEspecial(6, Cor::VERMELHO);

	jogadores.push_back(temp1);
    jogadores.push_back(temp2);

    Mesa mesa(jogadores, regras);

    mesa.moverProLixo(c1);
}

TEST_CASE("08 - Proximo Jogador"){
    vector<Jogador*> jogadores;
    vector<Regra*> regras;

    Jogador* temp1 = new Jogador("Jogador 1");
    Jogador* temp2 = new Jogador("Jogador 2");

	jogadores.push_back(temp1);
    jogadores.push_back(temp2);

    Mesa mesa(jogadores, regras);
    mesa.proxJogador();

}

TEST_CASE("09 - Efeitos"){
    vector<Jogador*> jogadores;
    vector<Regra*> regras;

    Jogador* temp1 = new Jogador("Jogador 1");
    Jogador* temp2 = new Jogador("Jogador 2");

	jogadores.push_back(temp1);
    jogadores.push_back(temp2);

    Mesa mesa(jogadores, regras);
    
    mesa.efeitoReverter();
    mesa.efeitoComprarCarta(2, temp1);

}