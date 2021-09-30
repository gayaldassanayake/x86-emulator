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
    uint32_t modmr_byte;
    // int first_operand_length;
    // int second_operand_length;
    enum OperandType first_operand_type;
    enum OperandType second_operand_type;
};

struct ModMrDecodeOutputArguments{
    string first_operand;
    string second_operand;
    int displacement;
    bool is_SIB_available;
    bool is_first_op_memory_location;
};

ModMrDecodeOutputArguments* decodeModeMrByte(ModMrDecodeInputArguments* inputs);
