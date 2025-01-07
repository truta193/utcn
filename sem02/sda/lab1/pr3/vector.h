#pragma once

typedef enum _status {
    STAT_ERROR_MEMORY,
    STAT_ERROR,
    STAT_SUCCESS
} Status;

typedef struct _vector_t Vector_t;

Status createVector(int initialCap, Vector_t **pVector);
Status vectorPushFront(Vector_t *vector, float elem);
Status vectorPushBatchFront(Vector_t *vector, float *elems, int elemCount);
void vectorPrint(Vector_t *vector);
