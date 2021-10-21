#include <map>
#include "inc.hpp"
#include "../utility_functions.hpp"

// int checkIncOverflow(uint32_t value, uint32_t size) {
//     uint32_t original = value -1;
//     value = (value << (32-size)) | ((1<<(32-size))-1);
//     original = (original << (32-size)) | ((1<<(32-size))-1);
//     if(original>0 && value<0) {
//         return 1;
//     }
//     return 0;
// }

std::map<int, string>   opcode_reg_map = {
    { 0x40, "EAX" }, { 0x41, "ECX" }, { 0x42, "EDX" }, { 0x43, "EBX" },
    { 0x44, "ESP" }, { 0x45, "EBP" }, { 0x46, "ESI" }, { 0x47, "EDI" }
};

void setIncFlags(RegisterBank *rb, uint32_t result){
    // OF, SF, ZF, AF, and PF
    // rb->setFlag("OF",0);
    rb->setFlag("SF", result>>31);
    rb->setFlag("ZF", result==0);
    rb->setFlag("PF", findParity(result));
}

void inc40s(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 40+rd
    // INC r32
    // decode
    string reg_name = opcode_reg_map[ins_arg->opcode];
    uint32_t arg = rb->getRegister(reg_name);
    printf("inc %%%s\n",reg_name.c_str());

    // execute
    uint32_t result = arg + 1;
    rb->setRegister(reg_name, result);
    setIncFlags(rb, result);
}

void inc(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
            inc40s(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported Add operand\n");
            break;
    }
}
