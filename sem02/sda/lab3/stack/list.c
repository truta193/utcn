#include <stdio.h>
#include <stdlib.h>
#include "list.h"


NodeT *createNode(int key, NodeT *next) {
    NodeT *newNode = malloc(sizeof(NodeT));
    if (newNode == NULL) {
        return NULL;
    }

    newNode->key = key;
    newNode->next = next;
    return newNode;
};


NodeT *searchKey(NodeT *first, int givenKey) {
    while (first != NULL && first->key != givenKey) {
        first = first->next;
    }
    return first;
};


void insertFirst(NodeT **first, NodeT **last, int givenKey) {
    if (first == NULL || last == NULL) {
        return;
    }
    NodeT *newNode = createNode(givenKey, *first);
    if (*first == NULL) {
        *last = newNode;
    }
    *first = newNode;
};


void insertLast(NodeT **first, NodeT **last, int givenKey) {
    NodeT *newNode = createNode(givenKey, NULL);
    if (*first == NULL) {
        *first = newNode;
        *last = newNode;
        return;
    }
    (*last)->next = newNode;
    *last = newNode;
};


void insertAfterKey(NodeT **first, NodeT **last, int afterKey, int givenKey) {
    NodeT *targetNode = searchKey(*first, afterKey);
    if (targetNode == NULL) {
        return;
    }

    NodeT *newNode = createNode(givenKey, targetNode->next);
    if (targetNode == *last) {
        *last = newNode;
    }
    targetNode->next = newNode;
};


void deleteFirst(NodeT **first, NodeT **last) {
    if (first == NULL || last == NULL) {
        return;
    }

    if (*first == NULL) {
        return;
    }

    NodeT *temp = *first;
    *first = (*first)->next;
    free(temp);
};


void deleteLast(NodeT **first, NodeT **last) {
    if (*first == NULL) {
        return;
    }

    NodeT *beforeLastNode = *first;
    while (beforeLastNode->next != *last) {
        beforeLastNode = beforeLastNode->next;
    }

    free(*last);
    beforeLastNode->next = NULL;
    *last = beforeLastNode;

}


void deleteKey(NodeT **first, NodeT **last, int givenKey) {
    if (first == NULL) {
        return;
    }

    NodeT *nodeToDelete = searchKey(*first, givenKey);
    if (nodeToDelete == NULL) {
        return;
    }

    if (nodeToDelete == *first) {
        deleteFirst(first, last);
        return;
    }
    if (nodeToDelete == *last) {
        deleteLast(first, last);
        return;
    }

    NodeT *previousNode = *first;
    while (previousNode->next != nodeToDelete) {
        previousNode = previousNode->next;
    }
    previousNode->next = nodeToDelete->next;
    free(nodeToDelete);
}

