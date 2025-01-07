#pragma once

typedef struct NodeT {
    int key;
    struct NodeT *next;
} NodeT;


NodeT *createNode(int key, NodeT *next);

NodeT *searchKey(NodeT *first, int givenKey);

void insertFirst(NodeT **first, NodeT **last, int givenKey);

void insertLast(NodeT **first, NodeT **last, int givenKey);

void insertAfterKey(NodeT **first, NodeT **last, int afterKey, int givenKey);

void deleteFirst(NodeT **first, NodeT **last);

void deleteLast(NodeT **first, NodeT **last);

void deleteKey(NodeT **first, NodeT **last, int givenKey);

