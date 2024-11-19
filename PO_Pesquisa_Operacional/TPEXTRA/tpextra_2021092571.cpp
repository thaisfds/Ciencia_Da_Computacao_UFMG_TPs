#include <iostream> //biblioteca padrão
#include <fstream> //biblioteca para leitura e escrita de arquivos

#include <iomanip> //facilitar os prints
#include <sstream> //facilitar os prints std::setw(3) 
#include <string> //facilitar os prints

#include <vector> //vetor utilizado para o tableau

/*
Grupo:
- Thaís Ferreira da Silva 2021092571
- Lucas Santos Teles 2017014995
- Ana Luisa Araujo Bastos 2021031459
*/

class Simplex {
    protected:
        int n;
        int m;
        int nTableau;
        int mTableau;

    public:
        //construtor
        Simplex(int n, int m, int nTableau, int mTableau) {
            this->n = n;
            this->m = m;
            this->mTableau = mTableau;
            this->nTableau = nTableau;
        }

        virtual ~Simplex() {}

        std::string limitfloat(float value) {
            std::stringstream ss;
            ss.precision(2);
            ss << value;
            return ss.str();
        }
        
        //Printar o tableau
        void printarTableau(std::vector<std::vector<float>>& tableau) {

            std::cout << std::endl;

            for (int j = 0; j < mTableau+4; j++) {
                std::cout << std::setw(6) << "------";
            }

            std::cout << std::endl;
            
            int linha = 0;

            for (int j = 0; j < mTableau+4; j++) {
                if (j == mTableau+2 || j == nTableau-1 || j == nTableau + m || j == mTableau - n + 1) 
                    std::cout << std::setw(6) << "|";
                else{
                    std::cout << std::setw(6) << linha;
                    linha++;
                }
            }

            std::cout << std::endl;

            for (int j = 0; j < mTableau+4; j++) {
                std::cout << std::setw(6) << "------";
            }

            std::cout << std::endl;
            
            for (int i = 0; i < nTableau; i++) {

                //Printar nTableau vezes "_"
                if(i == 1){
                    for (int j = 0; j < mTableau+4; j++) {
                        std::cout << std::setw(6) << "-";
                    }
                    std::cout << std::endl;
                }

                for (int j = 0; j < mTableau; j++) {
                    
                    //Divide a identidade inicial, identidade final, folgas e b
                    if (j == mTableau-1 || j == nTableau-1 ) 
                        std::cout << std::setw(6) << "|";
                    if (j == nTableau + m -1 || j == mTableau - n - 1) 
                        std::cout << std::setw(6) << "'";

                    std::cout << std::setw(6) << limitfloat(tableau[i][j]);
                }
                std::cout << std::endl;
            }
            
            std::cout << "\n" << std::endl;
            for (int j = 0; j < mTableau+4; j++) {
                std::cout << std::setw(6) << "======";
            }
            std::cout << "\n" << std::endl;
            
        }

        //Se tableau m-1 for negativo multiplicar a linha por -1
        int tratarEntrada(std::vector<std::vector<float>>& tableau) {
            int PLTratada = 0;
            for (int i = 0; i < nTableau; i++) {
                if (tableau[i][mTableau-1] < 0) {
                    PLTratada = 1;

                    //Inverte tudo menos a identidade
                    for (int j = 0; j < mTableau; j++) {
                        if(tableau[i][j] != 0)
                            tableau[i][j] *= -1;
                    }
                }
            }
            return PLTratada;
        }

        //Eliminação de Gauss
        void eliminacaoGaussia(std::vector<std::vector<float>>& tableau, int linha, int coluna) {
            float pivo = tableau[linha][coluna];

            //Divide a linha do pivo pelo pivo
            for (int i = 0; i < mTableau; i++) {
                tableau[linha][i] /= pivo;
            }

            //std::cout << "Pivo: " << pivo << std::endl; //printa o pivo

            //Eliminação de Gauss
            for (int i = 0; i < nTableau; i++) {
                if (i != linha) {
                    float mult = tableau[i][coluna];
                    for (int j = 0; j < mTableau; j++) {
                        tableau[i][j] -= mult * tableau[linha][j];
                        if (tableau[i][j] < 0.00001 && tableau[i][j] > -0.00001)
                            tableau[i][j] = 0;
                    }
                }
            }  
        }

        //Acha a linha do pivo para a eliminação de Gauss
        int acharLinhaPivo(std::vector<std::vector<float>>& tableau, int coluna) {
            int linha = -1;
            float div = -1;

            //Divide todos os valores de b pelo valor da coluna, e retorna o menor
            for (int i = 1; i < nTableau; i++) {
                if (tableau[i][coluna] > 0){
                    float aux = tableau[i][mTableau-1] / tableau[i][coluna];
                    if(div == -1 || (aux < div && aux >= 0)){
                        div = aux;
                        linha = i;
                    }
                }
            }
            return linha;
        }

