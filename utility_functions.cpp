#include "utility_functions.hpp"

string intToHexStr(uint32_t num){
    std::stringstream sstream;
    sstream << std::hex << num;
    string hex_str = "0x" + sstream.str();
    return hex_str;
}

uint32_t readDispalcement(Reader *reader, uint32_t disp_bytes){
    uint32_t displacement = 0;
    for(uint32_t i=0;i<disp_bytes;i++){
        uint32_t tmp = reader->readNextByte();
        // displacement = (displacement<<(8*i)) | tmp;
        displacement = (tmp<<(8*i)) | displacement;
    }
    return displacement;
}