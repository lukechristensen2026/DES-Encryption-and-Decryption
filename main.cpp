//Step 1: You will first write DES code that will take as input a 
//64-bit plaintext block and a 64-bit key block (note that only 56 bits of those will be selected by PC-1, 
//since every 8th bit represents odd-parity) and produce as output a 64-bit ciphertext block.

//Step 2: You will use your implementation to explore the Avalanche effect of the original DES denoted as 
//DES0, as well as DES1, DES2, and DES3, where in each version an operation is missing in each round as follows:  
    //0. DES0 - the original version of DES. 
    //1. DES1 – XOR with a round key is missing from F function in all rounds. 
    //2. DES2 – S-boxes are missing from F function in all rounds; instead, inverse 𝐸𝐸−1of the Expansion 
    //Permutation E is used for contraction from 48 bits down to 32 bits. 
    //3. DES3 – Permutation P is missing from F function in all rounds


#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include "functions.hpp"

using namespace std;

int main() {
    ifstream inputFile("testinput.txt");
    ofstream outputFile("output.txt");

    string binaryInput, binaryInput2, binaryKey, binaryKey2;
    inputFile >> binaryInput >> binaryInput2 >> binaryKey >> binaryKey2;

    cout << "Read input Plaintext P:  " << binaryInput << endl;
    cout << "Read input Plaintext P': " << binaryInput2 << endl;
    cout << "Read key K:              " << binaryKey << endl;
    cout << "Read key K':             " << binaryKey2 << endl;

    bitset<64> inputBits(binaryInput);
    bitset<64> inputBits2(binaryInput2);

    bitset<64> inputKey(binaryKey);
    bitset<64> inputKey2(binaryKey2);

    bitset<56> actualKey;
    int j = 55;
    for (int i = 63; i >= 0; i--) {
        if ((i % 8) != 0) {
            actualKey[j--] = inputKey[i];
        }
    }

    bitset<56> actualKey2;
    int k = 55;
    for (int i = 63; i >= 0; i--) {
        if ((i % 8) != 0) {
            actualKey2[k--] = inputKey2[i];
        }
    }

    cout << "Bitset<64> inputBits:   " << inputBits << endl;
    cout << "Bitset<64> fullKey:     " << inputKey << endl;
    cout << "Bitset<56> strippedKey: " << actualKey << endl;



    //dont know how much of this test output stuff we need to keep so im leaving it for now
    unsigned long long testText = inputBits.to_ullong(); 

    bitset<48> outputBits = expansionPermutationE(testText);
    long roundKey = inputBits.to_ullong();
    bitset<48> outputBits2 = xorWithRoundKey(outputBits, roundKey);
        
    bitset<64> ciphertext  = DES0(inputBits, actualKey);
    bitset<64> ciphertext2 = DES0(inputBits2, actualKey);
    bitset<64> ciphertext3 = DES0(inputBits, actualKey2);
    bitset<64> ciphertext4 = DES0(inputBits2, actualKey2);

    outputFile << "Initial Text:         " << inputBits << endl;
    outputFile << "Key:                  " << actualKey << endl;
    outputFile << " " << endl;
    outputFile << "DES0" << endl;
    outputFile << "Ciphertext P and K:   " << ciphertext << endl;
    outputFile << "Ciphertext P' and K:  " << ciphertext2 << endl;
    outputFile << "Ciphertext P and K':  " << ciphertext3 << endl;
    outputFile << "Ciphertext P' and K': " << ciphertext4 << endl;
    outputFile << " " << endl;

    bitset<64> ciphertext5  = DES1(inputBits, actualKey);
    bitset<64> ciphertext6 = DES1(inputBits2, actualKey);
    bitset<64> ciphertext7 = DES1(inputBits, actualKey2);
    bitset<64> ciphertext8 = DES1(inputBits2, actualKey2);

    outputFile << "DES1" << endl;
    outputFile << "Ciphertext P and K:   " << ciphertext5 << endl;
    outputFile << "Ciphertext P' and K:  " << ciphertext6 << endl;
    outputFile << "Ciphertext P and K':  " << ciphertext7 << endl;
    outputFile << "Ciphertext P' and K': " << ciphertext8 << endl;
    outputFile << " " << endl;

    bitset<64> ciphertext9  = DES2(inputBits, actualKey);
    bitset<64> ciphertext10 = DES2(inputBits2, actualKey);
    bitset<64> ciphertext11 = DES2(inputBits, actualKey2);
    bitset<64> ciphertext12 = DES2(inputBits2, actualKey2);

    outputFile << "DES2" << endl;
    outputFile << "Ciphertext P and K:   " << ciphertext9 << endl;
    outputFile << "Ciphertext P' and K:  " << ciphertext10 << endl;
    outputFile << "Ciphertext P and K':  " << ciphertext11 << endl;
    outputFile << "Ciphertext P' and K': " << ciphertext12 << endl;
    outputFile << " " << endl;

    bitset<64> ciphertext13  = DES3(inputBits, actualKey);
    bitset<64> ciphertext14 = DES3(inputBits2, actualKey);
    bitset<64> ciphertext15 = DES3(inputBits, actualKey2);
    bitset<64> ciphertext16 = DES3(inputBits2, actualKey2);

    outputFile << "DES3" << endl;
    outputFile << "Ciphertext P and K:   " << ciphertext13 << endl;
    outputFile << "Ciphertext P' and K:  " << ciphertext14 << endl;
    outputFile << "Ciphertext P and K':  " << ciphertext15 << endl;
    outputFile << "Ciphertext P' and K': " << ciphertext16 << endl;
    outputFile << " " << endl;

    inputFile.close();
    outputFile.close();
    return 0;

}