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
    std::map<int, string>   opcode_reg_map = {
        { 0x40, "EAX" }, { 0x41, "ECX" }, { 0x42, "EDX" }, { 0x43, "EBX" },
        { 0x44, "ESP" }, { 0x45, "EBP" }, { 0x46, "ESI" }, { 0x47, "EDI" }
    };
    // decode
    string reg_name = opcode_reg_map[ins_arg->opcode];
    uint32_t arg = rb->getRegister(reg_name);
    printf("inc %%%s\n",reg_name.c_str());

    // execute
    uint32_t result = arg + 1;
    rb->setRegister(reg_name, result);
    setIncFlags(rb, result);
}

void incfe(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory) {
    // FE/0
    // INC r/m8
    // decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, false, false, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("inc %s\n",modrm_byte_decoded->decoded_print_string_op1.c_str());

    // execute
    uint32_t result;
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t result = arg + 1;
        rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    }
    else{
        uint8_t arg;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg);
        result = arg + 1;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (uint8_t)(result));
    }
    setIncFlags(rb, result);  
}

void incff(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory) {
    // FF/0
    // INC r/m32
    // decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, false, false, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("inc %s\n",modrm_byte_decoded->decoded_print_string_op1.c_str());

    // execute
    uint32_t result;
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t result = arg + 1;
        rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    }
    else{
        uint32_t arg;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg);
        result = arg + 1;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, result);
    }
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
        case 0xfe:
            incfe(ins_arg, reader, rb, memory);
            break;
        case 0xff:
            incff(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported Inc operand\n");
            break;
    }
}
