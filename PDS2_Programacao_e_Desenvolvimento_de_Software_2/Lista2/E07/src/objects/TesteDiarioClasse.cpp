#include "doctest.h"
#include "DiarioClasse.hpp"

TEST_CASE("Teste 05 - Nota Exame Especial maior que 100") {
  DiarioClasse diario;
  CHECK_THROWS_AS(diario.determinarAprovacao(50, 120, 1), ExcecaoNotaEspecialInvalida);

}

TEST_CASE("Teste 06 - Nota do Semestre Negativa") {
  DiarioClasse diario;
  CHECK_THROWS_AS(diario.determinarAprovacao(-10, 60, 1), ExcecaoNotaSemestreInvalida);

}

TEST_CASE("Teste 07 - Nota do Exame Especial Negativa") {
  DiarioClasse diario;
  CHECK_THROWS_AS(diario.determinarAprovacao(50, -10, 1), ExcecaoNotaEspecialInvalida);

}

TEST_CASE("Teste 08 - Frequencia Negativa") {
  DiarioClasse diario;
  CHECK_THROWS_AS(diario.determinarAprovacao(70, 0, -1), ExcecaoFrequenciaInvalida);

}

TEST_CASE("Teste 09 - Reprovacao sem Nota para Exame Especial") {
  DiarioClasse diario;
  bool aprovado = diario.determinarAprovacao(30, 0, 1);
  CHECK_FALSE(aprovado);
}

TEST_CASE("Teste 10 - Reprovacao sem Frequencia para Exame Especial") {
  DiarioClasse diario;
  bool aprovado = diario.determinarAprovacao(50, 0, 0.5);
  CHECK_FALSE(aprovado);
}

TEST_CASE("Teste 11 - Reprovacao Exame Especial") {
  DiarioClasse diario;
  bool aprovado = diario.determinarAprovacao(50, 50, 1);
  CHECK_FALSE(aprovado);
}

TEST_CASE("Teste 12 - Reprovacao por Frequencia") {
  DiarioClasse diario;
  bool aprovado = diario.determinarAprovacao(80, 0, 0.5);
  CHECK_FALSE(aprovado);
}

TEST_CASE("Teste 13 - Aprovacao Simples") {
  DiarioClasse diario;
  bool aprovado = diario.determinarAprovacao(70, 0, 0.75);
  CHECK(aprovado);
}

TEST_CASE("Teste 14 - Sem nota e sem frequencia") {
  DiarioClasse diario;
  bool aprovado = diario.determinarAprovacao(50, 0, 0.6);
  CHECK_FALSE(aprovado);
}