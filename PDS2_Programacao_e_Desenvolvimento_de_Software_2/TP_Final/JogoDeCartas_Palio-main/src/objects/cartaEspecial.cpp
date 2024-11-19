#include "cartaEspecial.hpp"
#include "excecoes.hpp"

//Construtor de CartaEspecial
CartaEspecial::CartaEspecial(int id, int cor) : Carta(id, cor){
	// Exceção: cartas de id 13 e 14 devem ser criadas obrigatoriamente na cor BRANCA
	switch(id){
		case 10:
			this->funcao = "@"; //Bloqueio
			break;

		case 11:
			this->funcao = "S"; //Inverter
			break;

		case 12:
			this->funcao = "+2"; //Come 2 cartas do baralho
			break;

		case 13:
			this->funcao = "C"; //Troca de cor
			break;

		case 14:
			this->funcao = "+4"; //Troca de cor e come 4 cartas
			break;
	}
}

//Retorna a funcao da carta especial
//@return Função da carta especial
string CartaEspecial::getFuncao() const{
	return this->funcao;
}