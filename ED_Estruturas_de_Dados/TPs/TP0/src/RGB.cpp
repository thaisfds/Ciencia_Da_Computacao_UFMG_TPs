#include "RGB.h"

RGB::RGB(int red, int green, int blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->gray = (49.0f/255)*((0.3*red)+(0.59*green)+(0.11*blue));
}

RGB::~RGB(){

}

int RGB::getGray(){
    return(this->gray);
}