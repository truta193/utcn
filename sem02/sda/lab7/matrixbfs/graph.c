#include "graph.h"
#include <stdlib.h>
#include <memory.h>

GraphT *graphCreate(FILE *fin, int isOriented) {
    if (fin == NULL) {
        return NULL;
    }

    int nrNodes = 0;
    fscanf(fin, "%d", &nrNodes);

    int **mat = malloc(sizeof(int*) * nrNodes);
    for (int i = 0; i < nrNodes; i++) {
        mat[i] = malloc(sizeof(int) * nrNodes);
        memset(mat[i], 0, nrNodes * sizeof(int));
    }

    while (!feof(fin)) {
        int a, b;
        fscanf(fin, "%d %d", &a, &b);
        mat[a][b] = 1;
        if (isOriented)
            mat[b][a] = 1;
    }

    //Print matrix
    for (int i = 0; i < nrNodes; i++) {
        for (int j = 0; j < nrNodes; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    GraphT *graph = malloc(sizeof(GraphT));
    graph->nrNodes = nrNodes;
    graph->matrix = mat;
    return graph;
}

void graphPrintBFS(GraphT *graph) {
    if (graph == NULL)
        return;

    int start = 0;
    printf("Give starting node: \n");
    scanf("%d", &start);

    int visited[graph->nrNodes];
    memset(visited, 0, sizeof(int) * graph->nrNodes);
    QUEUE *queue = create_queue();

    visited[start] = 1;
    queueElementT nd;
    nd.id = start;
    enqueue(queue, &(nd.queueEntry));
    printf("%d ", start);

    while(queue_get_size(queue) != 0) {
        queueElementT *node = CONTAINING_RECORD(dequeue(queue), queueElementT, queueEntry);
        for (int i = 0; i < graph->nrNodes; i++) {
            //If neighbors
            if (graph->matrix[node->id][i] == 1) {
                if (visited[i] == 0) {
                    visited[i] = 1;
                    printf("%d ", i);
                    queueElementT tmp;
                    tmp.id = i;
                    enqueue(queue, &(tmp.queueEntry));
                }
            }
        }
    }

};

