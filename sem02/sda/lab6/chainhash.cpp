#include "chainhash.h"

int hashFunction(HashTableT *ht, int key) {
    return key % (ht->modulo);
};

void hashTableInit(HashTableT *ht) {
    if (ht == nullptr) {
        ht = (HashTableT *) malloc(sizeof(HashTableT));
    }

    memset(ht, 0, sizeof(HashTableT));
    ht->table = (HashNodeT **)malloc(sizeof(HashNodeT*) * DEF_MODULO);
    ht->modulo = DEF_MODULO;
}

void hashTableInsert(HashTableT *ht, int key) {
    int indx = hashFunction(ht, key);

    HashNodeT *node = (HashNodeT *) malloc(sizeof (HashNodeT));
    node->key = key;
    if (ht->table[indx] == nullptr) {
        ht->table[indx] = node;
        return;
    }

    HashNodeT *cursor = ht->table[indx];
    while (cursor != nullptr && cursor->next != nullptr) cursor = cursor->next;
    cursor->next = node;
};

HashNodeT *hashTableSearch(HashTableT *ht, int key) {
    int indx = hashFunction(ht, key);
    HashNodeT *cursor = ht->table[indx];
    if (cursor == nullptr)
        return nullptr;

    while (cursor != nullptr && cursor->key != key)
        cursor = cursor->next;

    return cursor;

}

void hashTableDelete(HashTableT *ht, int key) {
    int indx = hashFunction(ht, key);

    //If it's the only element
    if (ht->table[indx]->next == nullptr) {
        free(ht->table[indx]);
        ht->table[indx] = nullptr;
        return;
    }

    //If it's the first element
    if (ht->table[indx]->key == key) {
        HashNodeT *temp = ht->table[indx];
        ht->table[indx] = ht->table[indx]->next;
        free(temp);
        return;
    }

    //IF we have to search for elem
    HashNodeT *prev = nullptr;
    HashNodeT *curr = ht->table[indx];

    while (curr != nullptr && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }

    //If key was not found there's nothing to delete
    if (curr == nullptr)
        return;

    //If found, delete
    prev->next = curr->next;
    free(curr);
}
