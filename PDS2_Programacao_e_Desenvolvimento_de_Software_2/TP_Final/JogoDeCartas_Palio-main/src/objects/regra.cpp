#include "regra.hpp"

//Inicializa a regra
//@param nome Nome da regra 
//@param descrição Descrição 
Regra::Regra(string nome, string descricao){
	this->nome = nome;
	this->descricao = descricao;
}

//Retorna o nome da regra
//@return Nome da regra
string Regra::getNome(){
	return this->nome;
}

//Retorna a descrição da regra
//@return Descrição da regra
string Regra::getDescricao(){
	return this->descricao;
}