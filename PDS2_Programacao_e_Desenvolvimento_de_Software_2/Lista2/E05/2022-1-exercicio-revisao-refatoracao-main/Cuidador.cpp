#include <iostream>
#include <string>
#include "Cuidador.hpp"

void Cuidador::print(){

	std::cout << "[Cuidador]" << endl
         << "  Nome: " << NOME << endl
		 << "  CPF: " << cpf << endl
		<< "  Telefone: " << Telefone << endl
		 << "  Nascimento: " << BIRTH << endl;

}

