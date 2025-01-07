#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct _vector_t {
    int size;
    int capacity;
    int *vec;
} Vector_t;


Status vectorCreate(int initialCap, Vector_t **pVector) {
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
}

static Status growIfNeeded(Vector_t *vector, int growthSize) {
    if (vector == NULL) {
        return STAT_ERROR_MEMORY;
    }

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

Status vectorSearchKey(Vector_t *vector, int key, int *index) {
    for (int i = 0; i < vector->size; i++) {
        if (vector->vec[i] == key) {
            *index = i;
            return STAT_SUCCESS;
        }
    }
    *index = -1;
    return STAT_ERROR;
}

Status vectorPushBack(Vector_t *vector, int elem) {
    if (vector == NULL) {
        return STAT_ERROR_MEMORY;
    }

    if (growIfNeeded(vector, 1) != STAT_SUCCESS) {
        return STAT_ERROR;
    }

    vector->vec[vector->size++] = elem;

    return STAT_SUCCESS;
}

Status vectorPushFront(Vector_t *vector, int elem) {
    if (vector == NULL) {
        return STAT_ERROR_MEMORY;
    }

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

Status vectorDeleteFirst(Vector_t *vector) {
    if (vector == NULL) {
        return STAT_ERROR_MEMORY;
    }

    for (int i = 0; i < vector->size; i++) {
        vector->vec[i] = vector->vec[i + 1];
    }

    vector->size--;
    return STAT_SUCCESS;
}

Status vectorDeleteLast(Vector_t *vector) {
    if (vector == NULL) {
        return STAT_ERROR_MEMORY;
    }

    vector->size--;
    return STAT_SUCCESS;
}

Status vectorDeleteKey(Vector_t *vector, int key) {
    if (vector == NULL) {
        return STAT_ERROR_MEMORY;
    }

    for (int i = 0; i < vector->size; i++) {
        if (vector->vec[i] == key) {
            for (int j = i; j < vector->size; j++) {
                vector->vec[j] = vector->vec[j + 1];
            }
            vector->size--;
            return STAT_SUCCESS;
        }
    }

    return STAT_ERROR;
}

void vectorPrint(Vector_t *vector) {
    for (int i = 0; i < vector->size; i++) {
        printf("%d ", vector->vec[i]);
    }
    printf("\n");
}