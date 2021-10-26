#ifndef UTILITY_FUNC_H
#define UTILITY_FUNC_H

#include <string>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <bitset>
#include "reader.hpp"

using std::string;
using std::ostream;

string intToHexStr(uint32_t num);

string intToBinFmtStr(uint32_t num, int width, int space_gap = 32);

string intToHexFmtStr(uint32_t num, int width, int space_gap = 8);

uint32_t hexToInt(string hex_str);

uint32_t readDispalcement(Reader *reader, uint32_t disp_bytes);

bool findParity(uint32_t x);

void opcodeExtUnsupportedError(uint8_t opcode);

void print(ostream &os1, ostream &os2, const string &str);

#endif
