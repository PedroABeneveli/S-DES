#ifndef SDES
#define SDES

#include "globals.h"

bitset<4> F_mapping(bitset<4> &half, bitset<8> &key);

bitset<8> fk(bitset<8> &text, bitset<8> &key);

pair<bitset<8>, bitset<8>> subkey_generation(bitset<10> key, bool print=false);

bitset<8> sdes_encrypt(bitset<8> plain_text, bitset<10> key, bool print=false);

bitset<8> sdes_decrypt(bitset<8> cipher_text, bitset<10> key, bool print=false);

#endif