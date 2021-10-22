#ifndef OPCODE_DEC_H
#define OPCODE_DEC_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void dec(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif
