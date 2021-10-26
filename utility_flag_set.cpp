#include "utility_flag_set.hpp"

int readIthBit(uint32_t num, int bit){
    return num & ((uint32_t)1 << bit);
}

// Set OF, SF, ZF,and PF
void setFlags(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb){

    // OF
    // sign-bit-off operands + sign-bit-on result -> OF gets ‘1’
    if((readIthBit(operand1, msb) == 0 && readIthBit(operand2, msb) == 0) && readIthBit(result, msb) == 1){
        rb->setFlag("OF", 1);
    }
    // sign-bit-on operands + sign-bit-off result -> OF gets ‘1’
    else if((readIthBit(operand1, msb) == 1 && readIthBit(operand2, msb) == 1) && readIthBit(result, msb) == 0){
        rb->setFlag("OF", 1);
    }
    else{
        rb->setFlag("OF", 0);
    }

    // ZF
    // set if a result is zero; cleared otherwise
    if(result == 0){
        rb->setFlag("ZF", 1);
    }
    else{
        rb->setFlag("ZF", 0);
    }

    // SF
    // set if a result is negative
    if(readIthBit(result, msb) == 1){
        rb->setFlag("SF", 1);
    }
    else{
        rb->setFlag("SF", 0);
    }

    // PF
    if(findParity(result)){
        rb->setFlag("PF", 1);
    }
    else{
        rb->setFlag("PF", 0);
    }

}

// Set CF, OF, SF, ZF, AF, and PF
void setFlagsAdd(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb){

    // CF
    unsigned long long op1 = (unsigned long long)operand1;
    unsigned long long op2 = (unsigned long long)operand2;
    unsigned long long res = op1 + op2;

    res = res & ~(((unsigned long long)1 << (msb + 1)) - 1);
    if(res){
        rb->setFlag("CF", 1);
    }
    else{
        rb->setFlag("CF", 0);
    }
    
    // AF
    // set if borrow from a high nibble to low nibble

    uint32_t op1_low_nible = operand1 & (uint32_t)15;
    uint32_t op2_low_nible = operand2 & (uint32_t)15;
    uint32_t tmp = op1_low_nible + op2_low_nible;
    tmp = tmp & (uint32_t)15;

    if(tmp){
        rb->setFlag("AF", 1);
    }
    else{
        rb->setFlag("AF", 0);
    }

    // Set OF, SF, ZF,and PF
    setFlags( operand1, operand2, result, msb, rb);

}

// Set CF, OF, SF, ZF, AF, and PF
void setFlagsSub(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb){

    // CF
    if(operand1 < operand2){
        rb->setFlag("CF", 1);
    }
    else{
        rb->setFlag("CF", 0);
    }

    // AF
    // set if borrow from a high nibble to low nibble
    if((operand1 & (uint32_t)15) < (operand2 & (uint32_t)15)){
        rb->setFlag("AF", 1);
    }
    else{
        rb->setFlag("AF", 0);
    }

    // Set OF, SF, ZF,and PF
    setFlags( operand1, operand2, result, msb, rb);
}

// Set CF, OF, SF, ZF, and PF
void setFlagsAnd(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb){

    // CF
    rb->setFlag("CF", 0);
    
    // Set OF, SF, ZF, and PF
    setFlags( operand1, operand2, result, msb, rb);
}

// Set CF, OF, SF, ZF, and PF
void setFlagsOr(uint32_t operand1, uint32_t operand2, uint32_t result, int msb, RegisterBank *rb){

    // CF
    rb->setFlag("CF", 0);
    
    // Set OF, SF, ZF, and PF
    setFlags( operand1, operand2, result, msb, rb);
}

// Set AF, OF, SF, ZF, and PF
void setFlagsDec(uint32_t operand1, uint32_t result, int msb, RegisterBank *rb){

    // AF
    // set if borrow from a high nibble to low nibble
    if((operand1 & (uint32_t)15) == 0){
        rb->setFlag("AF", 1);
    } else{
        rb->setFlag("AF", 0);
    }
    
    // Set OF, SF, ZF, and PF
    setFlags( operand1, 1, result, msb, rb);
}

// Set AF, OF, SF, ZF, and PF
void setFlagsInc(uint32_t operand1, uint32_t result, int msb, RegisterBank *rb){

    // AF
    // set if borrow from a high nibble to low nibble
    if((operand1 & (uint32_t)15) == 15){
        rb->setFlag("AF", 1);
    } else{
        rb->setFlag("AF", 0);
    }
    
    // Set OF, SF, ZF, and PF
    setFlags( operand1, 1, result, msb, rb);
}
