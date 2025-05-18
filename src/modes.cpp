#include "modes.h"
#include "sdes.h"
#include "utils.h"

string eletronic_codebook_encrypt(string &plain_text, bitset<10> &key) {
    string block, cipher_text = "";
    bitset<8> text;

    for (int i = 0 ; i < ((int)plain_text.size()) ; i += 8) {
        block = plain_text.substr(i, 8);

        text = text_to_bits(block);
        text = sdes_encrypt(text, key);
        cipher_text += show_data(text);
    }

    return cipher_text;
}

string eletronic_codebook_decrypt(string &cipher_text, bitset<10> &key) {
    string block, plain_text = "";
    bitset<8> text;

    for (int i = 0 ; i < ((int)cipher_text.size()) ; i += 8) {
        block = cipher_text.substr(i, 8);

        text = text_to_bits(block);
        text = sdes_decrypt(text, key);
        plain_text += show_data(text);
    }

    return plain_text;
}

string cipher_block_chaining_encrypt(string &plain_text, bitset<10> &key, bitset<8> init_vector) {
    string block, cipher_text = "";
    bitset<8> text, prev = init_vector;

    for (int i = 0 ; i < ((int)plain_text.size()) ; i += 8) {
        block = plain_text.substr(i, 8);

        text = text_to_bits(block);
        text = text ^ prev;
        text = sdes_encrypt(text, key);
        cipher_text += show_data(text);

        prev = text;
    }

    return cipher_text;
}

string cipher_block_chaining_decrypt(string &cipher_text, bitset<10> &key, bitset<8> init_vector) {
    string block, plain_text = "";
    bitset<8> cipher_block, text, prev = init_vector;

    for (int i = 0 ; i < ((int)cipher_text.size()) ; i += 8) {
        block = cipher_text.substr(i, 8);

        cipher_block = text_to_bits(block);

        text = sdes_decrypt(cipher_block, key);
        text = text ^ prev;

        plain_text += show_data(text);
        prev = cipher_block;
    }

    return plain_text;   
}