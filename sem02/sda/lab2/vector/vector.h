#pragma once

typedef enum _status {
    STAT_ERROR_MEMORY,
    STAT_ERROR,
    STAT_SUCCESS
} Status;

typedef struct _vector_t Vector_t;

Status vectorCreate(int initialCap, Vector_t **pVector);
Status vectorSearchKey(Vector_t *vector, int key, int *index);
Status vectorPushBack(Vector_t *vector, int elem);
Status vectorPushFront(Vector_t *vector, int elem);
Status vectorDeleteFirst(Vector_t *vector);
Status vectorDeleteLast(Vector_t *vector);
Status vectorDeleteKey(Vector_t *vector, int key);
void vectorPrint(Vector_t *vector);