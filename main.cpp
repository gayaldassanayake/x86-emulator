#include <iostream>
#include "modmr.hpp"
using std::cout;
using std::endl;

std::ifstream infile; 

// string readNextByte(){
//     string nextByte;
//     while(infile>>nextByte){
//         return nextByte;
//     }
//     return "EOF";
// }

uint32_t readNextByte(){
    uint32_t nextByte;
    while(infile>>nextByte){
        return nextByte;
    }
    return 1000;
}

int main(){
    infile.open("sample1.txt"); 
    infile >> std::hex;
    cout<<std::hex;

   uint32_t tmp=readNextByte();
   while(tmp<500){
       std::cout<<tmp<<" ";
       tmp=readNextByte();

   }

    // cout<<std::hex;
    // for(int i=0;i<5;i++){
    //     uint32_t tmp=readNextByte();
    //     cout<<tmp<<endl;
    // }
}