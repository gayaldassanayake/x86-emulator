#include "reader.hpp"

Reader::Reader(string input_file_path){
    this->input_file_path = input_file_path;
    this->file.open(input_file_path); 
    file >> std::hex;
}

Reader::~Reader(){
    file.close();
}

uint8_t Reader::readNextByte(){
    uint16_t nextByte;
    while(file>>nextByte){
        return (uint8_t)nextByte;
    }
    return 0;
}

bool Reader::isEOF(){
    return(file.peek() == EOF);
}

uint8_t Reader::peekNextByte(){
    int place = file.tellg();
    uint8_t nextByte = readNextByte();
    file.seekg(place);
    return nextByte;
}
