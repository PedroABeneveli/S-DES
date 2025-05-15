#include "../headers/modes.h"
#include "../headers/sdes.h"
#include "../headers/utils.h"

string eletronic_codebook_encrypt(string &plain_text, bitset<10> &key) {
    string block, cipher_text = "";
    bitset<8> text;

    for (int i = 0 ; i < ((int)plain_text.size()) ; i += 8) {
        block = plain_text.substr(i, 8);

        // em cada bloco, o bit mais na esquerda eh o bit menos significativo
        // logo inverto a string para usar o construtor padrao do bitset
        reverse(block.begin(), block.end());

        text = bitset<8>(block);
        text = encrypt(text, key);
        cipher_text += show_data(text);
    }

    return cipher_text;
}

string eletronic_codebook_decrypt(string &cipher_text, bitset<10> &key) {
    string block, plain_text = "";
    bitset<8> text;

    for (int i = 0 ; i < ((int)cipher_text.size()) ; i += 8) {
        block = cipher_text.substr(i, 8);

        reverse(block.begin(), block.end());

        text = bitset<8>(block);
        text = decrypt(text, key);
        plain_text += show_data(text);
    }

    return plain_text;
}