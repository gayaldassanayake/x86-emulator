#include "memory.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>

Memory::Memory(uint32_t size){
    this->size = size;
    this->memory_array = (uint8_t*)malloc(size*sizeof(uint8_t));
}

void Memory::store(uint32_t address, uint8_t data){
    memcpy(&memory_array[address], &data, sizeof(data));
}

void Memory::store(uint32_t address, uint16_t data){
    memcpy(&memory_array[address], &data, sizeof(data));
}

void Memory::store(uint32_t address, uint32_t data){
    memcpy(&memory_array[address], &data, sizeof(data));
}

void Memory::store(uint32_t address, uint64_t data){
    memcpy(&memory_array[address], &data, sizeof(data));
}


void Memory::read(uint32_t address, uint8_t *data){
    memcpy(data, &memory_array[address], sizeof(*data));
}

void Memory::read(uint32_t address, uint16_t *data){
    memcpy(data, &memory_array[address], sizeof(*data));
}

void Memory::read(uint32_t address, uint32_t *data){
    memcpy(data, &memory_array[address], sizeof(*data));
}

void Memory::read(uint32_t address, uint64_t *data){
    memcpy(data, &memory_array[address], sizeof(*data));
}