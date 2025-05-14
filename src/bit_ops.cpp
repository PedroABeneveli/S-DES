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
    // as the key is small, we can directly map the bits from the key to the resulting shift
    // k0 k1 k2 k3 k4 | k5 k6 k7 k8 k9
    // =>
    // k1 k2 k3 k4 k0 | k6 k7 k8 k9 k5

    bitset<10> shifted_key;

    for (int i = 0 ; i < 10 ; i++) {
        if (i < 5)
            shifted_key[(i-num + 5) % 5] = key[i];
        else 
            shifted_key[5 + ((i-5)-num + 5) % 5] = key[i];
    }

    return shifted_key;
}