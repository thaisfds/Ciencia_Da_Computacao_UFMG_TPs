#include "pessoa.hpp"
#include <iostream>
#include "csv.hpp"
#include <string>
#include <vector>
#include <set>

// Este comando é como um typedef em C, nós estamos "renomeando"
// "std::vector<std::string>" para "StringVector"
using StringVector = std::vector<std::string>;

/**
 * @brief Carrega uma entrada com formato CSV
 * no vetor de strings "texto"
 * @param texto Vetor de strings
 */
void carregaEntrada(StringVector &texto) {
    std::string linha;

    while (std::cin >> linha) {
        texto.push_back(linha);
    }
}

/**
 * @brief Transforma as entradas do "texto" em objetos Pessoa
 * e salva no vetor "pessoas"
 * @param file Conversor de arquivos (Note o polimorfismo aqui, podemos enviar
 * qualquer conversor desde que ele herde de File)
 * @param texto vetor com textos
 * @param pessoas vetor de pessoas
 */
void carregaVetorPessoas(File* file, StringVector& texto, std::vector<Pessoa>& pessoas) {
    for (int i = 1; i < texto.size(); i++) {
        Pessoa p;
        // texto[0] sempre será o header do CSV
        file->readLine(texto[0], texto[i], p);
        std::cout << "Linha " << i << " -- Pessoa: " << p << std::endl;
        pessoas.push_back(p);
    }
}

/**
 * @brief Verificar se existe alguma pessoa com CPF repetido.
 * Caso exista, armazena seu índice no set "index_cpfs_repetidos"
 * @param pessoas Vetor de pessoas
 * @param index_cpfs_repetidos Set para salvar o index das pessoas com
 * CPF repetido
 */
void salvarIndexCPFRepetidos(std::vector<Pessoa>& pessoas, std::set<int>& index_cpfs_repetidos) {
    for (int i = 0; i < pessoas.size(); i++) {
        for (int j = i + 1; j < pessoas.size(); j++){
            if(pessoas[i] == pessoas[j]) {
                index_cpfs_repetidos.insert(i);
                index_cpfs_repetidos.insert(j);
            }
        }
    }
}

/**
 * @brief Transformar o vetor pessoas em linhas CSV. Gera dois arquivos,
 * o primeiro arquivo CSV irá conter as pessoas com CPF repetido,
 * o segundo arquivo CSV irá conter as pessoas com CPF único
 * @param file Conversor de arquivos (Note o polimorfismo aqui, podemos enviar
 * qualquer conversor desde que ele herde de File)
 * @param pessoas vetor de pessoas
 * @param csv_cpf_repetidos vetor para salvar CSV com pessoas com CPF repetidos
 * @param csv_cpf_unicos vetor para salvar CSV com pessoas com CPF únicos
 */
void geraCSVPessoas(File* file, std::vector<Pessoa>& pessoas, StringVector& csv_cpf_repetidos, StringVector& csv_cpf_unicos) {
    std::set<int> index_cpfs_repetidos;
    salvarIndexCPFRepetidos(pessoas, index_cpfs_repetidos);

    for (int i = 0; i < pessoas.size(); i++) {
        std::string csv_texto = file->write(pessoas[i]);
        
        if(index_cpfs_repetidos.find(i) == index_cpfs_repetidos.end()) {
            csv_cpf_unicos.push_back(csv_texto);
        } else {
            csv_cpf_repetidos.push_back(csv_texto);
        }
    }
}

int main() {
    CSV file;
    StringVector texto;
    std::vector<Pessoa> pessoas;

    carregaEntrada(texto);
    carregaVetorPessoas(&file, texto, pessoas);

    std::string header_pessoa = file.getHeader(pessoas[0]);

    StringVector csv_cpf_repetidos = {header_pessoa};
    StringVector csv_cpf_unicos = {header_pessoa};
    geraCSVPessoas(&file, pessoas, csv_cpf_repetidos, csv_cpf_unicos);
    

    std::cout << "-------------" << std::endl;

    std::cout << "CSV de CPFs repetidos:" << std::endl;
    for (auto line : csv_cpf_repetidos) {
        std::cout << line << std::endl;
    }

    std::cout << "-------------" << std::endl;

    std::cout << "CSV de CPFs únicos:" << std::endl;
    for (auto line : csv_cpf_unicos) {
        std::cout << line << std::endl;
    }

    return 0;
}