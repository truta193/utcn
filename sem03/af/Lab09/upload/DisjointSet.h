#pragma once
#include "Node.h"
#include "Profiler.h"
class DisjointSet {
private:
    Node** nodes;
    int size;
    Profiler *profiler;
public:
    DisjointSet(Profiler *profiler, int size);
    void makeSet(int key, char *assignOp, int n);
    int findSet(int key, char *assignOp, char *compOp, int n);
    void unionSets(int key1, int key2, char *assignOp, char *compOp, int n, char *findCompOp, char *findAssignOp);
    void printSet(int key);
    void printAllSets();
    int getSize();
};
