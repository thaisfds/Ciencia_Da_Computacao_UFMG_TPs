#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <iomanip>

using namespace std;

class Animal {
    public:
        string IDADE;
        string family;
        string nome;

        void print() {
            cout << "\n[Animal]" << endl
            << "  Nome: " << nome << endl

              << "  Idade: " << IDADE << endl
            << "  Familia: " << family << endl;
        }

        void print_oi(){
            cout << "Tchau" << endl;
        }
};

#endif
