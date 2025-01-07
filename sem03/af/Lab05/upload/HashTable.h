#pragma once

#define MAX_NAME_LENGTH 30
#define C1 1
#define C2 1
#define EMPTY_SLOT nullptr
#define DELETED_SLOT ((Entry *) 1)

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH + 1]; // +1 for null terminator
} Entry;

typedef struct HashTable {
    Entry **entries;
    int size;
    int entryCount;
    int searchOperationCount;
    long (*hash)(int size, int id, int i);
    void (*insert)(struct HashTable *self, Entry entry);
    Entry *(*searchById)(struct HashTable *self, int id);
    Entry *(*searchByName)(struct HashTable *self, char *name);
    Entry *(*searchExact)(struct HashTable *self, Entry entry);
    void (*deleteById)(struct HashTable *self, int id);
} HashTable;

// HashTable functions
HashTable *createHashTable(int size);
void destroyHashTable(HashTable *hashTable);
void printHashTable(HashTable *hashTable);
//Do not expose these
//int hash(int size, int id, int i);
//void insertEntry(HashTable *hashTable, Entry entry);
//Entry *searchEntryById(HashTable *hashTable, int id);
//Entry *searchEntryByName(HashTable *hashTable, char *name);
//Entry *searchEntryExact(HashTable *hashTable, Entry entry);
//void deleteEntry(HashTable *hashTable, int id);