        //verifica se existe coluna negativa
        int verificarIlimitado(std::vector<std::vector<float>>& tableau, int coluna) {
            //se para cada coluna de A, verifica se todos os valores são < 0
            //se sim retorna 1

            int ilimitado = 0;

            for (int i = 1; i < nTableau; i++) {
                if (tableau[i][coluna] <= 0)
                    ilimitado++;
            }

            if (ilimitado == n)
                ilimitado = 1;

            return ilimitado;
            
        }

        //arrumar o tableau para a pl auxiliar
        void auxiliar(std::vector<std::vector<float>>& tableau){
            //somar todas as linhas do tableau diferentes de 0
            for (int i = 1; i < nTableau; i++) {
                for (int j = 0; j < mTableau; j++) {
                    tableau[0][j] -= tableau[i][j];
                }
            }
        }

        int simplex(std::vector<std::vector<float>>& tableau) {
            //lupar a primeira linha a partir de n em busca de um valor negativo

            float temNegativo; //marca se necessitamos de pivoteamento
            int runs = 0; //marca o numero de vezes que o simplex rodou

            do{
                temNegativo = 0;
                int colunaPivo = 0; //marca o numero a ser pivoteado

                //Procurar por negativos na primeira linha
                for (int i = nTableau-1; i < mTableau-1; i++) {
                    if (tableau[0][i] < 0) {
                        temNegativo++;
                        if(colunaPivo == 0)
                            colunaPivo = i; //pega a posição da coluna a ser pivoteada
                    }
                }

                //Achar a linha do pivoteamento e chamar a eliminação
                int linhaPivo;
                if (temNegativo > 0){
                    linhaPivo = acharLinhaPivo(tableau, colunaPivo);

                    if (linhaPivo != -1)
                        eliminacaoGaussia(tableau,linhaPivo, colunaPivo);
                    else{
                        int v = verificarIlimitado(tableau, colunaPivo);
                        if (v == 1)
                            return 1;
                    }
                }
                
                // if (temNegativo > 0){
                //     std::cout << "Tableau " << runs << " -> Eliminar " << linhaPivo << "x" << colunaPivo << ":" << std::endl; //printa o resultado da iteração
                //     printarTableau(tableau);
                // }

                runs++;

            }while (temNegativo > 0);
            return 0;
        }

        //Certificado (-1 inviavel) (0 otimo) (1 ilimitado)
        //ilimitado = toda linha negativa
        //otimo = valor final positivo
        //inviavel = valor final negativo na pl auxiliar
        
        void imprimirCertificado(std::vector<std::vector<float>>& tableau, int tipo) {
            
            //Inviabilidade
            if (tipo == -1){
                //Pegar a 1° linha da identidade
                std::cout << "inviavel" << std::endl;
                for(int i = 0; i < n; i++)
                    std::cout << tableau[0][i] << " ";

                std::cout << std::endl;

            }

            //Otimalidade
            else if (tipo == 0){
                std::cout << "otima" << std::endl;
                std::cout << tableau[0][mTableau-1] << std::endl;
                
                //Imprimir os valores otimos
                //Para cada coluna verifica se tem varios 0s e um 1
                for (int j = n; j < n+m; j++) { 

                    int zeros = 0;
                    int uns = 0;
                    int linha;

                    for (int i = 1; i < nTableau; i++) {
                        if(tableau[i][j] == 0)
                            zeros++;
                        else if(tableau[i][j] == 1){
                            uns++;
                            linha = i;
                        }
                    }

                    if(zeros == n-1 && uns == 1)
                        std::cout << tableau[linha][mTableau-1] << " ";
                    else
                        std::cout << 0 << " ";

                }

                std::cout << std::endl;

                //Pegar a 1° linha da identidade
                for(int i = 0; i < n; i++)
                    std::cout << tableau[0][i] << " ";

                std::cout << std::endl;
            
            }
            
            //Ilimitado
            else if (tipo == 1){
                
                std::cout << "ilimitada" << std::endl;

                //criar vetor d de tamanho n-1
                std::vector<float> d;
                for (int i = 0; i < m; i++) {
                    d.push_back(0);
                }

                int colunaNegativa = 0;

                for (int j = n; j < (2*n)+m; j++) { 
                    
                    int negativos = 0;

                    if(tableau[0][j] < 0){
                        for (int i = 1; i < nTableau; i++) {
                            if (tableau[i][j] <= 0)
                                negativos++;
                        }
                        if(negativos == n){
                            colunaNegativa = j;
                            if(j < n+m)
                                d[j-n] = 1;
                        }
                    }
                }

                //Imprimir os valores otimos
                //Para cada coluna verifica se tem varios 0s e um 1
                for (int j = n; j < n+m; j++) { 

                    int zeros = 0;
                    int uns = 0;
                    int linha;

                    for (int i = 1; i < nTableau; i++) {
                        if(tableau[i][j] == 0)
                            zeros++;
                        else if(tableau[i][j] == 1){
                            uns++;
                            linha = i;
                        }
                    }

                    if(zeros == n-1 && uns == 1){
                        d[j-n] = tableau[linha][colunaNegativa];
                        std::cout << tableau[linha][mTableau-1] << " ";
                    }
                    else
                        std::cout << 0 << " ";

                }

                std::cout << std::endl;

                //Imprimir o vetor d
                for (int i = 0; i < m; i++) {
                    if (d[i] < 0)
                        d[i] *= -1;
                    std::cout << d[i] << " ";
                }

                std::cout << std::endl;
                
            }
        }

};


