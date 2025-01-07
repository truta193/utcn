#include "graph.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "int_stack.h"

graphVertexT *graphVertexCreate(int value) {
    graphVertexT *vertex = malloc(sizeof (graphVertexT));
    if (vertex == NULL) {
        return NULL;
    }

    memset(vertex, 0, sizeof(graphVertexT));
    vertex->node = value;
    return vertex;
};

graphT *graphCreate(int nodeCount) {
    graphT *graph = malloc(sizeof(graphT));

    if (graph == NULL) {
        return NULL;
    }

    graph->nodeCount = nodeCount;
    graph->neighbors = malloc(nodeCount * sizeof(SL_LIST *));

    if (graph->neighbors != NULL) {
        for (int i = 0; i < nodeCount; i++){
            graph->neighbors[i] = sll_create_list();
        }
    }

    graph->neighbors2 = malloc(nodeCount * sizeof(DL_LIST *));
    if (graph->neighbors2 != NULL) {
        for (int i = 0; i < nodeCount; i++) {
            graph->neighbors2[i] = dll_create_list();
        }
    }

    graph->parentList = malloc(nodeCount * sizeof(int));
    if (graph->parentList != NULL) {
        memset(graph->parentList, 0, nodeCount * sizeof(int));
    }

    graph->visited = malloc(sizeof(int) * nodeCount);
    if (graph->visited != NULL) {
        memset(graph->visited, 0, nodeCount * sizeof(int));
    }

    graph->discovered = malloc(sizeof(int) * nodeCount);
    if (graph->discovered != NULL) {
        memset(graph->discovered, 0, nodeCount * sizeof(int));
    }

    graph->depleted = malloc(sizeof(int) * nodeCount);
    if (graph->depleted != NULL) {
        memset(graph->depleted, 0, nodeCount * sizeof(int));
    }

    graph->departure = malloc(sizeof(int) * nodeCount);
    if (graph->departure != NULL) {
        memset(graph->departure, 0, nodeCount * sizeof(int));
    }

    graph->time = 0;

    return graph;
};

void graphAddEdge(graphT *graph, int x, int y) {
    if (graph == NULL) {
        return;
    }

    graphVertexT *arc1 = graphVertexCreate(y);
    graphVertexT *arc2 = graphVertexCreate(x);
    sll_insert_first(graph->neighbors[x], &arc1->sllEntry);
    sll_insert_first(graph->neighbors[y], &arc2->sllEntry);

    dll_insert_first(graph->neighbors2[x], &arc1->dllEntry);
    dll_insert_first(graph->neighbors2[y], &arc2->dllEntry);


}

void graphAddArc(graphT *graph, int x, int y) {
    if (graph == NULL) {
        return;
    }

    graphVertexT *arc1 = graphVertexCreate(y);
    sll_insert_first(graph->neighbors[x], &arc1->sllEntry);

    dll_insert_first(graph->neighbors2[x], &arc1->dllEntry);
}


void graphRecursiveDFS(graphT *graph, int start_node, int *cycleFlag, SL_LIST *sl) {
    graph->time++;
    graph->discovered[start_node] = graph->time;
    graph->visited[start_node] = GRAPH_COLOR_GRAY;

    DLL_ENTRY *entry = dll_get_last(graph->neighbors2[start_node]);
    while (entry != NULL) {
        graphVertexT *neighbor = CONTAINING_RECORD(entry, graphVertexT, dllEntry);

        if (graph->visited[neighbor->node] == GRAPH_COLOR_GRAY)
            *cycleFlag = 1;

        if (graph->visited[neighbor->node] == GRAPH_COLOR_WHITE) {
            graph->parentList[neighbor->node] = start_node;
            graphRecursiveDFS(graph, neighbor->node, cycleFlag, sl);
        };

        entry = entry->prev;
    }

    graph->visited[start_node] = GRAPH_COLOR_BLACK;
    graph->depleted[start_node] = graph->time;
    graphVertexT *slnode = malloc(sizeof(graphVertexT));
    slnode->node = start_node;
    sll_insert_first(sl, &slnode->sllEntry);
}

SL_LIST *topologicalSort(graphT *graph, int start_node) {
    int cycleFlag = 0;
    SL_LIST *sl = sll_create_list();

    for (int i = 0; i < graph->nodeCount; i++) {
        if (graph->visited[i] == GRAPH_COLOR_WHITE) {
            graphRecursiveDFS(graph, i, &cycleFlag, sl);
        }
    }
    if (cycleFlag) {
        printf("Graph contains cycles, cannot apply topological sort.\n");
        return NULL;
    }
    return sl;

//    graphVertexT *slnode = malloc(sizeof(graphVertexT));
//    slnode->node = start_node;
//    sll_insert_last(sl, &slnode->sllEntry);


};