#pragma once

typedef struct _Node {
    int key;
    struct _Node *left;
    struct _Node *right;
} Node;

Node *createNode(int key);

void traverseTreeRecursively(Node *root, int n);

void traverseTreeIteratively(Node *root, int n);

void reportTree();