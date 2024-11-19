#define DOCTEST_CONFIG_IMPEMENT_WITH_MAIN

#include "regra.hpp"
#include "doctest.h"

TEST_CASE("01 - "){
    Regra r = Regra("PularTurno", "Ao selecionar esta regra o jogador pode escolher pular ou nao o seu turno");
    CHECK(r.getNome() == "PularTurno");
    CHECK(r.getDescricao() == "Ao selecionar esta regra o jogador pode escolher pular ou nao o seu turno");
}