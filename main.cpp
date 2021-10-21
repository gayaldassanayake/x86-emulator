#include <iostream>
#include <set>
#include "opcode_extension.hpp"
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

    std::set<uint32_t, std::greater<uint32_t> > op_add = { 0x00, 0x01, 0x02, 0x03, 0x04 };
    std::set<uint32_t, std::greater<uint32_t> > op_mov = { 0x88, 0x8a, 0x8b, 0x89 };
    std::set<uint32_t, std::greater<uint32_t> > op_and = { 0x20, 0x21, 0x22, 0x23, 0x24, 0x25 };
    std::set<uint32_t, std::greater<uint32_t> > op_or = { 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D };
    std::set<uint32_t, std::greater<uint32_t> > op_push = { 
            0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x0e, 0x16, 0x1e, 0x06, 0x68 
        };
    std::set<uint32_t, std::greater<uint32_t> > op_pop = {
            0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x1f, 0x07, 0x17
        };
    std::set<uint32_t, std::greater<uint32_t> > opcode_exten = { 0x80, 0x81, 0x82, 0x83, 0xc6, 0xc7 };


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
        } else if(op_mov.count(arguments->opcode)) {
            mov(arguments, &reader, &rb, &memory);
        } else if(op_and.count(arguments->opcode)) {
            and_(arguments, &reader, &rb, &memory);
        } else if(op_or.count(arguments->opcode)) {
            or_(arguments, &reader, &rb, &memory);
        }else if(op_push.count(arguments->opcode)){
            push(arguments, &reader, &rb, &memory);
        } else if(opcode_exten.count(arguments->opcode)) {
            mapOpcodeExtendedInstructions(arguments, &reader, &rb, &memory);
        } 
        else if(op_pop.count(arguments->opcode)){
            pop(arguments, &reader, &rb, &memory);
        }
        else{
            printf("Opcode: %s is noopcode_byte_4t suporting!\n", intToHexStr(arguments->opcode).c_str());
        }  
        // break; 
    }
    printf("\nFinished Emulating...\n");
}
