#include <map>
#include "sub.hpp"
#include "../utility_functions.hpp"
#include "../utility_flag_set.hpp"

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
        setFlagsSub(arg1, arg2, result, 7, rb);
    }
    else{
        uint8_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (uint8_t)result);
        setFlagsSub(arg1, arg2, result, 7, rb);
    }
}

void sub29(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 29/r
    // SUB r/m32,r32 MR 
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("sub %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t result, arg1, arg2;
    if(modrm_byte_decoded->is_first_operand_register){
        arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, result);
    }
    setFlagsSub(arg1, arg2, result, 31, rb);
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
        setFlagsSub(arg1, arg2, result, 7, rb);
    } else{
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint8_t arg2;
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2); // read 1 byte
        result = arg1-arg2;
        setFlagsSub(arg1, arg2, result, 7, rb);
    }
    rb->setRegister(modrm_byte_decoded->first_operand_register, result);
}
void sub2b(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 2b/r
    // SUB r32,r/m32 RM
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("sub %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t result, arg1, arg2;
    if(modrm_byte_decoded->is_second_operand_register){
        arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        result = arg1-arg2;
    } else{
        arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2); // read 4 byte
        result = arg1-arg2;
    }
    rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    setFlagsSub(arg1, arg2, result, 31, rb);
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
    setFlagsSub(arg1, imm8_byte, result, 7, rb);
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
    setFlagsSub(arg1, imm32_byte, result, 31, rb);
}

void sub80(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory) {
    // 80 /5 ib
    // SUB r/m8,imm8 MI
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, false, false, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    uint8_t imm8_byte = readDispalcement(reader, 1);

    printf("sub $%s,%s\n",intToHexStr(imm8_byte).c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    uint8_t result;
    // Execute
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        result = arg1 - imm8_byte;
        rb->setRegister(modrm_byte_decoded->first_operand_register, result);
        setFlagsSub(arg1, imm8_byte, result, 7, rb);
    }
    else{
        uint8_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        result = arg1 - imm8_byte;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, result);
        setFlagsSub(arg1, imm8_byte, result, 7, rb);
    }
}

void sub81(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory) {
    // 81 /5 id
    // SUB r/m32,imm32 MI
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, false, false, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    uint32_t imm32_byte = readDispalcement(reader, 4);

    printf("sub $%s,%s\n",intToHexStr(imm32_byte).c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    uint32_t result, arg1;
    // Execute
    if(modrm_byte_decoded->is_first_operand_register){
        arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        result = arg1 - imm32_byte;
        rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        result = arg1 - imm32_byte;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, result);
    }
    setFlagsSub(arg1, imm32_byte, result, 31, rb);
}

void sub83(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory) {
    // 83 /5 ib
    // SUB r/m32,imm8 MI
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, false, false, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    uint32_t imm8_byte = readDispalcement(reader, 1);

    printf("sub $%s,%s\n",intToHexStr(imm8_byte).c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    uint32_t result, arg1;
    // Execute
    if(modrm_byte_decoded->is_first_operand_register){
        arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        result = arg1 - imm8_byte;
        rb->setRegister(modrm_byte_decoded->first_operand_register, result);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        result = arg1 - imm8_byte;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, result);
    }
    setFlagsSub(arg1, imm8_byte, result, 31, rb);
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
        case 0x80:
            sub80(ins_arg, reader, rb, memory);
            break;
        case 0x81:
            sub81(ins_arg, reader, rb, memory);
            break;
        case 0x83:
            sub83(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported Sub operand\n");
            break;
    }
}
