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
        graphAddArc(graph, x, y);
    }

    SL_LIST *sl = topologicalSort(graph, 0);

    SLL_ENTRY *cursor = sll_get_first(sl);
    while (cursor != NULL) {
        printf("%d ", CONTAINING_RECORD(cursor, graphVertexT, sllEntry)->node);
        cursor = cursor->next;
    }

    fclose(fin);
    return 0;
}
