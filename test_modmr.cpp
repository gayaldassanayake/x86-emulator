#include <iostream>
#include "modmr.hpp"
using std::cout;
using std::endl;

int main(){
    ModMrDecodeInputArguments* inputs = new ModMrDecodeInputArguments;
    inputs->rm_operand_type = REGISTER_8;
    inputs->reg_operand_type = REGISTER_16;
    inputs->modmr_byte = (uint8_t)0xe6;

    ModMrDecodeOutputArguments* outputs = decodeModeMrByte(inputs);
    
    cout<<outputs->rm_operand<<" "<<outputs->reg_operand<<endl;
}