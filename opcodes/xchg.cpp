#include "xchg.hpp"
#include "../utility_functions.hpp"

void xchg86(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // XCHG r8, r/m8
    // 86 /r
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("xchg\t%s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // execute

    uint8_t src1;
    uint8_t src2 = rb->getRegister(modrm_byte_decoded->second_operand_register);

    if(modrm_byte_decoded->is_first_operand_register){
        src1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        rb->setRegister(modrm_byte_decoded->first_operand_register, src2);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &src1);
        memory->store(modrm_byte_decoded->first_operand_effective_addr, src2);
    }
    rb->setRegister(modrm_byte_decoded->second_operand_register, src1);
}

void xchg87(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // XCHG r32, r/m32
    // 86 /r
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("xchg\t%s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // execute

    uint32_t src1;
    uint32_t src2 = rb->getRegister(modrm_byte_decoded->second_operand_register);

    if(modrm_byte_decoded->is_first_operand_register){
        src1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        rb->setRegister(modrm_byte_decoded->first_operand_register, src2);
    }
    else{
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &src1);
        memory->store(modrm_byte_decoded->first_operand_effective_addr, src2);
    }
    rb->setRegister(modrm_byte_decoded->second_operand_register, src1);
}

void xchg90s(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // XCHG EAX, r32
    // 90+rd
    // Decode
    std::map<int, string>   opcode_reg_map = {
        { 0x91, "ECX" }, { 0x92, "EDX" }, { 0x93, "EBX" },
        { 0x94, "ESP" }, { 0x95, "EBP" }, { 0x96, "ESI" }, { 0x97, "EDI" }
    };
    string reg_name = opcode_reg_map[ins_arg->opcode];
    uint32_t arg1 = rb->getRegister("EAX");
    uint32_t arg2 = rb->getRegister(reg_name);
    printf("xchg %%%s,%%EAX\n",reg_name.c_str());

    // execute
    rb->setRegister("EAX", arg2);
    rb->setRegister(reg_name, arg1);
}

void xchg(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x86:
            xchg86(ins_arg, reader, rb, memory);
            break;
        case 0x87:
            xchg87(ins_arg, reader, rb, memory);
            break;
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
        case 0x95:
        case 0x96:
        case 0x97:
            xchg90s(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported xchg opcode\n");
            break;
    }
}
