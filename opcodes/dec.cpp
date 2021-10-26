#include <map>
#include "dec.hpp"
#include "../utility_functions.hpp"
#include "../utility_flag_set.hpp"

void dec40s(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 48+rd
    // DEC r32
    std::map<int, string>   opcode_reg_map = {
        { 0x48, "EAX" }, { 0x49, "ECX" }, { 0x4a, "EDX" }, { 0x4b, "EBX" },
        { 0x4c, "ESP" }, { 0x4d, "EBP" }, { 0x4e, "ESI" }, { 0x4f, "EDI" }
    };
    // decode
    string reg_name = opcode_reg_map[ins_arg->opcode];
    uint32_t arg = rb->getRegister(reg_name);
    printf("dec\t%%%s\n",reg_name.c_str());

    // execute
    uint32_t result = arg - 1;
    rb->setRegister(reg_name, result);
    setFlagsDec(arg, result, 31, rb);
}

void decfe(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory) {
    // FE/1
    // DEC r/m8
    // decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, false, false, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("dec\t%s\n",modrm_byte_decoded->decoded_print_string_op1.c_str());

    // execute
    uint32_t result;
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t result = arg - 1;
        rb->setRegister(modrm_byte_decoded->first_operand_register, result);
        setFlagsDec(arg, result, 7, rb);
    }
    else{
        uint8_t arg;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg);
        result = arg - 1;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (uint8_t)(result));
        setFlagsDec(arg, result, 7, rb);
    }
}

void decff(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory) {
    // FF/1
    // DEC r/m32
    // decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, false, false, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("dec\t%s\n",modrm_byte_decoded->decoded_print_string_op1.c_str());

    // execute
    uint32_t result, arg;
    if(modrm_byte_decoded->is_first_operand_register){
        arg = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t result = arg - 1;
        rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg);
        result = arg - 1;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, result);
    }
    setFlagsDec(arg, result, 31, rb);
}

void dec(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x48:
        case 0x49:  
        case 0x4a:
        case 0x4b:
        case 0x4c:
        case 0x4d:
        case 0x4e:
        case 0x4f:
            dec40s(ins_arg, reader, rb, memory);
            break;
        case 0xfe:
            decfe(ins_arg, reader, rb, memory);
            break;
        case 0xff:
            decff(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported Dec operand\n");
            break;
    }
}
