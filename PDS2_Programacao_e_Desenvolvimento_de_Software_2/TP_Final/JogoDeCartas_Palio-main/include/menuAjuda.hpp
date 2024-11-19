#ifndef MENUAJUDA_HPP
#define MENUAJUDA_HPP
#include <iostream>
#include <vector>
#include <limits>
#include "excecoes.hpp"


class MenuAjuda {
	
	public:
		MenuAjuda();
		void menuDeAjuda();
		void mostrarRegras(int modoDeJogo);
		void mostrarDescricaoCartas(int modoDeJogo);
		int opcaoEhValida(int nOpcoes);
		
};

#endif