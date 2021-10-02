#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

class Memory{
    
    private:
        uint32_t size;
        uint8_t *memory_array;

    public:
        Memory(uint32_t size);

        void store(uint32_t address, uint8_t data);
        void store(uint32_t address, uint16_t data);
        void store(uint32_t address, uint32_t data);
        void store(uint32_t address, uint64_t data);

        void read(uint32_t address, uint8_t *data);
        void read(uint32_t address, uint16_t *data);
        void read(uint32_t address, uint32_t *data);
        void read(uint32_t address, uint64_t *data);
};

#endif