//
// Created by 82490 on 2019/5/23.
//

#include "Manager.h"

#define FULLSIZE 0
#define EMPTYSIZE 8
#define MUTEXSIZE 1

void Manager::Produce() {
    if(P(sig_empty,this->producer)){
        if(P(sig_mutex,this->producer)){
            ready_queue.emplace_back(this->producer);
            if(this->running== nullptr){
                this->running = ready_queue[0];
                ready_queue.erase(ready_queue.begin());
            }
        }
    }
}
void Manager::Consume() {
    if(P(sig_full,this->consumer)){
        if(P(sig_mutex,this->consumer)){
            ready_queue.emplace_back(this->consumer);
            if(this->running== nullptr){
                this->running = ready_queue[0];
                ready_queue.erase(ready_queue.begin());
            }
        }
    }
}
void Manager::Exit() {
    if(this->running!= nullptr){
        this->running->run(buffer);
        if(this->running->getPCB().kind==Kind::Producer){
            V(sig_mutex,this->running);
            V(sig_full,this->running);
        }else{
            V(sig_mutex,this->running);
            V(sig_empty,this->running);
        }
        if(!ready_queue.empty()){
            this->running = ready_queue[0];
            ready_queue.erase(ready_queue.begin());
        } else{
            this->running = nullptr;
        }
    }
}


bool Manager::P(semaphere &signal,Process* p) {
    if(--signal.num >= 0){
        return true;
    } else{
        signal.queue.emplace_back(p);
        return false;
    }
}
void Manager::V(semaphere &signal,Process* p) {
    if(++signal.num<=0){
        if(signal.queue == sig_mutex.queue){
            ready_queue.emplace_back(signal.queue[0]);
            signal.queue.erase(signal.queue.begin());
        } else{
            Process* temp = signal.queue[0];
            signal.queue.erase(signal.queue.begin());
            if(temp->getPCB().kind==Kind::Producer){
                P(sig_mutex,this->producer);
            } else{
                P(sig_mutex,this->consumer);
            }
        }
    }
}



Manager::Manager() {
    this->producer = new Process(0);
    this->consumer = new Process(1);
    this->running = nullptr;
    this->sig_full.assign(FULLSIZE,full_queue);
    this->sig_empty.assign(EMPTYSIZE,empty_queue);
    this->sig_mutex.assign(MUTEXSIZE,mutex_queue);
}

void Manager::Action(int opt) {
    switch(opt){
        case 0:
            Produce();
            break;
        case 1:
            Consume();
            break;
        case 2:
            Exit();
            break;
        default:
            cout << "请输入正确操作码" << endl;
            break;
    }
}
void Manager::Show() {
    system("cls");
    cout << "mutex queue:";
    for(Process *p : mutex_queue){
        cout << *p;
    }
    cout << endl << "empty queue:";
    for(Process *p : empty_queue){
        cout << *p;
    }
    cout << endl << "full queue:";
    for(Process *p : full_queue){
        cout << *p;
    }
    cout << endl << "ready queue:";
    for(Process *p : ready_queue){
        cout << *p;
    }
    cout << endl << "running:";
    if(this->running!= nullptr)cout << *this->running;
    cout << endl << "buffer:";
    for(int i=0;i<buffer.size();i++){
        cout << '(' << i << ":" << buffer[i] << ")";
    }
    cout << endl;
    cout << "Produce:0\t" << "Consume:1\t" << "Exit:2" << endl;
}

