#include "doctest.h"
#include "jogador.hpp"

TEST_CASE("Teste 01 - Tem carta válida"){
	Jogador j = Jogador("lucas");
	Carta* c1 = new CartaNormal(7,Cor::AZUL);
	Carta* c2 = new CartaEspecial(11,Cor::AMARELO);
	Carta* c3 = new CartaEspecial(14,Cor::BRANCO);
	j.adicionarCarta(c1);
	j.adicionarCarta(c2);
	j.adicionarCarta(c3);

	Carta* cartaDaMesa = new CartaNormal(7,Cor::AMARELO);

	CHECK(j.temCartaValida(cartaDaMesa,0));
}

TEST_CASE("Teste 02 - Não tem carta válida"){
	Jogador j = Jogador("lucas");
	Carta* c1 = new CartaNormal(7,Cor::AZUL);
	Carta* c2 = new CartaEspecial(11,Cor::AMARELO);
	Carta* c3 = new CartaEspecial(10,Cor::VERDE);
	j.adicionarCarta(c1);
	j.adicionarCarta(c2);
	j.adicionarCarta(c3);

	Carta* cartaDaMesa = new CartaNormal(1,Cor::VERMELHO);

	CHECK_FALSE(j.temCartaValida(cartaDaMesa,0));
}

TEST_CASE("Teste 03 - GetNumeroDeCartas"){
	Jogador j = Jogador("lucas");
	Carta* c1 = new CartaNormal(7,Cor::AZUL);
	Carta* c2 = new CartaEspecial(11,Cor::AMARELO);
	Carta* c3 = new CartaEspecial(14,Cor::BRANCO);
	j.adicionarCarta(c1);
	j.adicionarCarta(c2);
	j.adicionarCarta(c3);

	CHECK(j.getNumeroDeCartas() == 3);
}

TEST_CASE("Teste 04 - GetNome"){
	Jogador j = Jogador("lucas");
	Carta* c1 = new CartaNormal(7,Cor::AZUL);
	Carta* c2 = new CartaEspecial(11,Cor::AMARELO);
	Carta* c3 = new CartaEspecial(14,Cor::BRANCO);
	j.adicionarCarta(c1);
	j.adicionarCarta(c2);
	j.adicionarCarta(c3);

	CHECK(j.getNome() == "lucas");
}

TEST_CASE("Teste 05 - Limpar Cartas"){
	Jogador j = Jogador("lucas");
	Carta* c1 = new CartaNormal(7,Cor::AZUL);
	Carta* c2 = new CartaEspecial(11,Cor::AMARELO);
	Carta* c3 = new CartaEspecial(14,Cor::BRANCO);
	j.adicionarCarta(c1);
	j.adicionarCarta(c2);
	j.adicionarCarta(c3);

	j.limparCartas();

	CHECK(j.getNumeroDeCartas() == 0);	
}

TEST_CASE("Teste 06 - Limpar Cartas"){
	Jogador j = Jogador("lucas");
	Carta* c1 = new CartaNormal(7,Cor::AZUL);
	Carta* c2 = new CartaEspecial(11,Cor::AMARELO);
	Carta* c3 = new CartaEspecial(14,Cor::BRANCO);
	j.adicionarCarta(c1);
	j.adicionarCarta(c2);
	j.adicionarCarta(c3);

	j.mostrarCartas();
}

TEST_CASE("Teste 07 - Limpar Cartas"){
	Jogador j = Jogador("lucas");
	Carta* c1 = new CartaNormal(7,Cor::AZUL);
	Carta* c2 = new CartaEspecial(11,Cor::AMARELO);
	Carta* c3 = new CartaEspecial(14,Cor::BRANCO);
	j.adicionarCarta(c1);
	j.adicionarCarta(c2);
	j.adicionarCarta(c3);

	CHECK(j.temCarta("1"));
}

TEST_CASE("Teste 08 - Limpar Cartas"){
	Jogador j = Jogador("lucas");
	Carta* c1 = new CartaNormal(7,Cor::AZUL);
	Carta* c2 = new CartaEspecial(11,Cor::AMARELO);
	Carta* c3 = new CartaEspecial(14,Cor::BRANCO);
	j.adicionarCarta(c1);
	j.adicionarCarta(c2);
	j.adicionarCarta(c3);

	CHECK_THROWS_AS(j.temCarta("3"), ValorCartaInvalido);
}

TEST_CASE("Teste 09 - Limpar Cartas"){
	Jogador j = Jogador("lucas");
	j.ajuda();
}

TEST_CASE("Teste 10 - Limpar Cartas"){
	Jogador j = Jogador("lucas");
	j.regras();
}
