#include "../headers/sdes.h"
#include "../headers/bit_ops.h"
#include "../headers/utils.h"

bitset<4> F_mapping(bitset<4> &half, bitset<8> &key) {
    bitset<8> expanded = e_p(half);
    bitset<4> L, R, concat;
    bitset<2> s0_ret, s1_ret;

    expanded = expanded ^ key;
    L[0] = expanded[0];
    L[1] = expanded[1];
    L[2] = expanded[2];
    L[3] = expanded[3];
    R[0] = expanded[4];
    R[1] = expanded[5];
    R[2] = expanded[6];
    R[3] = expanded[7];

    s0_ret = S0(L);
    s1_ret = S1(R);

    concat[3] = s1_ret[0];
    concat[2] = s1_ret[1];
    concat[1] = s0_ret[0];
    concat[0] = s0_ret[1];

    cout << concat << '\n';

    return p4(concat);
}

bitset<8> fk(bitset<8> &text, bitset<8> &key) {
    bitset<4> L, R;
    bitset<8> result;

    L[0] = text[0];
    L[1] = text[1];
    L[2] = text[2];
    L[3] = text[3];
    R[0] = text[4];
    R[1] = text[5];
    R[2] = text[6];
    R[3] = text[7];

    L = L ^ F_mapping(R, key);

    result[0] = L[0];
    result[1] = L[1];
    result[2] = L[2];
    result[3] = L[3];
    result[4] = R[0];
    result[5] = R[1];
    result[6] = R[2];
    result[7] = R[3];

    return result;
}

pair<bitset<8>, bitset<8>> subkey_generation(bitset<10> key) {
    bitset<10> key_p10, key_1shift, key_2shift;
    bitset<8> k1, k2;

    key_p10 = p10(key);
    key_1shift = shift(key_p10, 1);
    k1 = p8(key_1shift);
    key_2shift = shift(key_1shift, 2);
    k2 = p8(key_2shift);

    cout << "Chave: " << show_data(key) << '\n';
    cout << "Chave apos P10 (K_P10): " << show_data(key_p10) << '\n';
    cout << "K_P10 apos o primeiro shift (K_S1): " << show_data(key_1shift) << '\n';
    cout << "Subchave 1 (K1): " << show_data(k1) << '\n';
    cout << "K_S1 apos passar pelo segundo shift (K_S2): " << show_data(key_2shift) << '\n';
    cout << "Subchave 2 (K2): " << show_data(k2) << '\n';

    return make_pair(k1, k2);
}

bitset<8> encrypt(bitset<8> plain_text, bitset<10> key) {
    bitset<8> k1, k2, cipher_text;

    tie(k1, k2) = subkey_generation(key);

    cout << "Plain Text: " << show_data(plain_text) << '\n';

    cipher_text = ip(plain_text);

    cout << "Mensagem apos IP: " << show_data(cipher_text) << '\n';

    cipher_text = fk(cipher_text, k1);

    cout << "Mensagem apos a primeira fk: " << show_data(cipher_text) << '\n';

    cipher_text = sw(cipher_text);

    cout << "Mensagem apos o primeiro switch: " << show_data(cipher_text) << '\n';

    cipher_text = fk(cipher_text, k2);

    cout << "Mensagem apos a segunda fk: " << show_data(cipher_text) << '\n';

    cipher_text = ip_inverse(cipher_text);

    return cipher_text;
}