#ifndef MENUINICIAL_HPP
#define MENUINICIAL_HPP
#include "menuAjuda.hpp"
#include "jogador.hpp"
#include "mesa.hpp"
#include <iostream>
#include <vector>
#include "regra.hpp"
#include <limits>

class MenuInicial{
	private:
		MenuAjuda ajuda;
		vector<Regra*> regras;

	public:
		MenuInicial();
		void menu();
		void pedirAjuda ();
		void iniciar ();
		void escolherRegras();
		void ativarRegra(string nomeRegra, string descricao);
		void regrasEmUso();
};

#endif 
