#pragma once
#define ALPHABET_LEN 26
#define PRIME_NR 5831

#include <string>

int charAlphabetIndex(char chr);

long long power(int nr, int pow);

int hashingFunction(int length, std::string pattern);

int rollHash(int length, std::string pattern, int oldHash);