#include "Imagem.hpp"

void Imagem::initialize_image(int width, int height){
    this->width = width;
    this->height = height;
    for(int i = 0; i < (width * height); i++){
        this->imagem.push_back(Pixel());
    }
}

void Imagem::fill(int row, int col, string pixel){
    int red = stoi(pixel.substr(0,3));
    int green = stoi(pixel.substr(3,3));
    int blue = stoi(pixel.substr(6,3));

    this->imagem[(this->width * row) + col].set_rgb(red, green, blue); //
}

void Imagem::to_grayscale(){
    vector<int> pixel;
    int gray;
    for(int i = 0; i < (this->width * this->height); i++){
        pixel = this->imagem[i].get_rgb();
        gray = (pixel[0] + pixel[1] + pixel[2]) / 3;
        this->imagem[i].set_rgb(gray, gray, gray);
    }
   
}

void Imagem::grayscale_thresholding(int lim){
    vector<int> pixel;
    for(int i = 0; i < (this->width * this->height); i++){
        pixel = this->imagem[i].get_rgb();
        if(pixel[0] > lim) this->imagem[i].set_rgb(255);
        else this->imagem[i].set_rgb(0);
    }    

}

void Imagem::show(){
    for(int i = 0; i<this->height;i++){
        for(int j = 0; j<this->width;j++){
            this->imagem[(this->width * i) + j].print();
            cout << " ";
        }
        cout << endl;
    }
}