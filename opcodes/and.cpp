#include "and.hpp"

void and24(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 24 ib   
    // And AL,imm9
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("add %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        rb->setRegister(modrm_byte_decoded->first_operand_register, (arg1 + arg2));
    }
    else{
        uint8_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (uint8_t)(arg1 + arg2));
    }
}

void and_(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x24:
            and24(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported And operand\n");
            break;
    }
}