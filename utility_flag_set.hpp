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

// OF, CF, SF, ZF, PF in Logical AND
void setFlagsAnd(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb);

// Set CF, OF, SF, ZF, and PF in Logical OR
void setFlagsOr(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb);

// OF, SF, ZF, AF, and PF in Dec
void setFlagsDec(uint32_t operand1, uint32_t result, int msb, RegisterBank *rb);

// Set AF, OF, SF, ZF, and PF in Inc
void setFlagsInc(uint32_t operand1, uint32_t result, int msb, RegisterBank *rb);

#endif
