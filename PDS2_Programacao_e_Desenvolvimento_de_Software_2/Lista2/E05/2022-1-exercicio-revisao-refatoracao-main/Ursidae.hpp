#ifndef ursidae_HPP
#define ursidae_HPP

#include <iostream>
#include <iomanip>

using namespace std;

int peixesPorPORCAO = 5;

class Ursidae {
    public:

        int IDADE;
        string nome;
        string especie;
        double kgPeixePorDIA;

        void print() {
            cout << "\n[Animal]" << endl
            << "  Nome: " << nome << endl
            << "  Idade: " << IDADE << endl
            << "  Família: Ursidae" << endl
              << "  Especie: " << especie << endl;
        }

        double calcula_PEIXES_CONSUMIDOS(int porcaoPeixes){
            double x;
            return peixesPorPORCAO*porcaoPeixes;
        }

};

#endif

