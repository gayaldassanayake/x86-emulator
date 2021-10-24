#include "test.hpp"
#include "../utility_functions.hpp"

void test84(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 84 /r TEST r/m8, r8 MR
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("test\t%s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // execute
    // flag set
    
    uint8_t src1;
    uint8_t src2 = rb->getRegister(modrm_byte_decoded->second_operand_register);

    if(modrm_byte_decoded->is_first_operand_register){
        src1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &src1);
    }

    uint8_t temp = src1 & src2;

    uint8_t msb = temp & ((uint8_t)1<<7);

    rb->setFlag("SF", msb);
    if(temp == 0){
        rb->setFlag("ZF", 1);
    }
    else{
        rb->setFlag("ZF", 0);
    }
    rb->setFlag("PF", findParity(temp));
    rb->setFlag("CF", 0);
    rb->setFlag("OF", 0);
}

void test85(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 85 /r TEST r/m32, r32
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("test\t%s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // execute
    // flag set
    
    uint32_t src1;
    uint32_t src2 = rb->getRegister(modrm_byte_decoded->second_operand_register);

    if(modrm_byte_decoded->is_first_operand_register){
        src1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &src1);
    }

    uint32_t temp = src1 & src2;

    uint32_t msb = temp & ((uint32_t)1<<31);

    rb->setFlag("SF", msb);
    if(temp == 0){
        rb->setFlag("ZF", 1);
    }
    else{
        rb->setFlag("ZF", 0);
    }
    rb->setFlag("PF", findParity(temp));
    rb->setFlag("CF", 0);
    rb->setFlag("OF", 0);
}

void test(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x85:
            test85(ins_arg, reader, rb, memory);
            break;
        case 0x84:
            test84(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported test opcode\n");
            break;
    }
}
