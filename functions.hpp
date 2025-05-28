#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <bitset>

using namespace std;

//Expansion Permutation E
const int ExpandedSet[48] = {
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};


bitset<48> expansionPermutationE(int inputValue) {
    bitset<32> inputBits(inputValue);
    bitset<48> result;

    for (int i = 0; i < 48; i++) {
        result[47 - i] = inputBits[32 - ExpandedSet[i]];
    }

    return result;
}

//XOR with a round key
bitset<48> xorWithRoundKey(const bitset<48> expandedInput, const bitset<48> roundKey) {
    bitset<48> result;

    for (int i = 0; i < 48; i++) {
        bool bit1 = expandedInput[i];
        bool bit2 = roundKey[i];

        if ((bit1 && !bit2) || (!bit1 && bit2)) {
            result[i] = 1;
        } else {
            result[i] = 0;
        }
    }

    return result;
}


//S-boxes
//Permutation P


#endif