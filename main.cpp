#include <iostream>
#include <bitset>
#include <fstream>
#include <chrono>
#include <string>
#include "functions.hpp"

using namespace std;
using namespace chrono;


bitset<64> readBinaryString(const string& str) {// Converts a string to a bitset<64>
    if (str.length() != 64) {
        throw runtime_error("Input string must be 64 bits long");
    }
    return bitset<64>(str);
}


vector<int> analyzeAvalanche(const vector<bitset<32>>& states1, const vector<bitset<32>>& states2) { //takes to vectors of bitsets and checks how bits are different between them
    vector<int> differences;
    for (size_t i = 0; i < states1.size(); i++) {
        differences.push_back(countDifferingBits(states1[i], states2[i]));
    }
    return differences;
}

int main() {
    try {
        //starts time tracking
        auto start = chrono::high_resolution_clock::now();
        
        //prepares the files for reading and writing
        ifstream inFile("input.txt");
        ofstream outFile("output.txt");

        string line;
        vector<string> inputs;
        while (getline(inFile, line) && inputs.size() < 4) {
            inputs.push_back(line);// Read each line from the innput file so we can get the plaintext and keys in the variables below
        }

        bitset<64> P = readBinaryString(inputs[0]);
        bitset<64> pPrime = readBinaryString(inputs[1]);
        bitset<64> K = readBinaryString(inputs[2]);
        bitset<64> kPrime = readBinaryString(inputs[3]);

        outFile << "Avalanche Demonstration\n\n";
        outFile << "Plaintext P: " << P << "\n";
        outFile << "Plaintext P': " << pPrime << "\n";
        outFile << "Key K: " << K << "\n";
        outFile << "Key K': " << kPrime << "\n\n";
        //writes the initial values to the output file

        // The running time will be calculated at the end

        cout << "Bitset<64> inputBits:   " << P << endl;
        cout << "Bitset<64> fullKey:     " << K << endl;
        cout << "Bitset<64> inputBit 2:   " << pPrime << endl;
        cout << "Bitset<64> fullKey 2:     " << kPrime << endl;
        //terminal output for debugging

        // vectors for tracking the round outputs for avalnche analysis
        vector<bitset<32>> statesPK, statesPPrimeK;
        vector<bitset<32>> statesPK1, statesPPrimeK1;
        vector<bitset<32>> statesPK2, statesPPrimeK2;
        vector<bitset<32>> statesPK3, statesPPrimeK3;

        //actual encryption process with each of the different kinds of DES functions and the two different kinds of input with the two cipher texts
        bitset<64> C = DES0(P, K, statesPK);
        bitset<64> Cprime = DES0(pPrime, K, statesPPrimeK);
        DES1(P, K, statesPK1);
        DES1(pPrime, K, statesPPrimeK1);
        DES2(P, K, statesPK2);
        DES2(pPrime, K, statesPPrimeK2);
        DES3(P, K, statesPK3);
        DES3(pPrime, K, statesPPrimeK3);

        outFile << "P and P' under K\n";
        outFile << "Ciphertext C: " << C << "\n";
        outFile << "Ciphertext C': " << Cprime << "\n\n";

        // actually applies the avlanche analysis here
        vector<int> diffPDES0 = analyzeAvalanche(statesPK, statesPPrimeK);
        vector<int> diffPDES1 = analyzeAvalanche(statesPK1, statesPPrimeK1);
        vector<int> diffPDES2 = analyzeAvalanche(statesPK2, statesPPrimeK2);
        vector<int> diffPDES3 = analyzeAvalanche(statesPK3, statesPPrimeK3);

        outFile << "Round DES0 DES1 DES2 DES3\n";
        for (size_t i = 0; i < 17; i++) {
            outFile << i << "\t" << diffPDES0[i] << "\t"
                   << diffPDES1[i] << "\t"
                   << diffPDES2[i] << "\t"
                   << diffPDES3[i] << "\n";
        }
        outFile << "\n";//this loop is used to populate the table of avalanche analysis with the different bits int he output file

        //this whole next section is the same as the above but with the second key and plaintext
        vector<bitset<32>> statesPKprime;
        vector<bitset<32>> statesPKprime1;
        vector<bitset<32>> statesPKprime2;
        vector<bitset<32>> statesPKprime3;

        bitset<64> CKprime = DES0(P, kPrime, statesPKprime);
        DES1(P, kPrime, statesPKprime1);
        DES2(P, kPrime, statesPKprime2);
        DES3(P, kPrime, statesPKprime3);

        outFile << "P under K and K'\n";
        outFile << "Ciphertext C: " << C << "\n";
        outFile << "Ciphertext C': " << CKprime << "\n\n";

        vector<int> diffKDES0 = analyzeAvalanche(statesPK, statesPKprime);
        vector<int> diffKDES1 = analyzeAvalanche(statesPK1, statesPKprime1);
        vector<int> diffKDES2 = analyzeAvalanche(statesPK2, statesPKprime2);
        vector<int> diffKDES3 = analyzeAvalanche(statesPK3, statesPKprime3);

        outFile << "Round DES0 DES1 DES2 DES3\n";
        for (size_t i = 0; i < 17; i++) {
            outFile << i << "\t" << diffKDES0[i] << "\t"
                   << diffKDES1[i] << "\t"
                   << diffKDES2[i] << "\t"
                   << diffKDES3[i] << "\n";
        }
        //same section ends



        inFile.close();
        // record end time and calculate duration
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        outFile << "\nTotal running time: " << duration.count() / 1000.0 << " seconds\n";
        //had to print the run time at the end
        outFile.close(); //close both files as good practice
        return 0;
    
    }
    catch (const exception& e) {//error catching mostly for sebugging and ensuring the input is a correct size
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}