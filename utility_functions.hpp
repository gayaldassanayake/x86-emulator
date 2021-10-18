#ifndef UTILITY_FUNC_H
#define UTILITY_FUNC_H

#include <string>
#include <stdlib.h>
#include <sstream>
#include "reader.hpp"

using std::string;

string intToHexStr(uint32_t num);

uint32_t readDispalcement(Reader *reader, uint32_t disp_bytes);

#endif