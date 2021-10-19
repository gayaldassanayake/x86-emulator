#include "modmr.hpp"
#include "utility_functions.hpp"
#include <bitset>

string register_array_32_bit[] = { "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI" };
string register_array_16_bit[] = { "AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI" };
string register_array_8_bit[] = { "AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH" };
string register_array_MMX[] = { "MM0", "MM1", "MM2", "MM3", "MM4", "MM5", "MM6", "MM7" };
string register_array_XMM[] = { "XMM0", "XMM1", "XMM2", "XMM3", "XMM4", "XMM5", "XMM6", "XMM7" };

ModMrDecodeOutputArguments* decodeModeMrByte(ModMrDecodeInputArguments* inputs, Reader *reader, RegisterBank *rb, Memory *memory){

    uint8_t modrm_byte = reader->readNextByte();

    uint32_t mod = (uint32_t)((modrm_byte & ((uint8_t)3<<6))>>6);
    uint32_t reg = (uint32_t)((modrm_byte & ((uint8_t)7<<3))>>3);
    uint32_t rm = (uint32_t)(modrm_byte & ((uint8_t)7));

    // std::cout<<"modmr: "<<(uint32_t)modrm_byte<<std::endl;
    // std::cout<< "mod: "<<mod<<" reg: "<<reg<<" rm: "<<rm<<std::endl;
    // std::cout<<"rm op type: "<<inputs->rm_operand_register_type<<std::endl;
    // std::cout<<"reg op type: "<<inputs->reg_operand_register_type<<std::endl;

    struct ModMrDecodeOutputArguments* output = new ModMrDecodeOutputArguments({false,false,0,0,"","","",""});

    if(inputs->is_first_operand_reg){

        if (inputs->reg_operand_register_type == REGISTER_8){
            output->first_operand_register = register_array_8_bit[reg];
        }
        else if (inputs->reg_operand_register_type == REGISTER_16){
            output->first_operand_register = register_array_16_bit[reg];
        }
        else if (inputs->reg_operand_register_type == REGISTER_32){
            output->first_operand_register = register_array_32_bit[reg];
        }
        else if (inputs->reg_operand_register_type == REGISTER_MM){
            output->first_operand_register = register_array_MMX[reg];
        }
        else{
            output->first_operand_register = register_array_XMM[reg];
        }
        output->is_first_operand_register = true;
        output->decoded_print_string_op1 = "%" + output->first_operand_register;
    }
    else{ // first operand is r/m

        output->first_operand_register = register_array_32_bit[rm];

        if(mod == 0){
            output->is_first_operand_register = false;
            if(rm == 4){ 
                // SIB [--]
                SibDecodeInputArguments *sib_inputs = new SibDecodeInputArguments;
                sib_inputs->modrm_byte = modrm_byte;

                SibDecodeOutputArguments *sib_outputs = decodeSIBByte(sib_inputs, reader, rb);

                output->first_operand_effective_addr = sib_outputs->effective_addr;
                output->decoded_print_string_op1 = "SIB[ " + sib_outputs->decoded_print_string +  "]";
            }
            else if(rm == 5){
                // "disp32";
                uint32_t displacement = readDispalcement(reader, 4);
                output->first_operand_effective_addr = displacement;
                output->decoded_print_string_op1 = intToHexStr(displacement);
            }
            else{
                output->first_operand_effective_addr = rb->getRegister(output->first_operand_register);
                output->decoded_print_string_op1 = "(%" + output->first_operand_register + ")";
            }
        }
        else if(mod == 1){
            output->is_first_operand_register = false;
            if(rm == 4){ 
                // SIB [--]
                SibDecodeInputArguments *sib_inputs = new SibDecodeInputArguments;
                sib_inputs->modrm_byte = modrm_byte;

                SibDecodeOutputArguments *sib_outputs = decodeSIBByte(sib_inputs, reader, rb);

                output->first_operand_effective_addr = sib_outputs->effective_addr;
                output->decoded_print_string_op1 = "SIB[ " + sib_outputs->decoded_print_string +  "]";

                uint32_t displacement = readDispalcement(reader, 1);
                output->first_operand_effective_addr += displacement;
                output->decoded_print_string_op1 += " " + intToHexStr(displacement);
            }
            else{
                uint32_t displacement = readDispalcement(reader, 1);
                output->first_operand_effective_addr = rb->getRegister(output->first_operand_register) + displacement;
                output->decoded_print_string_op1 = intToHexStr(displacement) + "(%" + output->first_operand_register + ")";
            }
        }
        else if(mod == 2){
            output->is_first_operand_register = false;
   
            if(rm == 4){
                // SIB [--]
                SibDecodeInputArguments *sib_inputs = new SibDecodeInputArguments;
                sib_inputs->modrm_byte = modrm_byte;

                SibDecodeOutputArguments *sib_outputs = decodeSIBByte(sib_inputs, reader, rb);

                output->first_operand_effective_addr = sib_outputs->effective_addr;
                output->decoded_print_string_op1 = "SIB[ " + sib_outputs->decoded_print_string +  "]";

                uint32_t displacement = readDispalcement(reader, 4);
                output->first_operand_effective_addr += displacement;
                output->decoded_print_string_op1 += " " + intToHexStr(displacement);
            }
            else{
                uint32_t displacement = readDispalcement(reader, 4);
                output->first_operand_effective_addr = rb->getRegister(output->first_operand_register) + displacement;
                output->decoded_print_string_op1 = intToHexStr(displacement) + "(%" + output->first_operand_register + ")";
            }
        }
        else{
            output->is_first_operand_register = true;

            if(inputs->rm_operand_register_type == REGISTER_16){
                output->first_operand_register = register_array_16_bit[rm];
            }
            else if(inputs->rm_operand_register_type == REGISTER_8){
                output->first_operand_register = register_array_8_bit[rm];
            }
            else if(inputs->rm_operand_register_type == REGISTER_MM){
                output->first_operand_register = register_array_MMX[rm];
            }
            else if(inputs->rm_operand_register_type == REGISTER_XMM){
                output->first_operand_register = register_array_XMM[rm];
            }
            else{
                output->first_operand_register = register_array_32_bit[rm];
            }

            output->decoded_print_string_op1 = "%" + output->first_operand_register;
        }
    }

    if(inputs->has_second_operand){

        if(inputs->is_second_operand_reg){

            if (inputs->reg_operand_register_type == REGISTER_8){
                output->second_operand_register = register_array_8_bit[reg];
            }
            else if (inputs->reg_operand_register_type == REGISTER_16){
                output->second_operand_register = register_array_16_bit[reg];
            }
            else if (inputs->reg_operand_register_type == REGISTER_32){
                output->second_operand_register = register_array_32_bit[reg];
            }
            else if (inputs->reg_operand_register_type == REGISTER_MM){
                output->second_operand_register = register_array_MMX[reg];
            }
            else{
                output->second_operand_register = register_array_XMM[reg];
            }
            output->is_second_operand_register = true;
            output->decoded_print_string_op2 = "%" + output->second_operand_register;
        }
        else{ // second operand is a r/m

            output->second_operand_register = register_array_32_bit[rm];

            if(mod == 0){
                output->is_second_operand_register = false;
                if(rm == 4){
                    // SIB [--]
                    SibDecodeInputArguments *sib_inputs = new SibDecodeInputArguments;
                    sib_inputs->modrm_byte = modrm_byte;

                    SibDecodeOutputArguments *sib_outputs = decodeSIBByte(sib_inputs, reader, rb);

                    output->second_operand_effective_addr = sib_outputs->effective_addr;
                    output->decoded_print_string_op2 = "SIB[ " + sib_outputs->decoded_print_string +  "]";
                }
                else if(rm == 5){
                    // "disp32";
                    uint32_t displacement = readDispalcement(reader, 4);
                    output->second_operand_effective_addr = displacement;
                    output->decoded_print_string_op2 = intToHexStr(displacement);
                }
                else{
                    output->second_operand_effective_addr = rb->getRegister(output->second_operand_register);
                    output->decoded_print_string_op2 = "(%" + output->second_operand_register + ")";
                }
            }
            else if(mod == 1){
                output->is_second_operand_register = false;
                
                if(rm == 4){
                    // SIB [--]
                    SibDecodeInputArguments *sib_inputs = new SibDecodeInputArguments;
                    sib_inputs->modrm_byte = modrm_byte;

                    SibDecodeOutputArguments *sib_outputs = decodeSIBByte(sib_inputs, reader, rb);

                    output->second_operand_effective_addr = sib_outputs->effective_addr;
                    output->decoded_print_string_op2 = "SIB[ " + sib_outputs->decoded_print_string +  "]";

                    uint32_t displacement = readDispalcement(reader, 1);
                    output->second_operand_effective_addr += displacement;
                    output->decoded_print_string_op2 += " " + intToHexStr(displacement);
                }
                else{
                    uint32_t displacement = readDispalcement(reader, 1);
                    output->second_operand_effective_addr = rb->getRegister(output->second_operand_register) + displacement;
                    output->decoded_print_string_op2 = intToHexStr(displacement) + "(%" + output->second_operand_register + ")";
                }
            }
            else if(mod == 2){
                output->is_second_operand_register = false;

                if(rm == 4){ 
                    // SIB [--]
                    SibDecodeInputArguments *sib_inputs = new SibDecodeInputArguments;
                    sib_inputs->modrm_byte = modrm_byte;

                    SibDecodeOutputArguments *sib_outputs = decodeSIBByte(sib_inputs, reader, rb);

                    output->second_operand_effective_addr = sib_outputs->effective_addr;
                    output->decoded_print_string_op2 = "SIB[ " + sib_outputs->decoded_print_string +  "]";

                    uint32_t displacement = readDispalcement(reader, 4);
                    output->second_operand_effective_addr += displacement;
                    output->decoded_print_string_op2 += " " + intToHexStr(displacement);
                }
                else{
                    uint32_t displacement = readDispalcement(reader, 4);
                    output->second_operand_effective_addr = rb->getRegister(output->second_operand_register) + displacement;
                    output->decoded_print_string_op2 = intToHexStr(displacement) + "(%" + output->second_operand_register + ")";
                }
            }
            else{
                output->is_second_operand_register = true;

                if(inputs->rm_operand_register_type == REGISTER_16){
                    output->second_operand_register = register_array_16_bit[rm];
                }
                else if(inputs->rm_operand_register_type == REGISTER_8){
                    output->second_operand_register = register_array_8_bit[rm];
                }
                else if(inputs->rm_operand_register_type == REGISTER_MM){
                    output->second_operand_register = register_array_MMX[rm];
                }
                else if(inputs->rm_operand_register_type == REGISTER_XMM){
                    output->second_operand_register = register_array_XMM[rm];
                }
                else{
                    output->second_operand_register = register_array_32_bit[rm];
                }

                output->decoded_print_string_op2 = "%" + output->second_operand_register;
            }
        }
    }

    return output;
}


void printModRm(ModMrDecodeOutputArguments* outputs){

    printf("\nif_1op_reg: %d, is_2op_reg: %d, 1op_eff_addr: %d, 2op_eff_addr: %d\n", 
    outputs->is_first_operand_register,
    outputs->is_second_operand_register,
    outputs->first_operand_effective_addr,
    outputs->second_operand_effective_addr
    );
    // cout << "1op Reg: " << outputs->first_operand_register << endl;
    // cout << "2op Reg: " << outputs->second_operand_register << endl;
    cout << "1op Print str: " << outputs->decoded_print_string_op1 << endl;
    cout << "2op Print str: " << outputs->decoded_print_string_op2 << endl;
}