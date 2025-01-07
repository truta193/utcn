#include <cstring>
#include "hashtable.h"

int hashTableInit(HashTableT *hash) {
    memset(hash, 0, sizeof(HashTableT));

    hash->modulo = MAX_HASH_SIZE;
    hash->hashFunction = hashTableHashFunc;
    hash->hashProbing = hashTableProbingFuncSec;
    memset(hash->table, EMPTY, sizeof(hash->table));

    return 0;
}

int hashTableHashFunc(HashTableT *hash, int key) {
    return key % hash->modulo;
};
int hashTableHashFuncSec(HashTableT *hash, int key) {
    return 5 - (key % 5);
};

int hashTableProbingFunc(HashTableT *hash, int key, int attempt) {
    return (hash->hashFunction(hash, key) + attempt) % hash->modulo;
};

int hashTableProbingFuncSec(HashTableT *hash, int key, int attempt) {
    return (hash->hashFunction(hash, key) + hashTableHashFuncSec(hash, key)) & hash->modulo;
};


int hashTableInsert(HashTableT *hash, int key) {
    int pos;

    for (int att = 0; att < MAX_HASH_SIZE; att++) {
        pos = hash->hashProbing(hash, key, att);
        if (hash->table[pos] == EMPTY || hash->table[pos] == DELETED) {
            hash->table[pos] = key;
            return 0;
        }
    }

    return -1;
}

bool hashTableSearch(HashTableT *hash, int key) {
    int pos;

    for (int att = 0; att < MAX_HASH_SIZE; att++) {
        pos = hash->hashProbing(hash, key, att);

        if (hash->table[pos] == EMPTY) {
            return false;
        }

        if (hash->table[pos] == key) {
            return true;
        }
    }

    return false;
}

int hashTableDelete(HashTableT *hash, int key) {
    int pos;

    for (int att = 0; att < MAX_HASH_SIZE; att++) {
        pos = hash->hashProbing(hash, key, att);

        if (hash->table[pos] == EMPTY) {
            break;
        }

        if (hash->table[pos] == key) {
            hash->table[pos] = DELETED;
            break;
        }
    }

    return 0;
}