#include <stdio.h>
#include "vector.h"

int main() {
    Vector_t *vector = NULL;
    if (vectorCreate(2, &vector) != STAT_SUCCESS) {
        return 1;
    };

    vectorPushBack(vector, 1);
    vectorPushBack(vector, 2);
    vectorPushBack(vector, 3);
    vectorPushBack(vector, 4);
    vectorPushFront(vector, 5);
    vectorDeleteFirst(vector);
    vectorDeleteKey(vector, 3);

    vectorPrint(vector);

    return 0;
}
