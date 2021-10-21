#ifndef UTILITY_FUNC_H
#define UTILITY_FUNC_H

#include <string>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include "reader.hpp"

using std::string;

string intToHexStr(uint32_t num);

uint32_t hexToInt(string hex_str);

uint32_t readDispalcement(Reader *reader, uint32_t disp_bytes);

bool findParity(uint32_t x);

#endif
