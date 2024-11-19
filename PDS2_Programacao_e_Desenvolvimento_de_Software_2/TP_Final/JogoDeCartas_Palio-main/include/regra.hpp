#ifndef REGRA_HPP
#define REGRA_HPP

#include <iostream>
#include "excecoes.hpp"

using namespace std;

class Regra{
	private:
		string nome;
		string descricao;
	
	public:
		Regra(string nome, string descricao);
		string getNome();
		string getDescricao();
};

#endif