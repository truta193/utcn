#pragma once

enum SortMethod { UNSORTED=0, ASCENDING=1, DESCENDING=2 };

typedef struct {
    void (*fillRandomArray)(int *arr, int size, int range_min, int range_max, bool unique, int sorted);
    char* (*generateRandomString)(int length);
    int (*generateRandomInt)(int min, int max);
} RandomGenerator;

RandomGenerator *createRandomGenerator();