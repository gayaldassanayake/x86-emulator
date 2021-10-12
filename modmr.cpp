#include "modmr.hpp"
#include <bitset>

string register_array_32_bit[] = { "EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI" };
string register_array_16_bit[] = { "AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI" };
string register_array_8_bit[] = { "AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH" };
string register_array_MMX[] = { "MM0", "MM1", "MM2", "MM3", "MM4", "MM5", "MM6", "MM7" };
string register_array_XMM[] = { "XMM0", "XMM1", "XMM2", "XMM3", "XMM4", "XMM5", "XMM6", "XMM7" };

ModMrDecodeOutputArguments* decodeModeMrByte(ModMrDecodeInputArguments* inputs){
    uint32_t mod = (uint32_t)((inputs->modmr_byte & ((uint8_t)3<<6))>>6);
    uint32_t reg = (uint32_t)((inputs->modmr_byte & ((uint8_t)7<<3))>>3);
    uint32_t rm = (uint32_t)(inputs->modmr_byte & ((uint8_t)7));

    // std::cout<<"modmrbits: "<<std::bitset<8>((uint32_t)3<<6)<<std::endl;
    std::cout<<"modmr: "<<(uint32_t)inputs->modmr_byte<<std::endl;
    std::cout<< "mod: "<<mod<<" reg: "<<reg<<" rm: "<<rm<<std::endl;
    std::cout<<"rm op type: "<<inputs->rm_operand_type<<std::endl;
    std::cout<<"reg op type: "<<inputs->reg_operand_type<<std::endl;

    struct ModMrDecodeOutputArguments* output = new ModMrDecodeOutputArguments;

    output->rm_operand = register_array_32_bit[rm];
    output->is_SIB_available = false;
    output->is_rm_op_memory_location = true;
    output->displacement = 0;

    if(mod == 0){
        if(rm == 4){
            output->rm_operand = "[--][--]";
            output->is_SIB_available = true;
        }
        else if(rm == 5){
            output->rm_operand = "disp32";
        }
    }
    else if(mod == 1){
        output->displacement = 8;
        if(rm == 4){
            output->rm_operand = "[--][--]";
            output->is_SIB_available = true;
        }
    }
    else if(mod == 2){
        output->displacement = 32;
        if(rm == 4){
            output->rm_operand = "[--][--]";
            output->is_SIB_available = true;
        }
    }
    else{
        output->is_rm_op_memory_location = false;

        if(inputs->rm_operand_type == REGISTER_16){
            output->rm_operand = register_array_16_bit[rm];
        }
        else if(inputs->rm_operand_type == REGISTER_8){
            output->rm_operand = register_array_8_bit[rm];
        }
        else if(inputs->rm_operand_type == REGISTER_MM){
            output->rm_operand = register_array_MMX[rm];
        }
        else if(inputs->rm_operand_type == REGISTER_XMM){
            output->rm_operand = register_array_XMM[rm];
        }
    }

    if (inputs->reg_operand_type == REGISTER_8){
        output->reg_operand = register_array_8_bit[reg];
    }
    else if (inputs->reg_operand_type == REGISTER_16){
        output->reg_operand = register_array_16_bit[reg];
    }
    else if (inputs->reg_operand_type == REGISTER_32){
        output->reg_operand = register_array_32_bit[reg];
    }
    else if (inputs->reg_operand_type == REGISTER_MM){
        output->reg_operand = register_array_MMX[reg];
    }
    else{
        output->reg_operand = register_array_XMM[reg];
    }

    return output;
}


void printModRm(ModMrDecodeOutputArguments* outputs){

    printf("rm: %s\nReg: %s\ndisplacement: %d\nisSib: %d\nis_rm_mem_loc: %d\n", 
    outputs->rm_operand.c_str(), 
    outputs->reg_operand.c_str(), 
    outputs->displacement, 
    outputs->is_SIB_available, 
    outputs->is_rm_op_memory_location);

}