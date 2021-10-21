#include "opcode_extension.hpp"
#include "utility_functions.hpp"
#include "opcodes/opcodes.hpp"

void mapOpcodeExtendedInstructions(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory) {
    uint8_t modrm_byte;
    if (!reader->isEOF()) {
        modrm_byte = reader->peekNextByte();
        uint32_t reg = (uint32_t)((modrm_byte & ((uint8_t)7<<3))>>3);
        switch(ins_arg->opcode) {
            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
                switch(reg) {
                    case 0:
                        add(ins_arg, reader, rb, memory);
                        break;
                    case 1:
                        or_(ins_arg, reader, rb, memory);
                        break;
                    case 4:
                        and_(ins_arg, reader, rb, memory);
                        break;
                    default:
                        opcodeExtUnsupportedError(ins_arg->opcode);
                        break;
                }
                break;
            case 0xc6:
            case 0xc7:
                switch(reg) {
                    case 0:
                        mov(ins_arg, reader, rb, memory);
                        break;
                    default:
                        opcodeExtUnsupportedError(ins_arg->opcode);
                        break;
                }
                break;
            default:
                opcodeExtUnsupportedError(ins_arg->opcode);
            break;
        }
    } else {
        printf("Incomplete instruction");
    }
}
