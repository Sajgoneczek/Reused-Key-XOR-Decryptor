# Reused-Key-XOR-Decryptor
This repository contains a C-based cryptanalysis tool designed to break XOR ciphers where the encryption key has been catastrophically reused across multiple messages. This vulnerability is commonly known as a Many-Time Pad attack.

## The Vulnerability
The security of an XOR cipher relies entirely on the key being as long as the message and used only once (One-Time Pad). When a key is reused:

1. $C_1 = P_1 \oplus K$
2. $C_2 = P_2 \oplus K$

By XORing two ciphertexts together, the key cancels out, leaving the XOR of two plaintexts:
$C_1 \oplus C_2 = (P_1 \oplus K) \oplus (P2 \oplus K) = P_1 \oplus P_2$

## How it works

The program implements a statistical frequency analysis attack. Since we have 27 different ciphertexts encrypted with the same key, we can treat each byte position (column) as a separate problem:

1. **Brute Force**: For each byte position, the program tries all 256 possible key values (`0x00`, `0xFF`).
2. **Scoring**: For every guess, it "decrypts" the byte across all 27 ciphertexts and assigns a score based on how closely the results match **English** letter frequencies.
     * High scores are given for common characters (space, 'e', 't', 'a').
     * Penalty points are given for unprintable characters
3. **Recovery**: The key byte with the highest cumulative score is selected as the winner for that position.

## Getting Started

### Prerequisites
* A C compiler (like gcc or clang).

### Compilation
Use the following command to compile the source code:
```bash
gcc -o MTP_attack MTP_attack.c
```
Simply run the executable:
```bash
./MTP_attack
