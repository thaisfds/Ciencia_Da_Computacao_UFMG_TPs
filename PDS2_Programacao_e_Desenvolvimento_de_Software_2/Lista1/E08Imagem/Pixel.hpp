#ifndef PIXEL_H
#define PIXEL_H

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Pixel{
    public:
        Pixel();
        Pixel(int red, int green, int blue);
        void set_rgb(int red, int green, int blue);
        void set_rgb(int gray);
        vector<int> get_rgb();
        void print();

    private:
        int red, green, blue, gray;  
};

#endif