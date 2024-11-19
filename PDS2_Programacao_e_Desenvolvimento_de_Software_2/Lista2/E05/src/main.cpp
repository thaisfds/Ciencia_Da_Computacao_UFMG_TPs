#include "Herpestidae.hpp"
#include "Ursidae.hpp"
#include "Cuidador.hpp"

int main(){

    //criacao das identificacoes dos animais
    Animal animal01("Bobby","Ursidae",13);
    animal01.print();

    Animal animal02("Jorge", "Ursidae",1);
    animal02.print();

    Animal animal03("Bonina","Herpestidae",7);
    animal03.print();

    Animal animal04("Felício", "Ursidae",3);
    animal04.print();

    Ursidae animal05("Tony", "Urso Pardo",9);
    animal05.print();

    Ursidae animal06("Wanda", "Urso Polar",10);
    animal06.print();

    Herpestidae animal07("Catita", "Suricato",2);
    animal07.print();
    
    Herpestidae animal08("Carolina","Suricato",2);

    //identificao dos cuidadores
    Cuidador cuidador01("Ana Maria Rodrigues Lopes");
    Cuidador cuidador02("Fernanda Silva Santos");

    //Forma de alimentacao e Descricao
    animal01.setTipoDescricao("Peixes","Bobby só quis comer 2 porções de peixes hoje");
    animal01.setPorcaoQuantidadePorcao(2,5);
    animal01.setQuantidadeConsumida(10);

    animal07.setTipoDescricao("Ração especial", "Catita comeu direitinho");
    animal07.setPorcaoQuantidadePorcao(1,1);
    animal07.setQuantidadeConsumida(animal07.calcularQuantidadeConsumida());

    animal08.setTipoDescricao("Ração", "Carolina estava com um apetite e tanto");
    animal08.setPorcaoQuantidadePorcao(3,1);
    animal08.setQuantidadeConsumida(animal08.calcularQuantidadeConsumida());

    animal05.setTipoDescricao("Peixes", "Tony comeu um pouco da comida do Bobby");
    animal05.setPorcaoQuantidadePorcao(10,5);
    animal05.setQuantidadeConsumida(animal05.calcularQuantidadeConsumida());

    //Relatorio das alimentacoes Animal, cuidador e descricao
    cout <<" \n \n--------------------------------\n\nRelatorio das alimentações " << endl;

    cout << "\nAnimal: " << animal01.getNome() << "\n Cuidador: " << cuidador01.getNome() << "\n Descricao: " << animal01.getDescricao() << endl;
    cout << "\nAnimal: " << animal07.getNome() << "\n Cuidador: " << cuidador02.getNome() << "\n Descricao: " << animal07.getDescricao() << endl;
    cout << "\nAnimal: " << animal08.getNome() << "\n Cuidador: " << cuidador02.getNome() << "\n Descricao: " << animal08.getDescricao() << endl;
    cout << "\nAnimal: " << animal05.getNome() << "\n Cuidador: " << cuidador01.getNome() << "\n Descricao: " << animal05.getDescricao() << endl;

    //Relatorio de kg de comida gastos racao e peixe
    cout <<"\n \n \n--------------------------------\n\nRelatorio de kg de comida gastos \n" << endl;
    cout << "Tipo de comida: " << "Ração" << endl;
    cout << "Kg consumidos: " << animal07.getQuantidadeConsumida() + animal08.getQuantidadeConsumida() << endl;
    cout << "\nTipo de comida: " << "Peixe" << endl;
    cout << "Kg consumidos: " << animal01.getQuantidadeConsumida() + animal05.getQuantidadeConsumida() <<endl;

    return 0;
}
