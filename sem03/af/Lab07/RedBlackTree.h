#pragma once

#include <cstdlib>
#include <string>
#include "Profiler.h"
#define SIZE(tree, node) ((node != tree->nil) ? node->size : 0)

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

typedef enum { BLACK, RED } Color;

typedef struct _Node {
    int key;
    Color color;
    int size;
    struct _Node* parent;
    struct _Node* left;
    struct _Node* right;
} Node;

typedef struct _RBTree {
    Node* nil;
    Node* root;
} RBTree;

RBTree* rbTreeCreate();

Node* nodeCreate(int key);

Node *rbSelect(RBTree *tree, Node *node, int rank, int n);

void rbTreeInsert(RBTree *tree, int key, int n);

void rbDelete(RBTree *tree, int key, int n);

void rbTreePrint(RBTree* tree, Node* root, std::string indent = "", bool last = false);

void report();
