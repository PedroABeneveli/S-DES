#ifndef MODES
#define MODES

#include "globals.h"

// nao foi implementado padding, ja que as entradas sempre terao uma quantidade de bits multipla de 8

string eletronic_codebook_encrypt(string &plain_text, bitset<10> &key, bool print=false);
string eletronic_codebook_decrypt(string &cipher_text, bitset<10> &key, bool print=false);

string cipher_block_chaining_encrypt(string &plain_text, bitset<10> &key, bitset<8> init_vector, bool print=false);
string cipher_block_chaining_decrypt(string &cipher_text, bitset<10> &key, bitset<8> init_vector, bool print=false);

#endif