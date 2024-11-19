#include "LimitedQueue.hpp"

int LimitedQueue::get_max_size(){
    return this->max_size;
}

LimitedQueue::LimitedQueue(int max_size){
    if(max_size <= 0) throw InvalidSizeException();
    this->max_size = max_size;
}

void LimitedQueue::push_back(int k){
    if(fila.size() == max_size) throw QueueFullException();
    fila.push_back(k);
}

void LimitedQueue::pop_front(){
    if(fila.empty() == true) throw QueueEmptyException();
    list<int>::iterator bg = fila.begin();
    fila.erase(bg);
}

int LimitedQueue::front(){
    if(fila.empty() == true) throw QueueEmptyException();
    return fila.front();
}

int LimitedQueue::back(){
    if(fila.empty() == true) throw QueueEmptyException();
    return fila.back();
}

int LimitedQueue::find(int k){
    bool found = false;
    if(fila.empty() == true) throw QueueEmptyException();
    int i = 0;

    for(int fl: fila){
        if(fl == k){
            found = true;
            return i;
        }
        i++;
    }

    if(found == false) throw ItemNotFoundException();

    return -1;
}

void LimitedQueue::print(){
    if(fila.empty() == true) throw QueueEmptyException();
    for(int fl: fila)
        cout << fl << endl;
   
}
