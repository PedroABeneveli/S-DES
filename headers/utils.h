#ifndef UTILS
#define UTILS

#include "globals.h"

// creates a bit string that follows how the S-DES specifications shows their messages and keys:
// LSBit is the leftmost bit
// MSBit is the rightmost bit
string show_data(bitset<8> &data);
string show_data(bitset<10> &data);

#endif