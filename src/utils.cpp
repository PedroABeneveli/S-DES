#include "../headers/utils.h"

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