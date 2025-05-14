#ifndef SDES
#define SDES

#include "globals.h"

bitset<4> F_mapping(bitset<4> &half, bitset<8> &key);

bitset<8> fk(bitset<8> &text, bitset<8> &key);

#endif