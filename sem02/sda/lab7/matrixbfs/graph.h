#pragma once

#include "single_linked_list.h"
#include "queue.h"
#include <limits.h>
#include <stdio.h>

#define UNTOUCHED INT_MIN
#define TOUCHED (INT_MIN + 1)


typedef struct {
    int nrNodes;
    int **matrix;
} GraphT;

typedef struct {
    int id;
    QUEUE_ENTRY queueEntry;
} queueElementT;

GraphT *graphCreate(FILE *fin, int isOriented);

void graphPrintBFS(GraphT *graph);
