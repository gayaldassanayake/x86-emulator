#ifndef UTILITY_FLAG_SET_H
#define UTILITY_FLAG_SET_H

#include <string>
#include <stdlib.h>
#include <iomanip>
#include "register.hpp"

using std::string;

// Set OF, SF, ZF,and PF
void setFlags(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb);

// Set CF, OF, SF, ZF, AF, and PF in Addition
void setFlagsAdd(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb);

// Set CF, OF, SF, ZF, AF, and PF in Substraction
void setFlagsSub(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb);

#endif
