#ifndef READER_H
#define READER_H

#include <cstdint>
#include <string>
#include <fstream>

using std::string;
    
class Reader{
    private:
        string input_file_path;
        std::ifstream file; 

    public:
        Reader(string file_file_path);
        ~Reader();
        uint8_t readNextByte();
        bool isEOF();
        uint8_t peekNextByte();
};

#endif