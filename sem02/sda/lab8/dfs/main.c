#include <stdio.h>
#include "graph.h"

int main() {
    graphT *graph = NULL;
    int nodeCount, edgeCount;
    FILE *fin = fopen("../date.in", "r");

    if (fin == NULL) {
        perror("Error file open");
        return -1;
    }

    fscanf(fin, "%d %d", &nodeCount, &edgeCount);

    graph = graphCreate(nodeCount);

    for (int i = 0; i < edgeCount; i++) {
        int x, y;
        fscanf(fin, "%d %d", &x, &y);
        graphAddEdge(graph, x, y);
    }

    //graphIterativeDFSBetter(graph, 1);
    printf("1 ");
    graph->parentList[1] = -1;
    graphRecursiveDFS(graph, 1);
    printf("\n");

    for (int i = 0; i < nodeCount; i++) {
        printf("%d ", graph->parentList[i]);
    }
    printf("\n");

    fclose(fin);
    return 0;
}
