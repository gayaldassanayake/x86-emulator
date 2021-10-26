#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <map>

class Memory{
    
    private:
        std::map<uint32_t, uint8_t> memory_map;

        uint8_t readAddress(uint32_t address);
        void writeToAddress(uint32_t address, uint8_t data);

    public:
        Memory();

        void store(uint32_t address, uint8_t data);
        void store(uint32_t address, uint16_t data);
        void store(uint32_t address, uint32_t data);
        void store(uint32_t address, uint64_t data);

        void read(uint32_t address, uint8_t *data);
        void read(uint32_t address, uint16_t *data);
        void read(uint32_t address, uint32_t *data);
        void read(uint32_t address, uint64_t *data);

        void dumpMemory();
};

#endif