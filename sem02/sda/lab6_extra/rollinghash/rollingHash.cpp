#include "rollingHash.h"
#include <string>
#include <iostream>

using namespace std;

int charAlphabetIndex(char chr) {
    return chr - 'a' + 1;
}

long long power(int nr, int pow) {
    long long ret = 1;
    for (int i = 0; i < pow; i++) {
        ret *= nr;
    }

    return ret;
}

int hashingFunction(int length, string pattern) {
    int hash = 0;
    for (int i = 0; i < length; i++) {
        hash += (charAlphabetIndex(pattern[i]) * (int)power(ALPHABET_LEN, length - 1 - i)) % PRIME_NR;
    }
    return hash % PRIME_NR;
}

int rollHash(int length, string pattern, int oldHash) {
    long long temp = oldHash;
    temp -= (charAlphabetIndex(pattern[0])*power(ALPHABET_LEN, length - 1)) % PRIME_NR;
    temp = (temp * ALPHABET_LEN ) % PRIME_NR;
    temp += charAlphabetIndex(pattern[length-1]) % PRIME_NR;
    return (int)(temp % PRIME_NR);
}