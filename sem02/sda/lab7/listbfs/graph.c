#include <stdio.h>
#include "graph.h"
#include "stdlib.h"
#include "string.h"

GraphT *graphCreate(int nrNodes) {
    GraphT *graph = malloc(sizeof(GraphT));

    if (graph == NULL)
        return NULL;

    graph->nrNodes = nrNodes;

    graph->neighbors = malloc(sizeof(SL_LIST *) * nrNodes);
    if (graph->neighbors != NULL) {
        for (int i = 0; i < nrNodes; i++) {
            graph->neighbors[i] = sll_create_list();
        }
    }

    return graph;
}

NeighborT *graphNeighborCreate(int neighbor) {
    NeighborT *nei = malloc(sizeof(NeighborT));
    if (nei == NULL)
        return NULL;

    memset(nei, 0, sizeof(NeighborT));
    nei->neighbor = neighbor;

    return nei;
}

void graphAddEdge(GraphT *graph, int x, int y) {
    if (graph == NULL)
        return;

    NeighborT *n1 = graphNeighborCreate(x);
    NeighborT *n2 = graphNeighborCreate(y);

    sll_insert_first(graph->neighbors[x], &n2->sllEntry);
    sll_insert_first(graph->neighbors[y], &n1->sllEntry);
}

void graphAddArc(GraphT *graph, int x, int y) {
    if (graph == NULL)
        return;

    NeighborT *n2 = graphNeighborCreate(y);

    sll_insert_first(graph->neighbors[x], &n2->sllEntry);
}

void graphPrintBFS(GraphT *graph, NeighborT *start) {
    int touched[graph->nrNodes];
    QUEUE *queue = NULL;
    queue = create_queue();
    for (int i = 0; i < graph->nrNodes; i++)
        touched[i] = UNTOUCHED;

    touched[start->neighbor] = TOUCHED;
    printf("%d ", start->neighbor);
    enqueue(queue, &start->queueEntry);

    while (queue_get_size(queue)) {
        QUEUE_ENTRY *entry = dequeue(queue);
        NeighborT *node = CONTAINING_RECORD(entry, NeighborT, queueEntry);

        SLL_ENTRY *cursor = sll_get_first(graph->neighbors[node->neighbor]);

        while (cursor != NULL) {

            NeighborT *nodeNeightbor = CONTAINING_RECORD(cursor, NeighborT, sllEntry);
            if (touched[nodeNeightbor->neighbor] == UNTOUCHED) {
                touched[nodeNeightbor->neighbor] = TOUCHED;

                printf("%d ", nodeNeightbor->neighbor);

                enqueue(queue, &nodeNeightbor->queueEntry);
            }
            cursor = cursor->next;
        }

    }

}













