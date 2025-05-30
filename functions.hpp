#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

//Numbers for the permutations and s-boxes were taken from https://en.wikipedia.org/wiki/DES_supplementary_material
// Initial Permutation (IP)
const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation (IP^-1)
const int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

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

// Permuted Choice 1 (PC-1)
const int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Permuted Choice 2 (PC-2)
const int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

//SBOX definition

const int S_BOX[8][4][16] = {
    { // S1
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    { // S2
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    { // S3
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    { // S4
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    { // S5
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    { // S6
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    { // S7
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    { // S8
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// Permutation P
const int P[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

bitset<48> expansionPermutationE(const bitset<32>& input) {
    bitset<48> result;
    for (int i = 0; i < 48; i++) {
        result[47 - i] = input[32 - ExpandedSet[i]];
    }
    return result;
}

bitset<32> inverseExpansionPermutationE(const bitset<48> input) {
    bitset<32> output;

    for (int i = 1; i < 32; i++) {
        //Finding one of each number from the input
        //Removing duplicates
        for (int j = 0; j < 48; j++) {
            if (ExpandedSet[j] == i+1) {
                output[31 - i] = input[47 - j]; // Adjusting bitset index
                break;
            }
        }
    }

    return output;
}

//XOR with a round key
bitset<48> xorWithRoundKey(const bitset<48>& input, const bitset<48>& key) {
    bitset<48> result;
    for (int i = 0; i < 48; i++) {
        result[i] = input[i] ^ key[i]; //Simplified this, "^" performs xor
    }
    return result;
}

//generate round keys
vector<bitset<48>> generateRoundKeys(bitset<56> key) {
    bitset<48> simpleKey;
    for (int i = 0; i < 48; i++) {
        simpleKey[47 - i] = key[55 - i]; // Just take the leftmost 48 bits
    }

    vector<bitset<48>> roundKeys(16, simpleKey); // same key for all rounds
    return roundKeys;
}



bitset<64> permute(bitset<64> input, const int* table, int size) {
    bitset<64> output;
    for (int i = 0; i < size; i++) {
        output[size - 1 - i] = input[64 - table[i]];
    }
    return output;
}


//S-boxes
bitset<32> applySBoxes(const bitset<48>& input) {
    bitset<32> output;
    int outputPos = 0;
    
    for (int i = 0; i < 8; i++) {
        int row = (input[47-6*i] << 1) | input[47-6*i-5];
        int col = (input[47-6*i-1] << 3) | (input[47-6*i-2] << 2) |
                 (input[47-6*i-3] << 1) | input[47-6*i-4];
        
        int value = S_BOX[i][row][col];
        
        for (int j = 0; j < 4; j++) {
            output[31-outputPos-j] = (value >> j) & 1;
        }
        outputPos += 4;
    }
    
    return output;
}

//Permutation P
bitset<32> permutationP(bitset<32> input) {
    bitset<32> output;
    for (int i = 0; i < 32; i++) {
        output[31 - i] = input[32 - P[i]];
    }
    return output;
}

bitset<32> fFunction(bitset<32> R, bitset<48> roundKey) {
    bitset<48> expanded = expansionPermutationE(R.to_ulong());
    bitset<48> xored = xorWithRoundKey(expanded, roundKey);
    bitset<32> sboxOut = applySBoxes(xored);
    return permutationP(sboxOut);
}
bitset<32> fFunction1(bitset<32> R, bitset<48> roundKey) {
    bitset<48> expanded = expansionPermutationE(R.to_ulong());
    //bitset<48> xored = xorWithRoundKey(expanded, roundKey);
    bitset<32> sboxOut = applySBoxes(expanded);
    return permutationP(sboxOut);
}

bitset<32> fFunction2(bitset<32> R, bitset<48> roundKey) {
    bitset<48> expanded = expansionPermutationE(R.to_ulong());
    bitset<48> xored = xorWithRoundKey(expanded, roundKey);
    return inverseExpansionPermutationE(xored);
}

bitset<32> fFunction3(bitset<32> R, bitset<48> roundKey) {
    bitset<48> expanded = expansionPermutationE(R.to_ulong());
    bitset<48> xored = xorWithRoundKey(expanded, roundKey);
    bitset<32> sboxOut = applySBoxes(xored);
    return sboxOut;
}
//this is the scaffold for the main function



bitset<64> initialPermutation(const bitset<64>& input) {
    bitset<64> output;
    for (int i = 0; i < 64; i++) {
        output[63-i] = input[64-IP[i]];
    }
    return output;
}

bitset<64> finalPermutation(const bitset<64>& input) {
    bitset<64> output;
    for (int i = 0; i < 64; i++) {
        output[63-i] = input[64-FP[i]];
    }
    return output;
}


vector<bitset<48>> generateSubkeys(const bitset<64>& key) {
    bitset<56> key56;
    for (int i = 0; i < 56; i++) {
        key56[55-i] = key[64-PC1[i]];
    }
    
    bitset<28> C, D;
    for (int i = 0; i < 28; i++) {
        C[27-i] = key56[55-i];
        D[27-i] = key56[27-i];
    }

    const int shifts[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    vector<bitset<48>> subkeys;
    
    for (int round = 0; round < 16; round++) {
        for (int i = 0; i < shifts[round]; i++) {
            bool c0 = C[27];
            bool d0 = D[27];
            C <<= 1;
            D <<= 1;
            C[0] = c0;
            D[0] = d0;
        }
        
        bitset<56> combined;
        for (int i = 0; i < 28; i++) {
            combined[55-i] = C[27-i];
            combined[27-i] = D[27-i];
        }
        
        bitset<48> subkey;
        for (int i = 0; i < 48; i++) {
            subkey[47-i] = combined[56-PC2[i]];
        }
        
        subkeys.push_back(subkey);
    }
    
    return subkeys;
}



//I need to go back over this with comments but the main difference in each of these DES functions is I've added tracking for the avalanch effect and fixed up the initial and final permutations because we werent using them.
bitset<64> DES0(const bitset<64>& plaintext, const bitset<64>& key, vector<bitset<32>>& intermediateStates) {
    auto subkeys = generateSubkeys(key);
    bitset<64> state = initialPermutation(plaintext);
    
    bitset<32> L;
    bitset<32> R;
    for(int i = 0; i < 32; i++) {
        L[i] = state[i + 32];
        R[i] = state[i];
    }
    
    intermediateStates.push_back(R);
    
    for (int round = 0; round < 16; round++) {
        bitset<32> prevR = R;
        
        bitset<48> expanded = expansionPermutationE(R);
        bitset<48> xored = xorWithRoundKey(expanded, subkeys[round]);
        bitset<32> substituted = applySBoxes(xored);
        bitset<32> permuted = permutationP(substituted);
        
        R = L ^ permuted;
        L = prevR;
        
        intermediateStates.push_back(R);
    }
    bitset<64> combined;
    for(int i = 0; i < 32; i++) {
        combined[i] = L[i];
        combined[i + 32] = R[i];
    }
    return finalPermutation(combined);
}

bitset<64> DES1(const bitset<64>& plaintext, const bitset<64>& key, vector<bitset<32>>& intermediateStates) {
    auto subkeys = generateSubkeys(key);
    bitset<64> state = initialPermutation(plaintext);
    
    bitset<32> L;
    bitset<32> R;
    for(int i = 0; i < 32; i++) {
        L[i] = state[i + 32];
        R[i] = state[i];
    }
    
    intermediateStates.push_back(R);
    
    for (int round = 0; round < 16; round++) {
        bitset<32> prevR = R;
        
        bitset<48> expanded = expansionPermutationE(R);
        bitset<32> substituted = applySBoxes(expanded);
        bitset<32> permuted = permutationP(substituted);
        
        R = L ^ permuted;
        L = prevR;
        
        intermediateStates.push_back(R);
    }
    
    bitset<64> combined;
    for(int i = 0; i < 32; i++) {
        combined[i] = L[i];
        combined[i + 32] = R[i];
    }
    return finalPermutation(combined);
}

bitset<64> DES2(const bitset<64>& plaintext, const bitset<64>& key, vector<bitset<32>>& intermediateStates) {
    auto subkeys = generateSubkeys(key);
    bitset<64> state = initialPermutation(plaintext);
    
    bitset<32> L;
    bitset<32> R;
    for(int i = 0; i < 32; i++) {
        L[i] = state[i + 32];
        R[i] = state[i];
    }
    
    intermediateStates.push_back(R);
    
    for (int round = 0; round < 16; round++) {
        bitset<32> prevR = R;

        bitset<48> expanded = expansionPermutationE(R);
        bitset<48> xored = xorWithRoundKey(expanded, subkeys[round]);
        bitset<32> contracted = inverseExpansionPermutationE(xored);
        bitset<32> permuted = permutationP(contracted);
        
        R = L ^ permuted;
        L = prevR;
        
        intermediateStates.push_back(R);
    }
    
    bitset<64> combined;
    for(int i = 0; i < 32; i++) {
        combined[i] = L[i];
        combined[i + 32] = R[i];
    }
    return finalPermutation(combined);
}

bitset<64> DES3(const bitset<64>& plaintext, const bitset<64>& key, vector<bitset<32>>& intermediateStates) {
    auto subkeys = generateSubkeys(key);
    bitset<64> state = initialPermutation(plaintext);
    
    bitset<32> L;
    bitset<32> R;
    for(int i = 0; i < 32; i++) {
        L[i] = state[i + 32];
        R[i] = state[i];
    }
    
    intermediateStates.push_back(R);
    
    for (int round = 0; round < 16; round++) {
        bitset<32> prevR = R;
        
        bitset<48> expanded = expansionPermutationE(R);
        bitset<48> xored = xorWithRoundKey(expanded, subkeys[round]);
        bitset<32> substituted = applySBoxes(xored);
        
        R = L ^ substituted;
        L = prevR;
        
        intermediateStates.push_back(R);
    }
    
    bitset<64> combined;
    for(int i = 0; i < 32; i++) {
        combined[i] = L[i];
        combined[i + 32] = R[i];
    }
    return finalPermutation(combined);
}


int countDifferingBits(const bitset<32>& a, const bitset<32>& b) {
    return (a ^ b).count();
}

#endif