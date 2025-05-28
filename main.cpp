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

    string binaryInput;
    inputFile >> binaryInput;

    bitset<32> inputBits(binaryInput);
    //
    //unsigned int testText = static_cast<unsigned int>(inputBits.to_ulong());
    unsigned long testText = inputBits.to_ulong();
    bitset<48> outputBits = expansionPermutationE(testText);

    outputFile << "Initial Text: " << inputBits << endl;
    outputFile << "Text After Expansion Permutation E: " << outputBits << endl;

    inputFile.close();
    outputFile.close();

    cout << "yo" << endl;
    return 0;

}