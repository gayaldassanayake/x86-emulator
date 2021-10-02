#include <iostream>
#include "modmr.hpp"
#include "reader.hpp"
using std::cout;
using std::endl;

int main(){

    cout<<std::hex;

    Reader reader("sample1.txt");
    while(!reader.isEOF()){
        uint8_t tmp=reader.readNextByte();
        cout<<(uint32_t)tmp<<endl;
    }
}