#ifndef OPCODE_ADD_H
#define OPCODE_ADD_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void add(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif