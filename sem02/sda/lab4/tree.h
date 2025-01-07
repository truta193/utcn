#pragma once

#include <cstdio>

typedef struct _treeNode {
    int key;
    struct _treeNode *left;
    struct _treeNode *right;
} treeNodeT;

treeNodeT *treeCreate(FILE *fin);

void treePrintPreorder(treeNodeT *node);

void treePrintInorder(treeNodeT *node);

void treePrintPostorder(treeNodeT *node);

int treeGetHeight(treeNodeT *node);

int treeGetDiamater(treeNodeT *node);

int treeGetLeafCount(treeNodeT *node);

int treeGetInternalNodeCount(treeNodeT *node);

treeNodeT *treeSearchKey(treeNodeT *node, int key);

int treeGetNodeLevel(treeNodeT *root, treeNodeT *node);

//int treeGetKeyHeight(treeNodeT *node, int key);
//Just treeGetHeight(treeSearchKey()) //ex6 ultima fraza

//File format:
//n [number of nodes 1st line]
// a1 a2 a3 ... an [node values 2nd line]
treeNodeT *treeBalancedCreate(FILE *fin);


