#ifndef AVALIACAO_H
#define AVALIACAO_H

#include <iostream>
#include <vector>

#include "Imagem.hpp"

using namespace std;

void avaliacao_basica() {
    
    Pixel pixel;

    pixel.print();
    cout << endl;

    pixel.set_rgb(85, 128, 255);
    pixel.print();
    cout << endl;

    std::vector<int> rgb = pixel.get_rgb();
    cout << rgb[0] << rgb[1] << rgb[2] << endl;

    cout << "----------" << endl;

    Imagem imagem;
    imagem.initialize_image(2, 2);
    imagem.show();

    cout << "----------" << endl;

    imagem.fill(0, 0, "255255255");
    imagem.fill(0, 1, "128128128");
    imagem.fill(1, 0, "128128128");
    imagem.fill(1, 1, "255255255");
    imagem.show();

    cout << "----------" << endl;

    imagem.to_grayscale();
    imagem.show();

    cout << "----------" << endl;

    imagem.grayscale_thresholding(128);
    imagem.show();

}

#endif