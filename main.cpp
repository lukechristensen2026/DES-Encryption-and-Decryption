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


bitset<64> readBinaryString(const string& str) {
    if (str.length() != 64) {
        throw runtime_error("Input string must be 64 bits long");
    }
    return bitset<64>(str);
}

vector<int> analyzeAvalanche(const vector<bitset<32>>& states1, const vector<bitset<32>>& states2) {
    vector<int> differences;
    for (size_t i = 0; i < states1.size(); i++) {
        differences.push_back(countDifferingBits(states1[i], states2[i]));
    }
    return differences;
}

int main() {
    try {
        ifstream inFile("input.txt");
        ofstream outFile("output.txt");

        string line;
        vector<string> inputs;
        while (getline(inFile, line) && inputs.size() < 4) {
            inputs.push_back(line);
        }

        bitset<64> P = readBinaryString(inputs[0]);
        bitset<64> P_prime = readBinaryString(inputs[1]);
        bitset<64> K = readBinaryString(inputs[2]);
        bitset<64> K_prime = readBinaryString(inputs[3]);

        outFile << "Avalanche Demonstration\n\n";
        outFile << "Plaintext P: " << P << "\n";
        outFile << "Plaintext P': " << P_prime << "\n";
        outFile << "Key K: " << K << "\n";
        outFile << "Key K': " << K_prime << "\n\n";

        cout << "Bitset<64> inputBits:   " << P << endl;
        cout << "Bitset<64> fullKey:     " << K << endl;



         vector<bitset<32>> states_P_K, states_Pprime_K;
        vector<bitset<32>> states_P_K1, states_Pprime_K1;
        vector<bitset<32>> states_P_K2, states_Pprime_K2;
        vector<bitset<32>> states_P_K3, states_Pprime_K3;

        bitset<64> C = DES0(P, K, states_P_K);
        bitset<64> C_prime = DES0(P_prime, K, states_Pprime_K);
        DES1(P, K, states_P_K1);
        DES1(P_prime, K, states_Pprime_K1);
        DES2(P, K, states_P_K2);
        DES2(P_prime, K, states_Pprime_K2);
        DES3(P, K, states_P_K3);
        DES3(P_prime, K, states_Pprime_K3);

        outFile << "P and P' under K\n";
        outFile << "Ciphertext C: " << C << "\n";
        outFile << "Ciphertext C': " << C_prime << "\n\n";

        vector<int> diff_P_DES0 = analyzeAvalanche(states_P_K, states_Pprime_K);
        vector<int> diff_P_DES1 = analyzeAvalanche(states_P_K1, states_Pprime_K1);
        vector<int> diff_P_DES2 = analyzeAvalanche(states_P_K2, states_Pprime_K2);
        vector<int> diff_P_DES3 = analyzeAvalanche(states_P_K3, states_Pprime_K3);

        outFile << "Round DES0 DES1 DES2 DES3\n";
        for (size_t i = 0; i < 17; i++) {
            outFile << i << "\t" << diff_P_DES0[i] << "\t"
                   << diff_P_DES1[i] << "\t"
                   << diff_P_DES2[i] << "\t"
                   << diff_P_DES3[i] << "\n";
        }
        outFile << "\n";


        vector<bitset<32>> states_P_Kprime;
        vector<bitset<32>> states_P_Kprime1;
        vector<bitset<32>> states_P_Kprime2;
        vector<bitset<32>> states_P_Kprime3;

        bitset<64> C_Kprime = DES0(P, K_prime, states_P_Kprime);
        DES1(P, K_prime, states_P_Kprime1);
        DES2(P, K_prime, states_P_Kprime2);
        DES3(P, K_prime, states_P_Kprime3);

        outFile << "P under K and K'\n";
        outFile << "Ciphertext C: " << C << "\n";
        outFile << "Ciphertext C': " << C_Kprime << "\n\n";

        vector<int> diff_K_DES0 = analyzeAvalanche(states_P_K, states_P_Kprime);
        vector<int> diff_K_DES1 = analyzeAvalanche(states_P_K1, states_P_Kprime1);
        vector<int> diff_K_DES2 = analyzeAvalanche(states_P_K2, states_P_Kprime2);
        vector<int> diff_K_DES3 = analyzeAvalanche(states_P_K3, states_P_Kprime3);

        outFile << "Round DES0 DES1 DES2 DES3\n";
        for (size_t i = 0; i < 17; i++) {
            outFile << i << "\t" << diff_K_DES0[i] << "\t"
                   << diff_K_DES1[i] << "\t"
                   << diff_K_DES2[i] << "\t"
                   << diff_K_DES3[i] << "\n";
        }

        inFile.close();
        outFile.close();
        return 0;
    
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}