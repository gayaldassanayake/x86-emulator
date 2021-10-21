#ifndef OPEX_H
#define OPEX_H

#include "opcodes/opcodes.hpp"
#include "reader.hpp"
#include "register.hpp"
#include "memory.hpp"

void mapOpcodeExtendedInstructions(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif