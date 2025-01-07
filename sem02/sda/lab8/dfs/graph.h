#pragma once

#include "single_linked_list.h"
#include "double_linked_list.h"

typedef struct {
    int node;
    SLL_ENTRY sllEntry;
    DLL_ENTRY dllEntry;
} graphVertexT;

typedef struct {
    int nodeCount;
    SL_LIST **neighbors;
    DL_LIST **neighbors2;
    int *parentList;
    int *visited;
    int *discovered;
    int *depleted;
    int time;
} graphT;

typedef enum {
    GRAPH_COLOR_WHITE,
    GRAPH_COLOR_GRAY,
    GRAPH_COLOR_BLACK
} graphStatusT;

graphT *graphCreate(int nodeCount);

void graphAddEdge(graphT *graph, int x, int y);

void graphAddArc(graphT *graph, int x, int y);

void graphIterativeDFS(graphT *graph, int startNode);

void graphIterativeDFSBetter(graphT *graph, int startNode);

void graphRecursiveDFS(graphT *graph, int start_node);

