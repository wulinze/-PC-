//
// Created by 82490 on 2019/5/23.
//

#ifndef PCMODEL_PROCESS_H
#define PCMODEL_PROCESS_H


#include <iostream>
#include <vector>

using  namespace std;

class Process;
enum  class Kind{
    Producer=0,Consumer=1
};
struct PCB{
    Kind kind;
    int times;
    Process* process;
};
class Process {
private:
    PCB PCB_obj;
public:
    explicit Process(int kind);

    const PCB& getPCB(){
        return this->PCB_obj;
    }

    void run(std::vector<int>& buffer);

    friend ostream& operator<<(ostream& out,Process& p);
};


#endif //PCMODEL_PROCESS_H
