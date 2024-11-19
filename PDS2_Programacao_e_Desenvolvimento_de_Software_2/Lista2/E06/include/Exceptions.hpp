#ifndef EXCEPTION_H
#define EXCEPTION_H

#include<iostream>
#include<stdio.h>
#include<string>
#include<iterator>
#include<list>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::list;

class Exceptions{
    public:
        string name;
};

class InvalidSizeException: public Exceptions{
    public:
        InvalidSizeException() {name = "Excecao: InvalidSizeException";}
};

class QueueFullException: public Exceptions{
    public:
        QueueFullException() {name = "Excecao: QueueFullException";}

};

class QueueEmptyException: public Exceptions{
    public:
        QueueEmptyException() {name = "Excecao: QueueEmptyException";}

};

class ItemNotFoundException: public Exceptions{
    public:
        ItemNotFoundException() {name = "Excecao: ItemNotFoundException";}

};

#endif