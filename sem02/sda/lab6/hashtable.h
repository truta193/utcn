#pragma once

#define MAX_HASH_SIZE 101
#define EMPTY (-1)
#define DELETED (-2)

typedef struct _hash HashT;

typedef int (*tfnHashFunction)(HashT *hash, int key);

typedef int (*tfnProbingFunction)(HashT *hash, int key, int attempt);

typedef struct _hash {
    int modulo;
    int table[MAX_HASH_SIZE];
    int size;
    tfnHashFunction hashFunction;
    tfnProbingFunction hashProbing;
} HashTableT;

int hashTableInit(HashTableT *hash);

int hashTableHashFunc(HashTableT *hash, int key);

int hashTableProbingFunc(HashTableT *hash, int key, int attempt);

int hashTableHashFuncSec(HashTableT *hash, int key);

int hashTableProbingFuncCuad(HashTableT *hash, int key, int attempt);

int hashTableProbingFuncSec(HashTableT *hash, int key, int attempt);

int hashTableInsert(HashTableT *hash, int key);

bool hashTableSearch(HashTableT *hash, int key);

int hashTableDelete(HashTableT *hash, int key);




