#include <iostream>
#include "modmr.hpp"
using std::cout;
using std::endl;

int main(){
    ModMrDecodeInputArguments* inputs = new ModMrDecodeInputArguments;
    inputs->first_operand_type = REGISTER_8;
    inputs->second_operand_type = REGISTER_16;
    inputs->modmr_byte = 0xe6;

    ModMrDecodeOutputArguments* outputs = decodeModeMrByte(inputs);
    
    cout<<outputs->first_operand<<" "<<outputs->second_operand<<endl;
}