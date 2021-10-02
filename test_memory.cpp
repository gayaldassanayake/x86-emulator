#include <iostream>
#include "memory.hpp"
using std::cout;
using std::endl;

int main(){

    Memory memory(100);

    uint8_t a = 1;

    memory.store(10,a);
    memory.store(11,a);
    memory.store(12,a);

    uint32_t c;
    memory.read(10, &c);

    cout<<(uint32_t)c<<endl;

}