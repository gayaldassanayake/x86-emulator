#include "utility_functions.hpp"

string intToBinFmtStr(uint32_t num, int width, int space_gap){
    std::bitset<8> bin(num);
    int zeros = width - bin.to_string().size();
    int spaces = space_gap - width;
    string prefix="";
    for(int i=0;i<spaces;i++){
        prefix += " ";
    }
    prefix += "0b";
    for(int i=0;i<zeros;i++){
        prefix += "0";
    }
    string bin_str = prefix + bin.to_string();
    return bin_str;
}

string intToHexFmtStr(uint32_t num, int width, int space_gap){
    std::stringstream sstream;
    sstream << std::hex << num;
    int zeros = width/4.0 - sstream.str().size();
    int spaces = space_gap - width/4.0;
    string prefix="";
    for(int i=0;i<spaces;i++){
        prefix += " ";
    }
    prefix += "0x";
    for(int i=0;i<zeros;i++){
        prefix += "0";
    }
    string hex_str = prefix + sstream.str();
    return hex_str;
}

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

// source: https://stackoverflow.com/questions/17350906/computing-the-parity
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

void print(ostream &os1, ostream &os2, const string &str) {
    os1 << str;
    os2 << str;
}
