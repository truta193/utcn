#pragma once

#include <cstdlib>
#include <cstring>

#define DEF_MODULO 101

typedef struct _hashNode {
    int key;
    struct _hashNode *next;
} HashNodeT;

typedef struct _hash {
    HashNodeT **table;
    int modulo;
} HashTableT;

int hashFunction(HashTableT *ht, int key);

void hashTableInit(HashTableT *ht);

void hashTableInsert(HashTableT *ht, int key);

HashNodeT *hashTableSearch(HashTableT *ht, int key);

void hashTableDelete(HashTableT *ht, int key);