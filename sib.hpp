#ifndef SIB_H
#define SIB_H

#include <string>
#include <stdlib.h>
#include "reader.hpp"
#include "register.hpp"
using std::string;

struct SibDecodeInputArguments{
    uint8_t modrm_byte;
};

struct SibDecodeOutputArguments{
    uint32_t effective_addr;
    string decoded_print_string;
};

SibDecodeOutputArguments* decodeSIBByte(SibDecodeInputArguments* inputs, Reader *reader, RegisterBank *rb);

#endif