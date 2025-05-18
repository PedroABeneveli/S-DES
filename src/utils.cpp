#include "utils.h"

string show_data(bitset<8> &data) {
    string result;

    for (int i = 0 ; i < 8 ; i++) 
        result.push_back(data[i]+'0');

    return result;
}

string show_data(bitset<10> &data) {
    string result;

    for (int i = 0 ; i < 10 ; i++) 
        result.push_back(data[i]+'0');

    return result;
}

bitset<10> key_to_bits(string key) {
    reverse(key.begin(), key.end());
    return bitset<10>(key);
}

bitset<8> text_to_bits(string text) {
    reverse(text.begin(), text.end());
    return bitset<8>(text);
}