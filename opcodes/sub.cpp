#include <map>
#include "sub.hpp"
#include "../utility_functions.hpp"

void setSubFlags(RegisterBank *rb, uint32_t result){
    // OF, SF-1, ZF-1, AF, PF-1, and CF
    // rb->setFlag("OF",0);
    rb->setFlag("SF", result>>31);
    rb->setFlag("ZF", result==0);
    rb->setFlag("PF", findParity(result));
}

void sub28(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 28/r
    // SUB r/m8,r8 MR 
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("sub %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t result;
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, (arg1 - arg2));
    }
    else{
        uint8_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (uint8_t)result);
    }
    setSubFlags(rb, result);
}

void sub29(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 29/r
    // SUB r/m32,r32 MR 
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("sub %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t result;
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    }
    else{
        uint32_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, result);
    }
    setSubFlags(rb, result);
}

void sub2a(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 2a/r
    // SUB r8,r/m8 RM
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("sub %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t result;
    if(modrm_byte_decoded->is_second_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
    } else{
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint8_t arg2;
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2); // read 1 byte
        result = arg1-arg2;
    }
    rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    setSubFlags(rb, result);
}
void sub2b(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 2b/r
    // SUB r32,r/m32 RM
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("sub %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t result;
    if(modrm_byte_decoded->is_second_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
    } else{
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2;
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2); // read 4 byte
        result = arg1-arg2;
    }
    rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    setSubFlags(rb, result);
}
void sub2c(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 2c ib
    // SUB AL,imm8 I
    // Decode
    uint8_t imm8_byte = readDispalcement(reader, 1);

    printf("sub $%s,%%AL\n",intToHexStr(imm8_byte).c_str());

    // Execute
    uint8_t arg1 = rb->getRegister("AL");
    uint8_t result = arg1 - imm8_byte;
    rb->setRegister("AL", result);
    setSubFlags(rb, result);
}
void sub2d(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 2b id
    // SUB EAX,imm32 I
    // Decode
    uint32_t imm32_byte = readDispalcement(reader, 4);

    printf("sub $%s,%%EAX\n",intToHexStr(imm32_byte).c_str());

    // Execute
    uint32_t arg1 = rb->getRegister("AL");
    uint32_t result = arg1 - imm32_byte;
    rb->setRegister("EAX", result);
    setSubFlags(rb, result);
}

void sub(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x28:
            sub28(ins_arg, reader, rb, memory);
            break;
        case 0x29:
            sub29(ins_arg, reader, rb, memory);
            break;
        case 0x2a:
            sub2a(ins_arg, reader, rb, memory);
            break;
        case 0x2b:
            sub2b(ins_arg, reader, rb, memory);
            break;
        case 0x2c:
            sub2c(ins_arg, reader, rb, memory);
            break;
        case 0x2d:
            sub2d(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported Sub operand\n");
            break;
    }
}
