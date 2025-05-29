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

    string binaryInput, binaryKey;
    inputFile >> binaryInput >> binaryKey;

    cout << "Read input: " << binaryInput << endl;
    cout << "Read key:   " << binaryKey << endl;

    bitset<64> inputBits(binaryInput);
    bitset<64> inputKey(binaryKey);

    bitset<56> actualKey;
    int j = 55;
    for (int i = 63; i >= 0; i--) {
        if ((i % 8) != 0) {
            actualKey[j--] = inputKey[i];
        }
    }

    cout << "Bitset<64> inputBits: " << inputBits << endl;
    cout << "Bitset<64> fullKey:   " << inputKey << endl;
    cout << "Bitset<56> strippedKey: " << actualKey << endl;



    //dont know how much of this test output stuff we need to keep so im leaving it for now
    unsigned long long testText = inputBits.to_ullong(); 

    bitset<48> outputBits = expansionPermutationE(testText);
    long roundKey = inputBits.to_ullong();
    bitset<48> outputBits2 = xorWithRoundKey(outputBits, roundKey);
    

    
    bitset<64> ciphertext = DES0(inputBits, actualKey);


 


    outputFile << "Initial Text: " << inputBits << endl;
    outputFile << "Key: " << actualKey << endl;
    outputFile << "Text After Expansion Permutation E: " << outputBits << endl;
    outputFile << "Text After Expansion Permutation E and XOR: " << outputBits2 << endl;
    outputFile << "Ciphertext: " << ciphertext << endl;

    inputFile.close();
    outputFile.close();

    cout << "yo" << endl;
    return 0;

}