#pragma once

typedef struct _bstNode {
    int key;
    struct _bstNode *left;
    struct _bstNode *right;
    struct _bstNode *parent;
} bstNodeT;

bstNodeT *bstNodeCreate(bstNodeT *parent, int key);

bstNodeT *bstNodeInsert(bstNodeT *root, int key);

void bstPrintPreorder(bstNodeT *node);

void bstPrintInorder(bstNodeT *node);

void bstPrintPostorder(bstNodeT *node);

bstNodeT *bstSearchKey(bstNodeT *root, int key);

bstNodeT *bstFindMin(bstNodeT *node);

bstNodeT *bstFindMax(bstNodeT *node);

bstNodeT* bstFindSuccessor(bstNodeT *node);

bstNodeT* bstFindPredecessor(bstNodeT *node);

void bstDeleteKey(bstNodeT *root, int key);

