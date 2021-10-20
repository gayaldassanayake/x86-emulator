#include "mov.hpp"

void mov88(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 88 /r
    // MOV r/m8, r8 MR
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("mov %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t arg = rb->getRegister(modrm_byte_decoded->second_operand_register);
    if(modrm_byte_decoded->is_first_operand_register) {
        rb->setRegister(modrm_byte_decoded->first_operand_register, arg);
    } else {
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (uint8_t)arg);
    }
}

void mov89(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 89 /r
    // MOV r/m32, r32 MR
    // Decode   
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("mov %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t arg = rb->getRegister(modrm_byte_decoded->second_operand_register);
    // cout<<"copying register value:"<<std::hex<<arg<<endl;
    if(modrm_byte_decoded->is_first_operand_register) {
        rb->setRegister(modrm_byte_decoded->first_operand_register, arg);
        // cout<<"copyied register value:"<<std::hex<<rb->getRegister(modrm_byte_decoded->first_operand_register)<<endl;
    } else {
        memory->store(modrm_byte_decoded->first_operand_effective_addr, arg);
        // memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg);
        // cout<<"copyied memory value:"<<std::hex<<arg<<endl;
    }
}

void mov8a(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 8A /r
    // MOV r8, r/m8 RM
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("mov %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint8_t arg;
    if(modrm_byte_decoded->is_second_operand_register) {
        arg = (uint8_t)rb->getRegister(modrm_byte_decoded->second_operand_register);
        // cout<<"copying register value:"<<std::hex<<arg<<endl;
    } else {
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg); // read 1 byte
        // cout<<"copying memory value:"<<std::hex<<arg<<endl;
    }
    rb->setRegister(modrm_byte_decoded->first_operand_register, (uint32_t)arg);
    // cout<<"copyied register value:"<<std::hex<<rb->getRegister(modrm_byte_decoded->first_operand_register)<<endl;
}

void mov8b(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // 8B /r
    // MOV r32, r/m32 RM
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    printf("mov %s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    uint32_t arg;
    if(modrm_byte_decoded->is_second_operand_register) {
        arg = rb->getRegister(modrm_byte_decoded->second_operand_register);
        // cout<<"copying register value:"<<std::hex<<arg<<endl;
    } else {
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg); // read 4 bytes
        // cout<<"copying memory value:"<<std::hex<<arg<<endl;
    }
    rb->setRegister(modrm_byte_decoded->first_operand_register, arg);
    // cout<<"copyied register value:"<<std::hex<<rb->getRegister(modrm_byte_decoded->first_operand_register)<<endl;
}

void movc6(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // C6 /0 ib
    // MOV r/m8, imm8 MI
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, false, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    uint8_t operand2 = readDispalcement(reader, 1);

    printf("mov 0x%x,%s\n",operand2, modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_first_operand_register) {
        rb->setRegister(modrm_byte_decoded->first_operand_register, (uint32_t)operand2);
    } else {
        memory->store(modrm_byte_decoded->first_operand_effective_addr, operand2);
    }
}

void movc7(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // C7 /0 id
    // MOV r/m32, imm32 MI
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, false, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    uint32_t operand2 = readDispalcement(reader, 4);

    printf("mov 0x%x,%s\n",operand2, modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_first_operand_register) {
        rb->setRegister(modrm_byte_decoded->first_operand_register, operand2);
    } else {
        memory->store(modrm_byte_decoded->first_operand_effective_addr, operand2);
    }
}

void mov(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x88:
            mov88(ins_arg, reader, rb, memory);
            break;
        case 0x89:
            mov89(ins_arg, reader, rb, memory);
            break;
        case 0x8a:
            mov8a(ins_arg, reader, rb, memory);
            break;
        case 0x8b:
            mov8b(ins_arg, reader, rb, memory);
            break;
        case 0xc6:
            movc6(ins_arg, reader, rb, memory);
            break;
        case 0xc7:
            movc7(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported Mov operand\n");
            break;
    }
}
