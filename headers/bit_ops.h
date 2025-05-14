#ifndef BITOPS
#define BITOPS

#include "globals.h"

// the S-DES document seems to represent the numbers with the LS-Bit on the left, so a left shift for the would be a right shift on C++, for example

// initial permutation on the received key
bitset<10> p10(bitset<10> &key);

// permutes and selects 8 bits from the current key to generate a subkey
bitset<8> p8(bitset<10> &key);

// circular shift on each of the halves of the key
bitset<10> shift(bitset<10> &key, int num);

// initial permutation
bitset<8> ip(bitset<8> &data);

// (initial permutation)^-1
bitset<8> ip_inverse(bitset<8> &data);

// operations needed for F mapping

bitset<8> e_p(bitset<4> &num);
bitset<2> S0(bitset<4> &num);
bitset<2> S1(bitset<4> &num);
bitset<4> p4(bitset<4> &num);

#endif