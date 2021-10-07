#ifndef UTILS_H
#define UTILS_H

#include <cstdint>

struct InstructionArguments{
    uint8_t legacy_prefix;
    // rex_prefixes
    uint8_t opcode;
    uint8_t opcode_byte_1;
    uint8_t opcode_byte_2;
    uint8_t opcode_byte_3;
    uint8_t opcode_byte_4;
    int opcode_type;
    bool has_leg_prefix = false;
};

#endif