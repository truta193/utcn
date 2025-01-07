#pragma once

#include "single_linked_list.h"
#include "queue.h"
#include <limits.h>

#define UNTOUCHED INT_MIN
#define TOUCHED (INT_MIN + 1)

typedef struct {
    int neighbor;
    SLL_ENTRY sllEntry;
    QUEUE_ENTRY queueEntry;
} NeighborT;

typedef struct {
    int nrNodes;
    SL_LIST **neighbors;
} GraphT;

GraphT *graphCreate(int nrNodes);

NeighborT *graphNeighborCreate(int neighbor);

void graphAddEdge(GraphT *graph, int x, int y);

void graphAddArc(GraphT *graph, int x, int y);

void graphPrintBFS(GraphT *graph, NeighborT *start);
