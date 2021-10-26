#ifndef MODRM_H
#define MODRM_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "reader.hpp"
#include "memory.hpp"
#include "register.hpp"
#include "sib.hpp"
using std::string;
using std::cout;
using std::endl;

enum OperandRegisterType
{
  REGISTER_32,
  REGISTER_16,
  REGISTER_8,
  REGISTER_MM,
  REGISTER_XMM
};

struct ModMrDecodeInputArguments{
    bool is_first_operand_reg;
    bool is_second_operand_reg;
    bool has_second_operand;

    enum OperandRegisterType rm_operand_register_type;
    enum OperandRegisterType reg_operand_register_type;
};

struct ModMrDecodeOutputArguments{

    bool is_first_operand_register;
    bool is_second_operand_register;

    uint32_t first_operand_effective_addr;
    uint32_t second_operand_effective_addr;

    string first_operand_register;
    string second_operand_register;

    string decoded_print_string_op1;
    string decoded_print_string_op2;
};

ModMrDecodeOutputArguments* decodeModeMrByte(ModMrDecodeInputArguments* inputs, Reader *reader, RegisterBank *rb, Memory *memory);
void printModRm(ModMrDecodeOutputArguments* outputs);

#endif