#include <stdio.h>
#include "vector.h"

int main() {
    Vector_t *vec = NULL;
    createVector(3, &vec);
    vectorPushFront(vec, 5.0f);
    vectorPushFront(vec, 7.0f);

    float temp[6] = {4.0f, 1.0f, 5.0f, 9.0f, -1.5f, -9.0f};
    vectorPushBatchFront(vec, temp, 6);

    vectorPrint(vec);
    return 0;
}
