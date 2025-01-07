#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include "HashTable.h"
#include "randomGenerator.h"

#define TABLE_SIZE 10007
#define SEARCH_M 3000
#define NR_TESTS 5

using std::cout, std::endl;

RandomGenerator *randomGenerator = createRandomGenerator();
FILE *fout = fopen("output.csv", "w");

void hashTableDemo() {
    HashTable *hashTable = createHashTable(11);
    Entry entry1 = {35, "John"};
    Entry entry2 = {66, "Mary"};
    Entry entry3 = {23, "Peter"};
    Entry entry4 = {12, "Paul"};
    Entry entry5 = {79, "George"};
    Entry entry6 = {44, "Lucy"};
    Entry entry7 = {88, "Jane"};

    hashTable->insert(hashTable, entry1);
    hashTable->insert(hashTable, entry2);
    hashTable->insert(hashTable, entry3);
    hashTable->insert(hashTable, entry4);
    hashTable->insert(hashTable, entry5);
    hashTable->insert(hashTable, entry6);
    hashTable->insert(hashTable, entry7);

    printHashTable(hashTable);

    Entry *ret = hashTable->searchById(hashTable, 35);
    cout << "-------------------" << endl;
    cout << ret->id << " " << ret->name << endl;
    ret = hashTable->searchByName(hashTable, "Jane");
    cout << "-------------------" << endl;
    cout << ret->id << " " << ret->name << endl;
    ret = hashTable->searchExact(hashTable, {44, "Lucy"});
    cout << "-------------------" << endl;
    cout << ret->name << endl;

    hashTable->deleteById(hashTable, 44);
    ret = hashTable->searchExact(hashTable, {44, "Lucy"});
    cout << "-------------------" << endl;
    cout << ret << endl;

}

//Pretty print function for trees stackoverflow
//https://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console


void testSearch(double fillFactor) {
    //ff = n/10007 => n = ff * 10007
    fprintf(fout, "%f,", fillFactor);
    double averageSearchCount = 0;
    double averageMaxSearchCount = 0;
    double averageNotFoundSearchCount = 0;
    double averageMaxNotFoundSearchCount = 0;
    for (int c = 0; c < NR_TESTS; c++) {
        //region Fill table
        int n = floor(fillFactor * TABLE_SIZE);
        HashTable *hashTable = createHashTable(TABLE_SIZE);
        int *arr = (int *) malloc(sizeof(int) * n);
        randomGenerator->fillRandomArray(arr, n, 0, 50000, true, UNSORTED);
        for (int i = 0; i < n; i++) {
            Entry entry = {arr[i], ""};
            char *r = randomGenerator->generateRandomString(MAX_NAME_LENGTH);
            strcpy(entry.name, r);
            free(r);
            hashTable->insert(hashTable, entry);
        }

        //endregion
        //region Search random
        int maxSearchCount = 0;

        for (int i = 0; i < SEARCH_M / 2; i++) {
            //Dupa ce luam un nr. din array, il stergem ca sa nu il luam de mai multe ori
            int randomIndex = rand() % n;
            int id = arr[randomIndex];
            arr[randomIndex] = -1;
            while (id == -1) {
                id = arr[rand() % n];
            }

            Entry *ret = hashTable->searchById(hashTable, id);
            averageSearchCount += hashTable->searchOperationCount / (double) SEARCH_M * 2;
            if (hashTable->searchOperationCount > maxSearchCount) {
                maxSearchCount = hashTable->searchOperationCount;
            }
        }

        averageMaxSearchCount += maxSearchCount;

        //endregion
        //region Search elements that don't exist
        maxSearchCount = 0;

        for (int i = 0; i < SEARCH_M / 2; i++) {
            int nr = randomGenerator->generateRandomInt(50001, 100000);
            Entry *ret = hashTable->searchById(hashTable, nr);
            averageNotFoundSearchCount += hashTable->searchOperationCount / (double) SEARCH_M * 2;
            if (hashTable->searchOperationCount > maxSearchCount) {
                maxSearchCount = hashTable->searchOperationCount;
            }
        }

        averageMaxNotFoundSearchCount += maxSearchCount;
        //endregion
    }

    fprintf(fout, "%f,%f,", averageSearchCount / NR_TESTS, averageMaxSearchCount / NR_TESTS);
    fprintf(fout, "%f,%f\n", averageNotFoundSearchCount / NR_TESTS, averageMaxNotFoundSearchCount / NR_TESTS);
}

