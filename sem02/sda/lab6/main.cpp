#include <iostream>
#include "hashtable.h"

int main() {
    HashTableT hash;
    hashTableInit(&hash);

    hashTableInsert(&hash, 10);
    hashTableInsert(&hash, 111);
    hashTableInsert(&hash, 80);
    hashTableInsert(&hash, 35);
    hashTableInsert(&hash, 350);
    hashTableInsert(&hash, 95);
    hashTableInsert(&hash, 32);
    hashTableInsert(&hash, 75);

    printf("%d is %sfound\n", 10, hashTableSearch(&hash, 10) ? "" : "not ");
    printf("%d is %sfound\n", 111, hashTableSearch(&hash, 111) ? "" : "not ");
    hashTableDelete(&hash, 10);
    printf("%d is %sfound\n", 10, hashTableSearch(&hash, 10) ? "" : "not ");
    printf("%d is %sfound\n", 111, hashTableSearch(&hash, 111) ? "" : "not ");


//    HashTableT hash;
//    hashTableInit(&hash);
//
//    hashTableInsert(&hash, 10);
//    hashTableInsert(&hash, 111);
//    hashTableInsert(&hash, 80);
//    hashTableInsert(&hash, 35);
//    hashTableInsert(&hash, 350);
//    hashTableInsert(&hash, 95);
//    hashTableInsert(&hash, 32);
//    hashTableInsert(&hash, 75);
//
//
//    printf("%d is %sfound\n", 10, hashTableSearch(&hash, 10) ? "" : "not ");
//    printf("%d is %sfound\n", 111, hashTableSearch(&hash, 111) ? "" : "not ");
//    hashTableDelete(&hash, 10);
//    printf("%d is %sfound\n", 10, hashTableSearch(&hash, 10) ? "" : "not ");
//    printf("%d is %sfound\n", 111, hashTableSearch(&hash, 111) ? "" : "not ");

    return 0;
}
