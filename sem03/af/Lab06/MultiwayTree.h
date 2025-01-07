#pragma once

#include <cstdlib>

typedef struct _node2 {
    int value;
    int numberOfChildren;
    struct _node2 **children;
} Node2;

typedef struct {
    Node2 *root;
} MultiwayTree;

MultiwayTree *createMultiwayTree(int rootValue);

void destroyMultiwayTree(MultiwayTree *multiwayTree);

void addChild(Node2 *parent, int childValue);

void printMultiwayTree(Node2 *root, int indent = 0);