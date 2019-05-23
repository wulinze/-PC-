#include <iostream>
#include "Manager.h"


using namespace std;

int main() {
    auto *m = new Manager();
    int opt;
    m->Show();
    while(cin >> opt){
        m->Action(opt);
        m->Show();
    }
    return 0;
}