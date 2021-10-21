#include "inc.hpp"
#include "../utility_functions.hpp"

void inc(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory){
    switch (ins_arg->opcode){
        case 0x0:
            // add00(ins_arg, reader, rb, memory);
            break;
        default:
            printf("Unsupported Add operand\n");
            break;
    }
}
