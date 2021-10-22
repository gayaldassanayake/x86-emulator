#ifndef OPCODE_SUB_H
#define OPCODE_SUB_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void sub(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif
