#include "Pixel.hpp"

Pixel::Pixel():Pixel(0,0,0){}

Pixel::Pixel(int red, int green, int blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void Pixel::set_rgb(int red, int green, int blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void Pixel::set_rgb(int gray){
    this->red = gray;
    this->green = gray;
    this->blue = gray;
}

vector<int> Pixel::get_rgb(){
    vector<int> pixel = {this->red, this->green, this->blue};
    return pixel;
}

void Pixel::print(){
    cout << std::setfill('0') << std::setw(3) << this->red;
    cout << std::setfill('0') << std::setw(3) << this->green;
    cout << std::setfill('0') << std::setw(3) << this->blue;
}