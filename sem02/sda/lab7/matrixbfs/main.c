#include <stdio.h>
#include "graph.h"
int main() {
    FILE *fin = fopen("../date.in", "r");
    GraphT *graph = graphCreate(fin, 1);
    graphPrintBFS(graph);
    return 0;
}
