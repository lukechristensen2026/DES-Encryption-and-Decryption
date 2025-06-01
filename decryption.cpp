//Decryption algorithm for our DES implementation
////Written by: Luke Christensen c3533694 and Reviewed by: Lachlan Turner c3477306 Group 10
#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include "functions.hpp"

using namespace std;

//Converts the string input to bitset
bitset<64> readBinaryString(const string &str)
{
    if (str.length() != 64)
    {
        throw runtime_error("Input string must be 64 bits long");
    }
    return bitset<64>(str);
}

int main()
{
    try
    {
        //prepares the files for reading and writing
        ifstream inFile("decryptinput.txt");
        ofstream outFile("decryptoutput.txt");

        //reads the input file
        string ciphertextStr, keyStr;
        getline(inFile, ciphertextStr);
        getline(inFile, keyStr);

        bitset<64> ciphertext = readBinaryString(ciphertextStr);
        bitset<64> key = readBinaryString(keyStr);

        //runs the decryption function
        bitset<64> plaintext = DES0Decrypt(ciphertext, key);

        //outputs the decrypted plaintext
        outFile << "DECRYPTION\n";
        outFile << "Ciphertext C: " << ciphertext << "\n";
        outFile << "Key K:        " << key << "\n";
        outFile << "Plaintext P:  " << plaintext << "\n";

        inFile.close();
        outFile.close();
        return 0;
    }
    //error catching mostly for sebugging and ensuring the input is a correct size
    catch (const exception e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}