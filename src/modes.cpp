#include "modes.h"
#include "sdes.h"
#include "utils.h"

string eletronic_codebook_encrypt(string &plain_text, bitset<10> &key, bool print) {
    string block, cipher_text = "";
    bitset<8> text;
    int cnt = 1;

    for (int i = 0 ; i < ((int)plain_text.size()) ; i += 8) {
        block = plain_text.substr(i, 8);

        text = text_to_bits(block);
        text = sdes_encrypt(text, key);

        if (print) {
            cout << "\nBloco " << cnt++ << ":\n";
            cout << "\tAntes de encriptar:  " << block << "\n";
            cout << "\tDepois de encriptar: " << show_data(text) << "\n";
        }

        cipher_text += show_data(text);
    }

    return cipher_text;
}

string eletronic_codebook_decrypt(string &cipher_text, bitset<10> &key, bool print) {
    string block, plain_text = "";
    bitset<8> text;
    int cnt = 1;

    for (int i = 0 ; i < ((int)cipher_text.size()) ; i += 8) {
        block = cipher_text.substr(i, 8);

        text = text_to_bits(block);
        text = sdes_decrypt(text, key);

        if (print) {
            cout << "\nBloco " << cnt++ << ":\n";
            cout << "\tAntes de decriptar:  " << block << "\n";
            cout << "\tDepois de decriptar: " << show_data(text) << "\n";
        }

        plain_text += show_data(text);
    }

    return plain_text;
}

string cipher_block_chaining_encrypt(string &plain_text, bitset<10> &key, bitset<8> init_vector, bool print) {
    string block, cipher_text = "";
    bitset<8> text, prev = init_vector;
    int cnt = 1;

    // tentei fazer uma tabela
    if (print) {
        cout << "\n|---------|----------------|------------------------------|------------------|----------------|\n";
        cout << "|  Bloco  | Bloco em Claro | IV ou bloco cifrado anterior | Resultado do XOR | Bloco  Cifrado |\n";
        cout << "|---------|----------------|------------------------------|------------------|----------------|\n";
    }

    for (int i = 0 ; i < ((int)plain_text.size()) ; i += 8) {
        block = plain_text.substr(i, 8);

        text = text_to_bits(block);
        text = text ^ prev;

        if (print) {
            int lg10 = floor(log10(cnt));
            cout << "|" << cnt++ << string(9-(lg10+1), ' ') << "|    " << block << "    |           " << show_data(prev) << "           |     " << show_data(text) << "     |";
        }

        text = sdes_encrypt(text, key);

        if (print) {
            cout << "    " << show_data(text) << "    |\n";
            cout << "|---------|----------------|------------------------------|------------------|----------------|\n";
        }

        cipher_text += show_data(text);

        prev = text;
    }

    return cipher_text;
}

string cipher_block_chaining_decrypt(string &cipher_text, bitset<10> &key, bitset<8> init_vector, bool print) {
    string block, plain_text = "";
    bitset<8> cipher_block, text, prev = init_vector;
    int cnt = 1;

    // 30 pro ult antes e depois do text

    if (print) {
        cout << "\n|---------|----------------|--------------------------------|------------------------------|--------------------------------------------------------------------|\n";
        cout << "|  Bloco  | Bloco  Cifrado | Bloco Cifrado Descriptografado | IV ou bloco cifrado anterior | Texto em Claro (XOR do Bloco Descriptografado e do Bloco Anterior) |\n";
        cout << "|---------|----------------|--------------------------------|------------------------------|--------------------------------------------------------------------|\n";
    }

    for (int i = 0 ; i < ((int)cipher_text.size()) ; i += 8) {
        block = cipher_text.substr(i, 8);

        cipher_block = text_to_bits(block);

        text = sdes_decrypt(cipher_block, key);

        if (print) {
            int lg10 = floor(log10(cnt));
            cout << "|" << cnt++ << string(9-(lg10+1), ' ') << "|";
            cout << "    " << block << "    |";
            cout << string(12, ' ') << show_data(text) << string(12, ' ') << "|";
            cout << string(11, ' ') << show_data(prev) << string(11, ' ') << "|";
        }

        text = text ^ prev;

        if (print) {
            cout << string(30, ' ') << show_data(text) << string(30, ' ') << "|\n";
            cout << "|---------|----------------|--------------------------------|------------------------------|--------------------------------------------------------------------|\n";
        }

        plain_text += show_data(text);
        prev = cipher_block;
    }

    return plain_text;   
}