void testDelete() {
    int n = floor(0.99 * TABLE_SIZE);
    int target = floor(0.8 * TABLE_SIZE);
    int toDeleteCount = n - target;

    double averageSearchCount = 0;
    double averageMaxSearchCount = 0;
    double averageNotFoundSearchCount = 0;
    double averageMaxNotFoundSearchCount = 0;

    for (int c = 0; c < NR_TESTS; c++) {

        HashTable *hashTable = createHashTable(TABLE_SIZE);
        int *arr = (int *) malloc(sizeof(int) * n);
        randomGenerator->fillRandomArray(arr, n, 0, 50000, true, UNSORTED);
        for (int i = 0; i < n; i++) {
            Entry entry = {arr[i], ""};
            char *r = randomGenerator->generateRandomString(MAX_NAME_LENGTH);
            strcpy(entry.name, r);
            free(r);
            hashTable->insert(hashTable, entry);
        }

        for (int i = 0; i < toDeleteCount; i++) {
            int randInt = randomGenerator->generateRandomInt(0, n - 1);
            hashTable->deleteById(hashTable, arr[randInt]);
            arr[randInt] = -1;
        }

        int searchMax = 0;

        for (int i = 0; i < SEARCH_M / 2; i++) {
            int index = randomGenerator->generateRandomInt(0, n);
            while (arr[index] == -1) {
                index = randomGenerator->generateRandomInt(0, n);
            }
            Entry *ret = hashTable->searchById(hashTable, arr[index]);
            averageSearchCount += hashTable->searchOperationCount;
            if (hashTable->searchOperationCount > searchMax) {
                searchMax = hashTable->searchOperationCount;
            }
        }

        averageMaxSearchCount += searchMax;

        searchMax = 0;
        for (int i = 0; i < SEARCH_M / 2; i++) {
            int nr = randomGenerator->generateRandomInt(50001, 100000);
            Entry *ret = hashTable->searchById(hashTable, nr);
            averageNotFoundSearchCount += hashTable->searchOperationCount;
            if (hashTable->searchOperationCount > searchMax) {
                searchMax = hashTable->searchOperationCount;
            }
        }
        averageMaxNotFoundSearchCount += searchMax;

    }

    averageSearchCount = averageSearchCount / (SEARCH_M / 2) / NR_TESTS;
    averageNotFoundSearchCount = averageNotFoundSearchCount / (SEARCH_M / 2) / NR_TESTS;
    averageMaxSearchCount = averageMaxSearchCount / NR_TESTS;
    averageMaxNotFoundSearchCount = averageMaxNotFoundSearchCount / NR_TESTS;
    fprintf(fout, "-,%f,%f,%f,%f\n", averageSearchCount, averageMaxSearchCount, averageNotFoundSearchCount,
            averageMaxNotFoundSearchCount);


}


int main() {
    fprintf(fout, "Alpha,Efort mediu gasite,Efort max gasite,Efort mediu ne-gasite,Efort max ne-gasite\n");
    testSearch(0.8);
    testSearch(0.85);
    testSearch(0.9);
    testSearch(0.95);
    testSearch(0.99);
    fprintf(fout, "-,Efort mediu gasite,Efort max gasite,Efort mediu ne-gasite,Efort max ne-gasite\n");
    testDelete();
    fclose(fout);
    hashTableDemo();
    return 0;
}
