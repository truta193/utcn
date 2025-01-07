#pragma once

typedef struct _node3 {
    int value;
    struct _node3 *leftChild;
    struct _node3 *rightBrother;
} Node3;

typedef struct {
    Node3 *root;
} BinaryTree;

BinaryTree *createBinaryTree();

void destroyBinaryTree(Node3 *root);
void printBinaryTree(Node3 *root, int indent = 0);


