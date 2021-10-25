#ifndef OPCODE_XCHG_H
#define OPCODE_XCHG_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void xchg(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif
