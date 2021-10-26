#include "sib.hpp"
#include "utility_functions.hpp"

string register_array[] = { "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI" };

SibDecodeOutputArguments* decodeSIBByte(SibDecodeInputArguments* inputs, Reader *reader, RegisterBank *rb){
    
    SibDecodeOutputArguments *output = new SibDecodeOutputArguments;
    output->effective_addr = 0;
    output->decoded_print_string = "";

    uint32_t mod = (uint32_t)((inputs->modrm_byte & ((uint8_t)3<<6))>>6);

    uint8_t sib_byte = reader->readNextByte();

    uint32_t scale = (uint32_t)((sib_byte & ((uint8_t)3<<6))>>6);
    uint32_t index = (uint32_t)((sib_byte & ((uint8_t)7<<3))>>3);
    uint32_t base = (uint32_t)(sib_byte & ((uint8_t)7));

    string scale_register = register_array[index];
    string base_register = register_array[base];

    if(index == 4){
        scale_register = "none";
    }
    string decoded_print_string_op1 = "";

    // Decode scale index
    if(index == 4){
            // ignore
    }
    else{
        output->effective_addr = rb->getRegister(scale_register) * (1 << scale);
        decoded_print_string_op1 = "%"+scale_register;
    }
    
    // Add base register
    if (base == 5){ // special case [*]
        if(mod == 0){
            uint32_t displacement = readDispalcement(reader, 4);
            output->effective_addr += displacement; 
            output->decoded_print_string = "("+intToHexStr(displacement)+"("+decoded_print_string_op1+"))";
        }
        else if(mod == 1){
            uint32_t displacement = readDispalcement(reader, 1);
            output->effective_addr += displacement;
            output->effective_addr += rb->getRegister("EBP");
            output->decoded_print_string = "("+intToHexStr(displacement) + "(%EBP,"+decoded_print_string_op1+"))";
        }
        else if(mod == 2){
            uint32_t displacement = readDispalcement(reader, 4);
            output->effective_addr += displacement;
            output->effective_addr += rb->getRegister("EBP");
            output->decoded_print_string = "("+intToHexStr(displacement) + "(%EBP,"+decoded_print_string_op1+"))";
        }
    }
    else{
        output->effective_addr += rb->getRegister(base_register);
        output->decoded_print_string = "(%"+base_register+","+decoded_print_string_op1+ "," +std::to_string(1<<scale)+")";
    }

    return output;
}