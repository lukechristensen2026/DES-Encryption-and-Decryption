# DES-Encryption-and-Decryption

## Input Files
### input.txt 
input.txt is the main input file for the program, the input should follow the format

Plaintext
Plaintext'
Key
Key'

Where each of the values is a string of 0's and 1's totalling 64 characters long.
An apostrophe denotes a string where one bit has been modified from the original version to help illustrate the avalanche effect, P-P' and K-K' are otherwise the same.

### decryptinput.txt 
decryptinput.txt is the input file for the decryption program, this file should follow the format

Ciphertext
Key

## Output Files
### output.txt
output.txt is the main output file that has the information on avalanching
example output:

Avalanche Demonstration

Plaintext P: 0000000100100011010001010110011110001001101010111100110111101111
Plaintext P': 1000000100100011010001010110011110001001101010111100110111101111
Key K: 0001001100110100010101110111100110011011101111001100111111110001
Key K': 0011001100110100010101110111100110011011101111001100111111110001

P and P' under K
Ciphertext C: 1101001111100000110000011100011100000111110101000100001000001000
Ciphertext C': 1000101010111011100011100100010111101100010111110001101100001100

Round DES0 DES1 DES2 DES3
0	1	1	1	1
1	6	5	1	6
2	17	17	2	8
3	16	14	1	11
4	16	18	3	7
5	14	7	2	15
6	16	19	3	19
7	11	20	1	20
8	14	17	4	13
9	13	21	3	16
10	15	17	5	19
11	17	19	2	13
12	20	17	5	22
13	19	10	3	18
14	12	21	4	19
15	15	18	1	15
16	16	12	5	19

P under K and K'
Ciphertext C: 1101001111100000110000011100011100000111110101000100001000001000
Ciphertext C': 1010101001101110110100111000110011000000111110000110110000001100

Round DES0 DES1 DES2 DES3
0	0	0	0	0
1	4	0	0	4
2	18	0	0	7
3	18	0	1	10
4	13	0	1	8
5	16	0	2	19
6	21	0	1	15
7	15	0	4	17
8	13	0	5	11
9	18	0	4	17
10	17	0	5	14
11	9	0	4	17
12	15	0	5	19
13	14	0	8	17
14	14	0	7	15
15	15	0	8	19
16	13	0	5	20

Total running time: 0.012 seconds

### decryptoutput.txt
decryptoutput.txt is the output file that shows the result of the decryption program being run
example ouptut:

DECRYPTION
Ciphertext C: 0000000100100011010001010110011110001001101010111100110111101111
Key K:        0000000100100011010011010110011110001001101010111100110111101111
Plaintext P:  1001111111010110100110101000101010011011111110011000111100010010
