#pragma once

typedef struct _edge {
    int src;
    int dest;
    int weight;
} Edge;

bool compareEdges(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}