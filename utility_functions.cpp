#include "utility_functions.hpp"

string intToHexStr(uint32_t num){
    std::stringstream sstream;
    sstream << std::hex << num;
    string hex_str = "0x" + sstream.str();
    return hex_str;
}

// input format: 0xfffffffff
uint32_t hexToInt(string hex_str){
    std::istringstream converter(hex_str.substr(2));
    uint32_t dec_num;
    converter >> std::hex >> dec_num;
    return dec_num;
}

uint32_t readDispalcement(Reader *reader, uint32_t disp_bytes){
    uint32_t displacement = 0;
    for(uint32_t i=0;i<disp_bytes;i++){
        uint32_t tmp = reader->readNextByte();
        displacement = (tmp<<(8*i)) | displacement;
    }
    return displacement;
}

bool findParity(uint32_t x){
   uint32_t y;
   y = x ^ (x >> 1);
   y = y ^ (y >> 2);
   y = y ^ (y >> 4);
   y = y ^ (y >> 8);
   y = y ^ (y >>16);
   return y & 1;
}

void opcodeExtUnsupportedError(uint8_t opcode) {
    printf("Opcode: %s is noopcode_byte_4t suporting!\n", intToHexStr(opcode).c_str());
}
