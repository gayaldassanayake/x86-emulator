#ifndef OPCODE_OR_H
#define OPCODE_OR_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void or_(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif
