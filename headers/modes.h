#ifndef MODES
#define MODES

#include "globals.h"

// nao foi implementado padding, ja que as entradas sempre terao uma quantidade de bits multipla de 8

string eletronic_codebook_encrypt(string &plain_text, bitset<10> &key);
string eletronic_codebook_decrypt(string &cipher_text, bitset<10> &key);

#endif