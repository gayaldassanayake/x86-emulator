#ifndef OPCODE_TEST_H
#define OPCODE_TEST_H

#include <cstdint>
#include <string>
#include "../memory.hpp"
#include "../modmr.hpp"
#include "../reader.hpp"
#include "../register.hpp"
#include "../utils.hpp"

void test(InstructionArguments *ins_arg, Reader *reader, RegisterBank *rb, Memory *memory);

#endif