#include "add.hpp"

void add03(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    std::cout<<"working"<<std::endl;
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments;
    uint8_t modrm_byte = reader->readNextByte();
    modrm_inputs->modmr_byte = modrm_byte;
    modrm_inputs->rm_operand_type = REGISTER_32;
    modrm_inputs->reg_operand_type = REGISTER_32;

    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs);
    printModRm(modrm_byte_decoded);

    printf("add %s %s\n",modrm_byte_decoded->reg_operand.c_str(), modrm_byte_decoded->rm_operand.c_str());
}

// void add03(InstructionArguments *ins_arg, Reader *reader, Memory memory){
//     // ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments;
//     // uint8_t modrm_byte = reader.readNextByte();
//     // modrm_inputs->modmr_byte = modrm_byte;
//     // modrm_inputs->rm_operand_type = REGISTER_32;
//     // modrm_inputs->reg_operand_type = REGISTER_32;

//     // ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs);
//     // printModRm(modrm_byte_decoded);

// }