#include "sdes.h"
#include "bit_ops.h"

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

    concat[0] = s0_ret[0];
    concat[1] = s0_ret[1];
    concat[2] = s1_ret[0];
    concat[3] = s1_ret[1];

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