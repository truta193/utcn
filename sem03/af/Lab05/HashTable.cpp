#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "HashTable.h"

//Quadratic hash function
long hash(int size, int id, int i);

void insertEntry(HashTable *hashTable, Entry entry);

Entry *searchEntryById(HashTable *hashTable, int id);

Entry *searchEntryByName(HashTable *hashTable, char *name);

Entry *searchEntryExact(HashTable *hashTable, Entry entry);

void deleteEntry(HashTable *hashTable, int id);


HashTable *createHashTable(int size) {
    HashTable *hashTable = (HashTable *) malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->entryCount = 0;
    hashTable->hash = hash;
    hashTable->insert = insertEntry;
    hashTable->searchById = searchEntryById;
    hashTable->searchByName = searchEntryByName;
    hashTable->searchExact = searchEntryExact;
    hashTable->deleteById = deleteEntry;
    hashTable->searchOperationCount = 0;
    hashTable->entries = (Entry **) malloc(sizeof(Entry *) * size);
    for (int i = 0; i < size; i++) {
        hashTable->entries[i] = EMPTY_SLOT;
    }
    return hashTable;
}

void destroyHashTable(HashTable *hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->entries[i] != EMPTY_SLOT && hashTable->entries[i] != DELETED_SLOT) {
            free(hashTable->entries[i]);
        }
    }
    free(hashTable->entries);
    free(hashTable);
}

void printHashTable(HashTable *hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->entries[i] != EMPTY_SLOT && hashTable->entries[i] != DELETED_SLOT) {
            printf("Index: %d, id: %d, name: %s\n", i, hashTable->entries[i]->id, hashTable->entries[i]->name);
        }
    }
}

long hash(int size, int key, int i) {
    long initialHash = key % size;
    return (initialHash + i * i * C1 + i * C2) % size;
}

void insertEntry(HashTable *hashTable, Entry entry) {
    // Verificam daca avem loc in array
    if (hashTable->entryCount == hashTable->size) {
        printf("Hash table is full\n");
        return;
    }

    // Quadratic probing, gasim prima pozitie libera
    int i = 0;
    long index = hash(hashTable->size, entry.id, i);
    while (hashTable->entries[index] != EMPTY_SLOT && hashTable->entries[index] != DELETED_SLOT) {
        i++;
        index = hashTable->hash(hashTable->size, entry.id, i);

    }
    // Am gasit prima pozitie libera, o ocupam
    hashTable->entryCount++;
    hashTable->entries[index] = (Entry *) malloc(sizeof(Entry));
    hashTable->entries[index]->id = entry.id;
    //Copiem numele
    for (int j = 0; j < MAX_NAME_LENGTH; j++) {
        hashTable->entries[index]->name[j] = entry.name[j];
    }
    hashTable->entries[index]->name[MAX_NAME_LENGTH] = '\0';
}

//region Search functions

//Names must match?
Entry *searchEntryById(HashTable *hashTable, int id) {
    hashTable->searchOperationCount = 0;
    int i = 0;
    long index = hashTable->hash(hashTable->size, id, i);
    while (i < hashTable->size && hashTable->entries[index] != EMPTY_SLOT) {
        hashTable->searchOperationCount++;
        if (index > 0 && hashTable->entries[index] != DELETED_SLOT && hashTable->entries[index]->id == id) {
            return hashTable->entries[index];
        }
        i++;
        index = hashTable->hash(hashTable->size, id, i);
    }
    return nullptr;
}

Entry *searchEntryByName(HashTable *hashTable, char *name) {
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->entries[i] != EMPTY_SLOT && hashTable->entries[i] != DELETED_SLOT) {
            if (strcmp(hashTable->entries[i]->name, name) == 0) {
                return hashTable->entries[i];
            }
        }
    }
    return nullptr;
}

Entry *searchEntryExact(HashTable *hashTable, Entry entry) {
    int i = 0;
    long index = hashTable->hash(hashTable->size, entry.id, i);
    while (hashTable->entries[index] != EMPTY_SLOT) {
        if (hashTable->entries[index] != DELETED_SLOT && hashTable->entries[index]->id == entry.id) {
            if (strcmp(hashTable->entries[index]->name, entry.name) == 0) {
                return hashTable->entries[index];
            }
        }
        i++;
        index = hashTable->hash(hashTable->size, entry.id, i);
    }
    return nullptr;
}

//endregion

void deleteEntry(HashTable *hashTable, int id) {
    int i = 0;
    long index = hashTable->hash(hashTable->size, id, i);
    while (hashTable->entries[index] != EMPTY_SLOT) {
        if (index > 0 && hashTable->entries[index] != DELETED_SLOT && hashTable->entries[index]->id == id) {
            free(hashTable->entries[index]);
            hashTable->entries[index] = DELETED_SLOT;
            hashTable->entryCount--;
            return;
        }
        i++;
        index = hashTable->hash(hashTable->size, id, i);
    }
}



