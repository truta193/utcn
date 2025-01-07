#pragma once

#include <cstdlib>

typedef struct {
    int *parent;
    int size;
} ParentVectorTree;

ParentVectorTree *createParentVectorTree(int size);

void destroyParentVectorTree(ParentVectorTree *parentVectorTree);

void printParentVectorTree(ParentVectorTree *parentVectorTree, int parent = -1, int indent = 0);




