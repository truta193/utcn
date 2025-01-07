#include <cstdio>
#include <iostream>
#include "ParentVectorTree.h"

using std::cout, std::endl;

ParentVectorTree *createParentVectorTree(int size) {
    ParentVectorTree *parentVectorTree = (ParentVectorTree *) malloc(sizeof(ParentVectorTree));
    parentVectorTree->parent = (int *) malloc(sizeof(int) * size);
    parentVectorTree->size = size;
    for (int i = 0; i < size; ++i) {
        parentVectorTree->parent[i] = -1;
    }
    return parentVectorTree;
}

void destroyParentVectorTree(ParentVectorTree *parentVectorTree) {
    free(parentVectorTree->parent);
    free(parentVectorTree);
}

void printParentVectorTree(ParentVectorTree *parentVectorTree, int parent, int indent)
{
    for (int i = 0; i != parentVectorTree->size; i++)
    {
        if (parentVectorTree->parent[i] == parent) {
            for (int j = 0; j < indent; j++) {
                cout << "  ";
            }
            cout<< i << endl;
            printParentVectorTree(parentVectorTree, i, indent + 2);
        }
    }
}
