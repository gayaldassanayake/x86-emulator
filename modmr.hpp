#ifndef MODRM_H
#define MODRM_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using std::string;

enum OperandType
{
  REGISTER_32,
  REGISTER_16,
  REGISTER_8,
  REGISTER_MM,
  REGISTER_XMM
};

struct ModMrDecodeInputArguments{
    uint8_t modmr_byte;
    // int rm_operand_length;
    // int reg_operand_length;
    enum OperandType rm_operand_type;
    enum OperandType reg_operand_type;
};

struct ModMrDecodeOutputArguments{
    string rm_operand;
    string reg_operand;
    int displacement;
    bool is_SIB_available;
    bool is_rm_op_memory_location;
};

ModMrDecodeOutputArguments* decodeModeMrByte(ModMrDecodeInputArguments* inputs);
void printModRm(ModMrDecodeOutputArguments* outputs);

#endif