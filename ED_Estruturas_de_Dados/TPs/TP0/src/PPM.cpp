#include "PPM.h"

PPM::PPM(){
    this->version = "";
    this->height = 0;
    this->width = 0;
    this->max = 0;
    this->tamVector = 0;

}

PPM::~PPM(){
    delete rgb;
    delete pgm;
}

void PPM::PPMreader(string nameFile){

    ifstream input(nameFile, ios::binary); //abre o arquivo
    int r,g,b;

    //Valores iniciais da versao, altura, largura e valor maximo do rgb
    if(input.is_open()){
        input >> this->version;
        if(version != "P3") erroAssert(true,"Arquivo não é P3");

        input >> this->height;
        erroAssert(height>0,"Tamanho invalido");

        input >> this->width;
        erroAssert(width>0,"Tamanho invalido");

        input >> this->max;
        erroAssert((max == 255),"Tamanho invalido");

        this->tamVector = height*width;

        rgb = new RGB[tamVector];

        for(int i=0; i<tamVector; i++){
            input >> r;
            input >> g;
            input >> b;

            if(r <= max || g <= max || b <= max){
                erroAssert(false,"Valores do RGB invalidos");
            }
            
            rgb[i] = RGB(r,g,b);
            ESCREVEMEMLOG((long int)(&this->rgb[i]), sizeof(RGB),0);
        }
        input.close();
    }else{
        erroAssert(false,"Arquivo nao pode ser aberto");
    }
}

void PPM::PPMtoPGM(){
    pgm = new int[tamVector];
    int gray;

    for(int i=0; i < tamVector; i++){
        gray = rgb[i].getGray();
        LEMEMLOG((long int)(&this->rgb[i]), sizeof(RGB),0);

        pgm[i] = gray;
        ESCREVEMEMLOG((long int)(&this->pgm[i]), sizeof(int),1);
    }
}

void PPM::PGMwrite(string nameFile){
    this->nameFile = "/tmp/" + nameFile;
    ofstream output(this->nameFile, ios::binary);
    if(output.is_open()){
        output << "P2\n" << height << " " << width << "\n49" << endl;
        
        for(int i=0; i < tamVector; i++){ 
            output << pgm[i];
            LEMEMLOG((long int)(&this->pgm[i]), sizeof(int),1);
            if(i>1 && i%height == 0){
                output << "\n";
            }else{
                output << " ";
            }
        }

        output.close();
    }else{
        erroAssert(false,"Arquivo nao pode ser aberto");
    }
}