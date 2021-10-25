#include "add.hpp"
#include "../utility_functions.hpp"
#include "../utility_flag_set.hpp"

void add00(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 00 /r ADD r/m8, r8 MR    Add r8 to r/m8.
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("add\t%s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        rb->setRegister(modrm_byte_decoded->first_operand_register, (arg1 + arg2));

        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, arg2, arg1 + arg2, 7, rb);
    }
    else{
        uint8_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (uint8_t)(arg1 + arg2));

        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, arg2, arg1 + arg2, 7, rb);
    }
}

void add01(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 01 /r ADD r/m32, r32 MR      Add r32 to r/m32.
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, true, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("add\t%s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        rb->setRegister(modrm_byte_decoded->first_operand_register, (arg1 + arg2));
        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, arg2, arg1 + arg2, 31, rb);
    }
    else{
        uint32_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (arg1 + arg2));
        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, arg2, arg1 + arg2, 31, rb);
    }
}

void add02(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 02 /r ADD r8, r/m8 RM
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_8, REGISTER_8});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("add\t%s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_second_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        rb->setRegister(modrm_byte_decoded->second_operand_register, (arg1 + arg2));
        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, arg2, arg1 + arg2, 7, rb);
    }
    else{
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint8_t arg2;
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2); // read 4 bytes

        rb->setRegister(modrm_byte_decoded->second_operand_register, (arg1 + (uint32_t)arg2));
        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, arg2, arg1 + arg2, 7, rb);
    }
}

void add03(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 03 /r ADD r32, r/m32 RM
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    
    printf("add\t%s,%s\n",modrm_byte_decoded->decoded_print_string_op2.c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_second_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2 = rb->getRegister(modrm_byte_decoded->second_operand_register);
        rb->setRegister(modrm_byte_decoded->second_operand_register, (arg1 + arg2));
        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, arg2, arg1 + arg2, 31, rb);
    }
    else{
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        uint32_t arg2;
        memory->read(modrm_byte_decoded->second_operand_effective_addr, &arg2); // read 4 bytes

        rb->setRegister(modrm_byte_decoded->second_operand_register, (arg1 + arg2));
        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, arg2, arg1 + arg2, 31, rb);
    }
}

void add04(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 04 ib ADD AL, imm8 I     Add imm8 to AL
    int8_t imm8_byte = readDispalcement(reader, 1);

    printf("add\t$%s,%%AL\n",intToHexStr(imm8_byte).c_str());

    // Execute
    uint8_t arg1 = rb->getRegister("AL");
    uint8_t ans = arg1 + imm8_byte;
    rb->setRegister("AL", ans);

    // Set CF, OF, SF, ZF, AF, and PF
    setFlagsAdd(arg1, imm8_byte, ans, 7, rb);
}

void add81(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // 81 /0 id ADD r/m32, imm32 MI
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, false, false, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    int32_t operand2 = readDispalcement(reader, 4);

    printf("add\t$%s,%s\n",intToHexStr(operand2).c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        rb->setRegister(modrm_byte_decoded->first_operand_register, (arg1 + operand2));
        
        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, operand2, arg1 + operand2, 31, rb);
    }
    else{
        uint32_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (arg1 + operand2));

        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, operand2, arg1 + operand2, 31, rb);
    }
}

void add83(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    // ADD r/m32, imm8 MI
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({false, false, false, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);

    int32_t operand2 = (int32_t)(uint8_t)readDispalcement(reader, 1);

    printf("add\t$%s,%s\n",intToHexStr(operand2).c_str(), modrm_byte_decoded->decoded_print_string_op1.c_str());

    // Execute
    if(modrm_byte_decoded->is_first_operand_register){
        uint32_t arg1 = rb->getRegister(modrm_byte_decoded->first_operand_register);
        rb->setRegister(modrm_byte_decoded->first_operand_register, (arg1 + operand2));
       
        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, operand2, arg1 + operand2, 31, rb);
    }
    else{
        uint32_t arg1;
        memory->read(modrm_byte_decoded->first_operand_effective_addr, &arg1);
        memory->store(modrm_byte_decoded->first_operand_effective_addr, (arg1 + operand2));

        // Set CF, OF, SF, ZF, AF, and PF
        setFlagsAdd(arg1, operand2, arg1 + operand2, 31, rb);
    }
}

void add(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x0:
            add00(ins_arg, reader, rb, memory);
            break;
        case 0x1:
            add01(ins_arg, reader, rb, memory);
            break;
        case 0x2:
            add02(ins_arg, reader, rb, memory);
            break;
        case 0x3:
            add03(ins_arg, reader, rb, memory);
            break;
        case 0x4:
            add04(ins_arg, reader, rb, memory);
            break;
        case 0x81:
            add81(ins_arg, reader, rb, memory);
            break;
        case 0x83:
            add83(ins_arg, reader, rb, memory);
            break;
        
        default:
            printf("Unsupported Add operand\n");
            break;
    }
    
}