//
// Created by 82490 on 2019/5/23.
//

#include "Process.h"

void Process::run(std::vector<int>& buffer) {
    this->PCB_obj.times++;
    if(this->PCB_obj.kind==Kind::Producer){
        buffer.emplace_back(this->PCB_obj.times);
    } else if(this->PCB_obj.kind==Kind::Consumer){
        buffer.erase(buffer.begin());
    }
}

Process::Process(int kind) {
    this->PCB_obj.kind = Kind (kind);
    this->PCB_obj.times = 0;
    this->PCB_obj.process = this;
}

ostream &operator<<(ostream &out, Process &p) {
    if(p.getPCB().kind==Kind::Producer){
        out << "(Producer,";
    } else{
        out << "(Consumer,";
    }
    out << "times:" << p.getPCB().times << ')';
    return out;
}

