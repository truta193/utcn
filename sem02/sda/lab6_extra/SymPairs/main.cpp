#include <iostream>
#include <cstring>

#define NR_MOD 101

int hashFunc(int key) {
    return key % NR_MOD;
}

int hashProbe(int key, int attempt) {
    return ((key % NR_MOD) + attempt) % NR_MOD;
}

void hashInsert(int *ht, int key, int value) {
    int idx = hashFunc(key);
    int i = 0;
    while (ht[hashProbe(idx, i)] != -1) i++;
    ht[hashProbe(idx, i)] = value;
}

int hashSearch(int *ht, int key, int value) {
    int idx = hashFunc(key);
    int i = 0;
    while (ht[hashProbe(idx, i)] != -1) {
        if (ht[hashProbe(idx, i)] == value)
            return ht[hashProbe(idx, i)];
        i++;
    }
    return -1;
}

int main() {
    int hash[102];
    memset(hash, -1, sizeof(int) * 102);
    int arr[] = {2, 5, 5, 8, 5, 2, 10, 60, 25, 55, 8, 5, 30, 10, 55, 25};

    for (int i = 0; i < 16; i += 2) {
        int first = arr[i];
        int second = arr[i+1];
        hashInsert(hash, first, second);

        if (hashSearch(hash, second, first) != -1) {
            std::cout << first << " " << second << std::endl;
        }

    }
    return 0;
}
