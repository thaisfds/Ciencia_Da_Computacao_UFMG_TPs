#include "carta.hpp"

//Construtor da Carta, inicializa o id da carta com o valor padrão de -1
Carta::Carta() : cor(Cor::BRANCO){
	this->id = -1;
}

//Verifica se a carta é ou não compatível com determinada regra
//@return True se a carta é compatível coma regra
bool Carta::ehCompativel(Carta* c, int regraEmpilharCompraCarta){
	// RegraEmpilharCartaCompra:
	// 0: Não é possivel jogar uma carta de compra em resposta à outra
	// 1: Jogar uma carta de compra em resposta à outra, +4 não pode ser jogado em resposta à um +2
	// 2: Jogar uma carta de compra em resposta à outra, +4 pode ser jogado em resposta à um +2
	switch (regraEmpilharCompraCarta){
	case 0:
		if(*this == *c || (this->cor.getCodigo() == Cor::BRANCO)){
			return true;
		}
		break;
	case 1:
		if(this->getID() == c->getID()){
			return true;
		}
		break;
	case 2:
		if(this->getID() == c->getID() || this->getID() == 14){
			return true;
		}
		break;
	}
	return false;
}

//Modifica a Descricao em caso de alteracao
void Carta::setDescricaoCarta(string descricao){
	this->descricaoCarta = descricao;
}

//Obtém Descricao da carta utilizada no menu
//@return Descrição da carta usada no menu
string Carta::getDescricaoCarta(){
	return this->descricaoCarta;
}

//Obtém ID da carta
//@return ID da carta
int Carta::getID() const{
	return this->id;
}

//Obtém a cor da carta
//@return Cor da carta
int Carta::getCor() const{
	return this->cor.getCodigo();
}

//Modifica a cor da carta (pelo ID)
void Carta::setCor(int cor){
	this->cor = Cor::Modificador(cor);
}

//Sobrecarga de operador para testar se o jogador pode jogar a carta
bool Carta::operator==(const Carta& c){
	return ((this->id == c.id) || (this->cor == c.cor));
}