#include <unistd.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib> 
#include "MetodosOrdenacao.h"

//Funcoes do timer
#include <stdio.h>
#include <sys/resource.h>

bool extensionChecker(std::string& name, std::string extension); //Verifica a extensao de um arquivo
double Timer(); // Pega o horário atual do relogio
void Argumentos(int argc, char* argv[]); //Recebe e seta os argumentos da compilacao
void AnaliseGeral(std::ifstream& input,std::ofstream& output); //v0 Realiza uma analise geral dos metodos

//Metodos para imprimir as saidas de forma esteticamente agradavel
void ImprimeCabecalho(int tamanho,std::ofstream& input);
void ImprimeSaida(int tamanho, std::ofstream& output);
void ImprimeMedia(int n, std::ofstream& output);
void ImprimeGeral(std::ofstream& input);
void ImprimeMediaGeral(int *tamanhos, int n, std::ofstream& output);
void ZeraMedias();