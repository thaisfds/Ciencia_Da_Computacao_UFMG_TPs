#ifndef PPM_H
#define PPM_H
//PPM imagem colorida

#include<iostream>
#include<string>
#include<fstream>
#include "RGB.h"

using namespace std;
class PPM{
    private:
        string nameFile, version;
        int height, width, max, tamVector;

    public:
        PPM();
        ~PPM();

        RGB* rgb;
        int* pgm;

        void PPMreader(string nameFile);
        void PPMtoPGM();
        void PGMwrite(string nameFile);
        
};

#endif