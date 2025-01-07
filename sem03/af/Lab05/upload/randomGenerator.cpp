#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "randomGenerator.h"

void fillRandomArray(int *arr, int size, int range_min, int range_max, bool unique, int sorted);
char* generateRandomString(int length);
int generateRandomInt(int min, int max);

RandomGenerator *createRandomGenerator() {
    RandomGenerator *randomGenerator = (RandomGenerator *) malloc(sizeof(RandomGenerator));
    srand(time(NULL));
    randomGenerator->fillRandomArray = fillRandomArray;
    randomGenerator->generateRandomString = generateRandomString;
    randomGenerator->generateRandomInt = generateRandomInt;
    return randomGenerator;
};

void fillRandomArray(int *arr, int size, int range_min=10, int range_max=50000, bool unique=false, int sorted=UNSORTED)
{
    int i, pos, extendedSize;
    bool discreteType = true;
    int interval_len = range_max - range_min + 1;
    int idx1, idx2;
    int aux;

    if(range_min >= range_max) {
        throw "empty range";
    }

    if(typeid(int) == typeid(double) || typeid(int) == typeid(float)) {
        discreteType = false;
    }
    if(!unique) {
        //no worries
        for(i=0; i<size; ++i) {
            if(discreteType) {
                arr[i] = range_min + (rand() % int(interval_len));
            } else {
                arr[i] = range_min + ((int)(rand()) / RAND_MAX) * (interval_len - 1);
            }
        }
        if(sorted == ASCENDING) {
            std::sort(arr, arr + size);
        } else if(sorted == DESCENDING) {
            std::sort(arr, arr + size, std::greater<int>());
        }
    } else {
        //use Knuth approach
        if(discreteType) {
            if(interval_len < size) {
                fprintf(stderr, "[ERROR] cannot generate %d unique numbers in an interval of length %d!\n", size, int(interval_len));
                throw "range too small";
            }
            pos = 0;
            for(i=0; i<=interval_len && pos<size; ++i) {
                if(rand() % (int(interval_len) - i) < (size - pos)) {
                    arr[pos++] = range_min + i;
                }
            }
        } else {
            //use the same approach as above, pick integers from 0 to 17*size
            extendedSize = 17 * size;
            pos = 0;
            for(i=0; i<=extendedSize && pos<size; ++i) {
                if(rand() % (extendedSize - i) < (size - pos)) {
                    arr[pos++] = range_min + ((int)i / extendedSize) * (interval_len - 1);
                }
            }
        }
        //we got a sorted array in ascending order
        if(sorted == DESCENDING) {
            std::reverse(arr, arr+size);
        }else if(sorted == UNSORTED) {
            //we need to scramble the array
            for(i=0; i<size; ++i) {
                idx1 = rand() % size;
                idx2 = rand() % size;
                aux = arr[idx1];
                arr[idx1] = arr[idx2];
                arr[idx2] = aux;
            }
        }
    }
}

char* generateRandomString(int length) {
    char *str = (char *) malloc(sizeof(char) * (length + 1));
    for(int i = 0; i < length; i++) {
        str[i] = (char) (rand() % 26 + 97);
    }
    str[length] = '\0';
    return str;
};

int generateRandomInt(int min, int max) {
    return min + (rand() % (max - min + 1));
}
