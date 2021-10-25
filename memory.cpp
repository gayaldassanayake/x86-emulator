#include "memory.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "utility_functions.hpp"
using std::cout;
using std::endl;

Memory::Memory(){
    
}

uint8_t Memory::readAddress(uint32_t address){
    if(memory_map.count(address)){
        return memory_map[address];
    }
    else return 0;
}

void Memory::writeToAddress(uint32_t address, uint8_t data){
    memory_map[address] = data;
}

void Memory::store(uint32_t address, uint8_t data){
    writeToAddress(address, data);
}

void Memory::store(uint32_t address, uint16_t data){
    uint32_t mask = 0b11111111;
    uint32_t data_to_write;

    for(int i=0; i < 2; i++){
        data_to_write = data & mask;
        data = data >> 8;
        writeToAddress(address, data_to_write);
        address ++;
    }
}

void Memory::store(uint32_t address, uint32_t data){
    uint32_t mask = 0b11111111;
    uint32_t data_to_write;

    for(int i=0; i < 4; i++){
        data_to_write = data & mask;
        data = data >> 8;
        writeToAddress(address, data_to_write);
        address ++;
    }
}

void Memory::store(uint32_t address, uint64_t data){
    uint32_t mask = 0b11111111;
    uint32_t data_to_write;

    for(int i=0; i < 8; i++){
        data_to_write = data & mask;
        data = data >> 8;
        writeToAddress(address, data_to_write);
        address ++;
    }
}


void Memory::read(uint32_t address, uint8_t *data){
    uint8_t tmp = readAddress(address);
    memcpy(data, &tmp, sizeof(*data));
}

void Memory::read(uint32_t address, uint16_t *data){
    uint16_t tmp = 0;

    for(int i=0; i < 2; i++){
        uint16_t read_byte = (uint16_t)readAddress(address);
        tmp =  tmp | (read_byte << (i*8));
        address ++;
    }

    memcpy(data, &tmp, sizeof(*data));
}

void Memory::read(uint32_t address, uint32_t *data){

    uint32_t tmp = 0;

    for(int i=0; i < 4; i++){
        uint32_t read_byte = (uint32_t)readAddress(address);
        tmp =  tmp | (read_byte << (i*8));
        address ++;
    }
    
    memcpy(data, &tmp, sizeof(*data));
}

void Memory::read(uint32_t address, uint64_t *data){
    uint64_t tmp = 0;

    for(int i=0; i < 8; i++){
        uint64_t read_byte = (uint64_t)readAddress(address);
        tmp =  tmp | (read_byte << (i*8));
        address ++;
    }
    
    memcpy(data, &tmp, sizeof(*data));
}

void Memory::dumpMemory(){
    std::fstream file;
    file.open("memory_dump.out",std::fstream::out);
    
    std::map<uint32_t, uint8_t>::iterator itr;

    print(cout, file, "\n******* Memory Dump *******\n\n");
    print(cout, file, "(NOTE: Only non-zero values are printed.)\n\n");
    print(cout, file, "Address\t|      Value \n");
    print(cout, file, "---------------------------\n");

    for (itr = memory_map.begin(); itr != memory_map.end(); ++itr) {
        if(itr->second == 0){
            continue;
        }
        print(cout, file, intToHexStr(itr->first) + "\t| " + intToHexFmtStr(itr->second, 8, 2) + " | " + intToBinFmtStr(itr->second, 8, 8) + "\n");
    }

    file.close();
}