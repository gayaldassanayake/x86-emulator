#include <iostream>
#include "modmr.hpp"
#include "reader.hpp"
#include "utils.hpp"
using std::cout;
using std::endl;

int main(){

    cout<<std::hex;

    Reader reader("sample1.txt");

    // while(!reader.isEOF()){
    //     uint8_t tmp=reader.readNextByte();
    //     cout<<(uint32_t)tmp<<endl;
    // }

    uint8_t next_byte;

    while(!reader.isEOF()){       
        next_byte = reader.readNextByte();
        struct InstructionArguments *arguments = new InstructionArguments;

        if(next_byte == 0x0f){
            arguments->opcode_byte_1 = next_byte;
            next_byte = reader.readNextByte();
            arguments->opcode_byte_2 = next_byte;

            if(next_byte == 0x38 || next_byte == 0x3a){
                next_byte = reader.readNextByte();
                arguments->opcode_byte_3 = next_byte;
                arguments->opcode_type = 3;
                arguments->opcode = next_byte;
            }
            else{
                arguments->opcode_type = 2;
                arguments->opcode = next_byte;
            }
            arguments->opcode = next_byte;
        }
        else if(next_byte == 0x66 || next_byte == 0xf2 || next_byte == 0xf3){
            arguments->opcode_byte_1 = next_byte;
            arguments->has_leg_prefix = true;

            next_byte = reader.readNextByte();
            arguments->opcode_byte_2 = next_byte;

            next_byte = reader.readNextByte();
            arguments->opcode_byte_3 = next_byte;

            if(next_byte == 0x38 || next_byte == 0x3a){
                arguments->opcode_type = 3;
                next_byte = reader.readNextByte();
                arguments->opcode_byte_4 = next_byte;
                arguments->opcode = next_byte;
            }
            else{
                arguments->opcode_type = 2;
                arguments->opcode = next_byte;
            }
            arguments->opcode = next_byte;
        }
        else{
            arguments->opcode_byte_1 = next_byte;
            arguments->opcode_type = 1;
            arguments->opcode = next_byte;
        }
        // call the respective handler
    }

}