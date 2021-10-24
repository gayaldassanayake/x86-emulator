#include "cmp.hpp"
#include "../utility_flag_set.hpp"

void cmp38(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    //38 /r CMP r/m8, r8 MR         Compare r8 with r/m8.
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("cmp %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint8_t src1;
    uint8_t src2 = rb->getRegister(modrm_byte_decoded->second_operand_register);

    if(modrm_byte_decoded->is_first_operand_register){
        src1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &src1);
    }

    uint8_t temp = src1 - src2;

    setFlagsSub(src1, src2, temp, 7, rb);

}

void cmp39(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 39 /r CMP r/m32, r32 MR      Compare r32 with r/m32.
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("cmp %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t src1;
    uint32_t src2 = rb->getRegister(modrm_byte_decoded->second_operand_register);

    if(modrm_byte_decoded->is_first_operand_register){
        src1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &src1);
    }

    uint32_t temp = src1 - src2;

    setFlagsSub(src1, src2, temp, 31, rb);

}

void cmp3a(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 3A /r CMP r8, r/m8 RM        Compare r/m8 with r8
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("cmp %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint8_t src1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    uint8_t src2;

    if(modrm_byte_decoded->is_second_operand_register){
        src2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
    }
    else{
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &src2);
    }

    uint8_t temp = src1 - src2;

    setFlagsSub(src1, src2, temp, 7, rb);

}

void cmp3b(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 3B /r CMP r32, r/m32 RM      Compare r/m32 with r32
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("cmp %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t src1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
    uint32_t src2;

    if(modrm_byte_decoded->is_second_operand_register){
        src2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
    }
    else{
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &src2);
    }

    uint32_t temp = src1 - src2;

    setFlagsSub(src1, src2, temp, 31, rb);

}


void cmp(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x38:
            cmp38(ins_arg, reader, rb, memory);
            break;
        case 0x39:
            cmp39(ins_arg, reader, rb, memory);
            break;
        case 0x3a:
            cmp3a(ins_arg, reader, rb, memory);
            break;
        case 0x3b:
            cmp3b(ins_arg, reader, rb, memory);
            break;

        default:
            printf("Unsupported cmp opcode\n");
            break;
    }
}