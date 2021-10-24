#include "and.hpp"
#include "../utility_functions.hpp"

void setAndFlags(RegisterBank *rb, uint32_t result){
    rb->setFlag("OF", 0);
    rb->setFlag("CF", 0);
    rb->setFlag("SF", result>>31);
    rb->setFlag("ZF", result==0);
    rb->setFlag("PF", findParity(result));
}

void and24(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 24 ib   
    // And AL,imm8 I
    // Decode
    uint8_t imm8_byte = readDispalcement(reader, 1);
    string reg_name = "AL";

    printf("and $%s,%%%s\n", intToHexStr(imm8_byte).c_str(), reg_name.c_str());

    // Execute
    uint8_t arg1 = rb->getRegister(reg_name);
    uint8_t ans = arg1 & imm8_byte;
    rb->setRegister(reg_name, ans);
    
    setAndFlags(rb, ans);
}

void and25(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 25 id  
    // And EAX,imm32 I
    // Decode
    uint32_t imm32_byte = readDispalcement(reader, 4);
    string reg_name = "EAX";

    printf("and $%s,%%%s\n", intToHexStr(imm32_byte).c_str(), reg_name.c_str());

    // Execute
    uint32_t arg1 = rb->getRegister(reg_name);
    uint32_t ans = arg1 & imm32_byte;
    rb->setRegister(reg_name, ans);
    setAndFlags(rb, ans);
}

void and20(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 20/r  
    // And r/m8,r8 MR
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("and %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
    uint32_t ans;
    if(modrm_byte_decoded->is_first_operand_register) {
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        ans = arg1 & arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
    } else {
        uint8_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        ans = arg1 & arg2;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (uint8_t)ans);
    }
    setAndFlags(rb, ans);
}

void and21(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 21/r  
    // And r/m32,r32 MR
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("and %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t arg1;
    uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
    uint32_t ans;
    if(modrm_byte_decoded->is_first_operand_register) {
        arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        ans = arg1 & arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
    } else {
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        ans = arg1 & arg2;
        memory->store(modrm_byte_decoded->first_operand_effective_addr, ans);
    }
    setAndFlags(rb, ans);
}

void and22(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 22/r  
    // And r8,r/m8 RM
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("and %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t ans;
    uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    if(modrm_byte_decoded->is_second_operand_register) {
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        ans = arg1 & arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
    } else {
        uint8_t arg2;
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2);
        ans = arg1 & (uint32_t)arg2;
        rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
    }
    setAndFlags(rb, ans);
}

void and23(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 23/r  
    // And r32,r/m32 RM
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    printf("and %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    uint32_t arg2;
    if(modrm_byte_decoded->is_second_operand_register) {
        arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
    } else {
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2);
    }
    uint32_t ans = arg1 & arg2;
    rb->setRegister(modrm_byte_decoded->first_operand_register, ans);
    setAndFlags(rb, ans);
}

void and_(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x24:
            and24(ins_arg, reader, rb, memory);
            break;
        case 0x25:
            and25(ins_arg, reader, rb, memory);
            break;
        case 0x20:
            and20(ins_arg, reader, rb, memory);
            break;
        case 0x21:
            and21(ins_arg, reader, rb, memory);
            break;
        case 0x22:
            and22(ins_arg, reader, rb, memory);
            break;
        case 0x23:
            and23(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported And operand\n");
            break;
    }
}
