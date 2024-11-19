#ifndef CSV_H
#define CSV_H

#include "file.hpp"
#include <bits/stdc++.h>
using std::stringstream;

class CSV : public File{
   private: 
    void split(string& str, vector<string>& out);

    public: 
        string getHeader(IReadable& object);
        virtual void readLine(string& head, string& line, IReadable& object) override;
        virtual string write(IReadable& object) override;
};

#endif