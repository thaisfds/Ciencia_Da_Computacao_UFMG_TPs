#ifndef CUIDADOR_HPP
#define CUIDADOR_HPP

#include <string>
#include <iostream>

using std::string;

class Cuidador{

	private:
		string nome;

	public:
		//construtores
		Cuidador(string nome);

		//gets
		string getNome();

};

#endif
