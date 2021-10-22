#ifndef OPCODE_PUSH_H
#define OPCODE_PUSH_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void push(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);
void pop(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);
#endif