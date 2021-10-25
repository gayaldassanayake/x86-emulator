#include "or.hpp"
#include "../utility_functions.hpp"
#include "../utility_flag_set.hpp"

void or0c(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 0C ib   
    // Or AL,imm8 I
    // Decode
    uint8_t imm8_byte = readDispalcement(reader, 1);
    string reg_name = "AL";

    printf("or $%s,%%%s\n", intToHexStr(imm8_byte).c_str(), reg_name.c_str());

    // Execute
    uint8_t arg1 = rb->getRegister(reg_name);
    uint8_t ans = arg1 | imm8_byte;
    rb->setRegister(reg_name, ans);
    
    setFlagsOr(arg1, imm8_byte, ans, 7, rb);
}

void or0d(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 0D id
    // Or EAX,imm32 I
    // Decode
    uint32_t imm32_byte = readDispalcement(reader, 4);
    string reg_name = "EAX";

    printf("or $%s,%%%s\n", intToHexStr(imm32_byte).c_str(), reg_name.c_str());

    // Execute
    uint32_t arg1 = rb->getRegister(reg_name);
    uint32_t ans = arg1 | imm32_byte;
    rb->setRegister(reg_name, ans);
    setFlagsOr(arg1, imm32_byte, ans, 31, rb);
}

void or08(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 08/r  
    // Or r/m8,r8 MR
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("or %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
    uint32_t ans;
    if(modrm_byte_decoded->is_first_operand_register) {
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        ans = arg1 | arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
        setFlagsOr(arg1, arg2, ans, 7, rb);
    } else {
        uint8_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        ans = arg1 | arg2;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (uint8_t)ans);
        setFlagsOr(arg1, arg2, ans, 7, rb);
    }
}

void or09(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 09/r  
    // Or r/m32,r32 MR
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("or %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t arg1;
    uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
    uint32_t ans;
    if(modrm_byte_decoded->is_first_operand_register) {
        arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        ans = arg1 | arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
    } else {
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        ans = arg1 | arg2;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, ans);
    }
    setFlagsOr(arg1, arg2, ans, 31, rb);
}

void or0a(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 0a/r  
    // Or r8,r/m8 RM
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("or %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t ans;
    uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    if(modrm_byte_decoded->is_second_operand_register) {
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        ans = arg1 | arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
        setFlagsOr(arg1, arg2, ans, 7, rb);
    } else {
        uint8_t arg2;
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2);
        ans = arg1 | (uint32_t)arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
        setFlagsOr(arg1, arg2, ans, 7, rb);
    }
}

void or0b(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 0b/r  
    // Or r32,r/m32 RM
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    printf("or %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    uint32_t arg2;
    if(modrm_byte_decoded->is_second_operand_register) {
        arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
    } else {
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2);
    }
    uint32_t ans = arg1 | arg2;
    rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
    setFlagsOr(arg1, arg2, ans, 31, rb);
}

void or_(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x0C:
            or0c(ins_arg, reader, rb, memory);
            break;
        case 0x0D:
            or0d(ins_arg, reader, rb, memory);
            break;
        case 0x08:
            or08(ins_arg, reader, rb, memory);
            break;
        case 0x09:
            or09(ins_arg, reader, rb, memory);
            break;
        case 0x0A:
            or0a(ins_arg, reader, rb, memory);
            break;
        case 0x0B:
            or0b(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported Or operand\n");
            break;
    }
}
