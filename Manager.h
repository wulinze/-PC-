//
// Created by 82490 on 2019/5/23.
//

#ifndef PCMODEL_MANAGER_H
#define PCMODEL_MANAGER_H


#include "Process.h"
#include <iostream>

using  namespace std;


struct semaphere{
    semaphere(vector<Process *> &queue,int num) : queue(queue) {
        this->num = num;
    }

    int num;
    vector<Process*>& queue;
    void assign(int num, vector<Process *> &q)  {
        this->num = num;
        this->queue = q;
    }

};
class Manager {
private:
    Process* producer;
    Process* consumer;
    Process* running;
    vector<int> buffer;
    vector<Process*> mutex_queue,full_queue,empty_queue;
    vector<Process*> ready_queue;
    semaphere sig_full=semaphere(full_queue,0),sig_empty=semaphere(empty_queue,0), sig_mutex = semaphere(mutex_queue, 0);
public:

    Manager();

    void Produce();
    void Consume();
    void Exit();

    bool P(semaphere& signal,Process* p);
    void V(semaphere& signal,Process* p);

    void Show();
    void Action(int opt);
};


#endif //PCMODEL_MANAGER_H
