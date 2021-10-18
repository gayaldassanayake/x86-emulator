#include "add.hpp"

void add03(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    printModRm(modrm_byte_decoded);

    // cout<< modrm_byte_decoded->decoded_print_string_op1<<endl;
    // cout<< modrm_byte_decoded->decoded_print_string_op2<<endl;

    printf("add %s, %s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_second_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        rb->setRegister(modrm_byte_decoded->second_operand_register, (arg1 + arg2));
    }
    else{
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2;
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2); // read 4 bytes

        rb->setRegister(modrm_byte_decoded->second_operand_register, (arg1 + arg2));
    }
}
