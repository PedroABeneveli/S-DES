#include "../headers/bit_ops.h"

bitset<10> p10(bitset<10> &key) {
    bitset<10> permutation;

    permutation[0] = key[2];
    permutation[1] = key[4];
    permutation[2] = key[1];
    permutation[3] = key[6];
    permutation[4] = key[3];
    permutation[5] = key[9];
    permutation[6] = key[0];
    permutation[7] = key[8];
    permutation[8] = key[7];
    permutation[9] = key[5];

    return permutation;
} 

bitset<8> p8(bitset<10> &key) {
    bitset<8> subkey;

    subkey[0] = key[5];
    subkey[1] = key[2];
    subkey[2] = key[6];
    subkey[3] = key[3];
    subkey[4] = key[7];
    subkey[5] = key[4];
    subkey[6] = key[9];
    subkey[7] = key[8];

    return subkey;
}

bitset<10> shift(bitset<10> &key, int num) {
    bitset<10> shifted_key;
    num %= 5;   // to garantee that (index - num) > -5
    
    for (int i = 0 ; i < 10 ; i++) {
        if (i < 5)
            shifted_key[(i-num + 5) % 5] = key[i];
        else 
            shifted_key[5 + ((i-5)-num + 5) % 5] = key[i];
    }

    return shifted_key;
}

bitset<8> ip(bitset<8> &data) {
    bitset<8> permutation;

    permutation[0] = data[1];
    permutation[1] = data[5];
    permutation[2] = data[2];
    permutation[3] = data[0];
    permutation[4] = data[3];
    permutation[5] = data[7];
    permutation[6] = data[4];
    permutation[7] = data[6];

    return permutation;
}

bitset<8> ip_inverse(bitset<8> &data) {
    bitset<8> permutation;

    permutation[0] = data[3];
    permutation[1] = data[0];
    permutation[2] = data[2];
    permutation[3] = data[4];
    permutation[4] = data[6];
    permutation[5] = data[1];
    permutation[6] = data[7];
    permutation[7] = data[5];

    return permutation;
}

bitset<8> e_p(bitset<4> &num) {
    bitset<8> expansion;

    expansion[0] = num[3];
    expansion[1] = num[0];
    expansion[2] = num[1];
    expansion[3] = num[2];
    expansion[4] = num[1];
    expansion[5] = num[2];
    expansion[6] = num[3];
    expansion[7] = num[0];

    return expansion;
}

bitset<2> S0(bitset<4> &num) {
    int s_box[4][4];

    // matrix initialization
    s_box[0][0] = 1; s_box[0][1] = 0; s_box[0][2] = 3; s_box[0][3] = 2;
    s_box[1][0] = 3; s_box[1][1] = 2; s_box[1][2] = 1; s_box[1][3] = 0;
    s_box[2][0] = 0; s_box[2][1] = 2; s_box[2][2] = 1; s_box[2][3] = 3;
    s_box[3][0] = 3; s_box[3][1] = 1; s_box[3][2] = 3; s_box[3][3] = 2;

    int lin, col;
    lin = (num[0]<<1) + num[3];
    col = (num[1]<<1) + num[2];

    bitset<2> ans(s_box[lin][col]);
    return ans;
}

bitset<2> S1(bitset<4> &num) {
    int s_box[4][4];

    // matrix initialization
    s_box[0][0] = 0; s_box[0][1] = 1; s_box[0][2] = 2; s_box[0][3] = 3;
    s_box[1][0] = 2; s_box[1][1] = 0; s_box[1][2] = 1; s_box[1][3] = 3;
    s_box[2][0] = 3; s_box[2][1] = 0; s_box[2][2] = 1; s_box[2][3] = 0;
    s_box[3][0] = 2; s_box[3][1] = 1; s_box[3][2] = 0; s_box[3][3] = 3;

    int lin, col;
    lin = (num[0]<<1) + num[3];
    col = (num[1]<<1) + num[2];

    bitset<2> ans(s_box[lin][col]);
    return ans;
}

bitset<4> p4(bitset<4> &num) {
    bitset<4> permutation;

    permutation[0] = num[1];
    permutation[1] = num[3];
    permutation[2] = num[2];
    permutation[3] = num[0];

    return permutation;
}

bitset<8> sw(bitset<8> &text) {
    bitset<8> result;

    for (int i = 0 ; i < 4 ; i++) {
        result[i] = text[i+4];
        result[i+4] = text[i];
    }

    return result;
}