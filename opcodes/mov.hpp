#ifndef OPCODE_MOV_H
#define OPCODE_MOV_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void mov8b(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif
