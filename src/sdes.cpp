#include "sdes.h"
#include "bit_ops.h"
#include "utils.h"

bitset<4> F_mapping(bitset<4> &half, bitset<8> &key, bool print) {
    bitset<8> expanded = e_p(half);
    bitset<4> L, R, concat;
    bitset<2> s0_ret, s1_ret;

    if (print) {
        cout << "\t\tMetade expandida = " << show_data(expanded) << "\n";
    }

    expanded = expanded ^ key;
    L[0] = expanded[0];
    L[1] = expanded[1];
    L[2] = expanded[2];
    L[3] = expanded[3];
    R[0] = expanded[4];
    R[1] = expanded[5];
    R[2] = expanded[6];
    R[3] = expanded[7];

    if (print) cout << "\t\tMetade expandida XOR " << show_data(key) << " (subchave) = " << show_data(expanded) << "\n";

    s0_ret = S0(L);
    s1_ret = S1(R);

    // para deixar a concatenacao do jeito que a especificacao pede
    concat[3] = s1_ret[0];
    concat[2] = s1_ret[1];
    concat[1] = s0_ret[0];
    concat[0] = s0_ret[1];

    if (print) {
        cout << "\t\tS0 retornou " << s0_ret << "\n";
        cout << "\t\tS1 retornou " << s1_ret << "\n";
        cout << "\t\tS0 + S1 = " << show_data(concat) << "\n";
    }

    return p4(concat);
}

bitset<8> fk(bitset<8> &text, bitset<8> &key, bool print) {
    bitset<4> L, R, F_result;
    bitset<8> result;

    L[0] = text[0];
    L[1] = text[1];
    L[2] = text[2];
    L[3] = text[3];
    R[0] = text[4];
    R[1] = text[5];
    R[2] = text[6];
    R[3] = text[7];

    if (print) cout << "\tL = " << show_data(L) << ", R = " << show_data(R) << "\n\tF_mapping:\n";

    F_result = F_mapping(R, key, print);

    if (print) cout << "\tResultado F_mapping = " << show_data(F_result) << "\n";

    L = L ^ F_result;

    if (print) cout << "\tNovo L = " << show_data(L) << "\n";

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

pair<bitset<8>, bitset<8>> subkey_generation(bitset<10> key, bool print) {
    bitset<10> key_p10, key_1shift, key_2shift;
    bitset<8> k1, k2;

    key_p10 = p10(key);
    key_1shift = shift(key_p10, 1);
    k1 = p8(key_1shift);
    key_2shift = shift(key_1shift, 2);
    k2 = p8(key_2shift);

    if (print) {
        cout << "Chave:\n    " << show_data(key) << '\n';
        cout << "\nChave apos P10 (K_P10):\n    " << show_data(key_p10) << '\n';
        cout << "\nK_P10 apos o primeiro shift (K_S1):\n    " << show_data(key_1shift) << '\n';
        cout << "\nSubchave 1 (K1):\n    " << show_data(k1) << '\n';
        cout << "\nK_S1 apos passar pelo segundo shift (K_S2):\n    " << show_data(key_2shift) << '\n';
        cout << "\nSubchave 2 (K2):\n    " << show_data(k2) << '\n';
    }

    return make_pair(k1, k2);
}

bitset<8> sdes_encrypt(bitset<8> plain_text, bitset<10> key, bool print) {
    bitset<8> k1, k2, cipher_text;

    tie(k1, k2) = subkey_generation(key);

    if (print) cout << "\nPlain Text:\t\t\t" << show_data(plain_text) << "\n";

    cipher_text = ip(plain_text);

    if (print) cout << "Mensagem apos IP:\t\t" << show_data(cipher_text) << "\nPrimeiro fk:\n";

    cipher_text = fk(cipher_text, k1, print);

    if (print) cout << "Mensagem apos fk com k1:\t" << show_data(cipher_text) << "\n";

    cipher_text = sw(cipher_text);

    if (print) cout << "Mensagem apos o switch:\t\t" << show_data(cipher_text) << "\n";

    cipher_text = fk(cipher_text, k2, print);

    if (print) cout << "Mensagem apos fk com k2:\t" << show_data(cipher_text) << "\n";

    cipher_text = ip_inverse(cipher_text);

    return cipher_text;
}

bitset<8> sdes_decrypt(bitset<8> cipher_text, bitset<10> key, bool print) {
    bitset<8> k1, k2, plain_text;

    tie(k1, k2) = subkey_generation(key);

    if (print) cout << "\nCipher Text:\t\t\t" << show_data(cipher_text) << '\n';

    plain_text = ip(cipher_text);

    if (print) cout << "Mensagem apos IP:\t\t" << show_data(plain_text) << '\n';

    plain_text = fk(plain_text, k2, print);

    if (print) cout << "Mensagem apos fk com k2:\t" << show_data(plain_text) << '\n';

    plain_text = sw(plain_text);

    if (print) cout << "Mensagem apos o switch:\t\t" << show_data(plain_text) << '\n';

    plain_text = fk(plain_text, k1, print);

    if (print) cout << "Mensagem apos fk com k1:\t" << show_data(plain_text) << '\n';

    return ip_inverse(plain_text);
}