int main(int argc, char* argv[]) {

    // passar argv[1] para std::string nomeArquivo
    std::string nomeArquivo = argv[1];

    //se o nome do arquivo terminar em .txt, remover o .txt
    if(nomeArquivo.substr(nomeArquivo.size() - 4) == ".txt")
        nomeArquivo = nomeArquivo.substr(0, nomeArquivo.size() - 4);

    // Abre o arquivo
    std::ifstream input(nomeArquivo);
    //Leitura das entradas

    int n, m, nTableau, mTableau;
    float c;
    int PLAuxiliar;
    int tipo = 0;
    input >> n >> m; //n e m da matria A

    nTableau = n + 1; //linhas
    mTableau = m + (3*n) + 1; //colunas -> identidade + A + identidade + folga + b
    

    std::vector<std::vector<float>> tableau;

    //criar uma matriz nTableau x mTableau com 0
    for (int i = 0; i < nTableau; i++) {
        std::vector<float> row;
        for (int j = 0; j < mTableau; j++) {
            row.push_back(0);
        }
        tableau.push_back(row);
    }

    //Preencher a primeira linha
    for (int i = 0; i < mTableau; i++) {
        float value;
        if(i > n-1 && i < n+m){
            input >> value;
            if(value != 0)
                value *= -1;
        }else
            value = 0;
        tableau[0][i] = value;
    }

    //Preencher as outras n-1 linhas
    for (int i = 1; i < nTableau; i++) {
        for (int j = 0; j < mTableau; j++) {
            float value = 0;
            if((i-1 == j) || (i-1+m+n == j)) //montar a identidade do inicio e do final
                value = 1;           
            else if((j >= n && j < n+m) || j == mTableau-1) //montar A e b
                input >> value;

            tableau[i][j] = value;
        }
    }

    Simplex simplex(n, m, nTableau, mTableau); //Iniciaro simplex

    //std::cout << "Tableau inicial:" << std::endl;
    //simplex.printarTableau(tableau);  //tableau inicial montado pelas entradas

    PLAuxiliar = simplex.tratarEntrada(tableau);
    
    //std::cout << "Tableau tratado:" << std::endl;
    //simplex.printarTableau(tableau); //tableau tratado sem negativos no b

    //-----------PLAUXILIAR-------------
    
    std::vector<float> b;

    if(PLAuxiliar == 1){
        // std::cout << "------------" << std::endl;
        // std::cout << "PL Auxiliar:" << std::endl;

        //copiar a primeira linha de tableau para b
        for (int i = 0; i < mTableau; i++) {
            b.push_back(tableau[0][i]);
        }

        int count = 1;
        for (int i = 0; i < mTableau; i++) {
            //alterar a primeira linha de tableau para 0
            if(i > (2*n)+m-1 && i < mTableau-1)
                tableau[0][i] = 1;
            else
                tableau[0][i] = 0;

            //Add identidade no final
            if(i > (2*n) + m - 1 && i < mTableau-1){
                tableau[count][i] = 1;
                count++;
            }

        }

        //simplex.printarTableau(tableau); //tableau tratado sem negativos no b

        simplex.auxiliar(tableau); //arrumar pra auxiliar
        
        //simplex.printarTableau(tableau); //tableau tratado sem negativos no b
        
        simplex.simplex(tableau); //chamar o simplex

        //SE A PL AUXILIAR É VIAVEL
        if(tableau[0][mTableau-1] == 0){
            tipo = 0;
            //zera identidade do final
            for (int i = 0; i < nTableau; i++) {
                for (int j = (2*n)+m; j < mTableau-1; j++) 
                        tableau[i][j] = 0;
            }
            
            //std::cout << "Tableau sem identidade:" << std::endl;
            //simplex.printarTableau(tableau); //tableau tratado sem negativos no b

            //voltar a primeira linha de tableau para b
            for (int i = 0; i < mTableau; i++) {
                tableau[0][i] = b[i];
            }

            //std::cout << "Tableau com b original:" << std::endl;
            //simplex.printarTableau(tableau); //tableau tratado sem negativos no b
        }else{
            tipo = -1;
        }
    }



    //-----------SIMPLEX-------------
    
    if(tipo == 0){
        tipo = simplex.simplex(tableau); //chamar o simplex
    }

    //pegar os certificados
    simplex.imprimirCertificado(tableau, tipo);
}