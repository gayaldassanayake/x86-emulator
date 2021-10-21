#ifndef OPCODE_INC_H
#define OPCODE_INC_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void inc(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif
