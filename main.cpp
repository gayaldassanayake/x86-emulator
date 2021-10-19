#include <iostream>
#include <set>
#include "modmr.hpp"
#include "reader.hpp"
#include "utils.hpp"
#include "memory.hpp"
#include "register.hpp"
#include "utility_functions.hpp"

#include "opcodes/opcodes.hpp"

using std::cout;
using std::endl;
using std::find;

int main(int argc, char *argv[]){

    // cout<<std::hex;

    Reader reader(argv[1]);
    Memory memory(1000);
    // RegisterBank rb();
    RegisterBank rb = RegisterBank();

    set<uint32_t, greater<uint32_t> > op_add = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x81, 0x83 };

    // while(!reader.isEOF()){
    //     uint8_t tmp=reader.readNextByte();
    //     cout<<(uint32_t)tmp<<endl;
    // }

    uint8_t next_byte;

    printf("\nEmulation started...\n\n");

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
        if(op_add.count(arguments->opcode)){
            add(arguments, &reader, &rb, &memory);
        }
        else{
            printf("Opcode: %s is not suporting!\n", intToHexStr(arguments->opcode).c_str());
        }
        
        printf("\nFinished Emulating...\n");
        break; 
    }

}