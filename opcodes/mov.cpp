#include "mov.hpp"

void mov8b(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    // Decode
    ModMrDecodeInputArguments* modrm_inputs = new ModMrDecodeInputArguments({true, false, true, REGISTER_32, REGISTER_32});
    ModMrDecodeOutputArguments* modrm_byte_decoded =  decodeModeMrByte(modrm_inputs, reader, rb, memory);
    printModRm(modrm_byte_decoded);
}
