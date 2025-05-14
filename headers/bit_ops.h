#ifndef BITOPS
#define BITOPS

#include "globals.h"

// initial permutation on the received key
bitset<10> p10(bitset<10> &key);

// permutes and selects 8 bits from the current key to generate a subkey
bitset<8> p8(bitset<10> &key);

// circular shift on each of the halves of the key
bitset<10> shift(bitset<10> &key);

#endif