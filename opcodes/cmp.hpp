#ifndef OPCODE_CMP_H
#define OPCODE_CMP_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void cmp(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif