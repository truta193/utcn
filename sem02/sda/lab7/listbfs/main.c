#include <stdio.h>
#include "graph.h"
#include <stdlib.h>

int main() {
    int nrNode = 0;
    int nrEdge = 0;

    scanf("%d %d", &nrNode, &nrEdge);

    GraphT *graph = NULL;
    graph = graphCreate(nrNode);

    for (int i = 0; i < nrEdge; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        graphAddEdge(graph, x, y);
    }


    NeighborT *n = CONTAINING_RECORD(sll_get_first(graph->neighbors[1]), NeighborT, sllEntry);
    graphPrintBFS(graph, n);

    return 0;
}
