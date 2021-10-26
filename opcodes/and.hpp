#ifndef OPCODE_AND_H
#define OPCODE_AND_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void and_(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif
