#ifndef AVALIACAO_H
#define AVALIACAO_H

#include <iostream>

#include "LimitedQueue.hpp"

using namespace std;

void avaliacao_basica() {
    
    InvalidSizeException ise;
    QueueFullException qfe;
    QueueEmptyException qee;
    ItemNotFoundException infe;

    LimitedQueue* lq;
    lq = new LimitedQueue(5);

    cout << lq->get_max_size() << endl;

    lq->push_back(11);
    lq->push_back(22);
    lq->push_back(33);
    lq->push_back(44);
    lq->push_back(55);

    lq->print();

    lq->pop_front();
    lq->pop_front();

    cout << lq->front() << "\t" << lq->back() << endl;    

    int i = lq->find(44);
    std::cout << i << std::endl;

    lq->find(11);
}

#endif