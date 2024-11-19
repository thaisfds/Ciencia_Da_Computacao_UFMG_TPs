#ifndef RGB_H
#define RGB_H

#include<iostream>
#include<string>
#include<fstream>
#include "memlog.h"
#include "msgassert.h"

using namespace std;
class RGB{
    private:
        int red, green, blue, gray;

    public:
        RGB(): red(0), green(0), blue(0){};
        RGB(int red, int green, int blue);
        ~RGB();
        
        int getGray();
        
};

#endif