#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


typedef struct _vector_t {
    int size;
    int capacity;
    float *vec;
} Vector_t;

Status createVector(int initialCap, Vector_t **pVector) {
    Vector_t *ret = malloc(sizeof(Vector_t));
    if (ret == NULL) {
        return STAT_ERROR_MEMORY;
    }

    ret->capacity = initialCap;
    ret->size = 0;
    ret->vec = malloc(sizeof(float) * initialCap);
    if (ret->vec == NULL) {
        free(ret);
        return STAT_ERROR_MEMORY;
    }

    *pVector = ret;

    return STAT_SUCCESS;
};

static Status growIfNeeded(Vector_t *vector, int growthSize) {
    if (vector->size + growthSize <= vector->capacity) {
        return STAT_SUCCESS;
    }

    do {
        vector->capacity = vector->capacity * 2;
    } while (vector->size + growthSize > vector->capacity);

    vector->vec = realloc(vector->vec, sizeof(float) * (vector->size + growthSize));
    if (vector->vec == NULL) {
        return STAT_ERROR_MEMORY;
    }

    return STAT_SUCCESS;
}

Status vectorPushFront(Vector_t *vector, float elem) {
    if (growIfNeeded(vector, 1) != STAT_SUCCESS) {
        return STAT_ERROR;
    }

    for (int i = vector->size; i > 0; i--) {
        vector->vec[i] = vector->vec[i - 1];
    }

    vector->vec[0] = elem;
    vector->size++;

    return STAT_SUCCESS;
}

//TODO
Status vectorPushBatchFront(Vector_t *vector, float *elems, int elemCount) {
    if (growIfNeeded(vector, elemCount) != STAT_SUCCESS) {
        return STAT_ERROR;
    }

    memcpy(vector->vec + elemCount, vector->vec, vector->size * sizeof(float));
    memcpy(vector->vec, elems, elemCount * sizeof(float));
    vector->size += elemCount;
    return STAT_SUCCESS;
}

void vectorPrint(Vector_t *vector) {
    for (int i = 0; i < vector->size; i++) {
        printf("%.3f ", vector->vec[i]);
    }
    printf("\n");
}