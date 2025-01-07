#include "DoublyLinkedList.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

void dllInit(dllHeaderT *header) {
    header->first = nullptr;
    header->last = nullptr;
}

void dllPrint(dllHeaderT *header) {
    dllNodeT *node = header->first;
    while (node != nullptr) {
        printf("%d ", node->key);
        node = node->next;
    }
    printf("\n");
};

void dllPrintReversed(dllHeaderT *header) {
    dllNodeT *node = header->last;
    while (node != nullptr) {
        printf("%d ", node->key);
        node = node->prev;
    }
    printf("\n");

}


dllNodeT *dllCreateNode(int key, dllNodeT *next, dllNodeT *prev) {
    dllNodeT *node = (dllNodeT *) malloc(sizeof(dllNodeT));
    if (node == nullptr) {
        return nullptr;
    }
    memset(node, 0, sizeof(dllNodeT));
    node->key = key;
    node->next = next;
    node->prev = prev;
    return node;
};

dllNodeT *dllSearchKey(dllHeaderT *header, int givenKey) {
    if (header == nullptr) {
        return nullptr;
    }

    dllNodeT *node = header->first;
    while (node != nullptr) {
        if (node->key == givenKey) {
            return node;
        }
        node = node->next;
    }
    return nullptr;
};

void dllInsertFirst(dllHeaderT *header, int givenKey) {
    if (header == nullptr) {
        return;
    }

    dllNodeT *node = dllCreateNode(givenKey, nullptr, nullptr);
    if (header->first == nullptr) {
        header->first = node;
        header->last = node;
        return;
    }

    node->prev = nullptr;
    node->next = header->first;
    header->first->prev = node;
    header->first = node;

};

void dllInsertLast(dllHeaderT *header, int givenKey) {
    if (header == nullptr) {
        return;
    }

    if (header->first == nullptr) {
        dllInsertFirst(header, givenKey);
        return;
    }

    dllNodeT *node = dllCreateNode(givenKey, nullptr, nullptr);
    header->last->next = node;
    node->prev = header->last;
    header->last = node;
};

void dllInsertAfterKey(dllHeaderT *header, int afterKey, int givenKey) {
    if (header == nullptr) {
        return;
    }

    dllNodeT *node = dllSearchKey(header, afterKey);
    if (node == nullptr) {
        return;
    }

    dllNodeT *newNode = dllCreateNode(givenKey, nullptr, nullptr);

    if (node == header->first) {
        dllInsertFirst(header, givenKey);
        return;
    }

    if (node == header->last) {
        dllInsertLast(header, givenKey);
        return;
    }

    newNode->next = node->next;
    newNode->prev = node;
    node->next->prev = newNode;
    node->next = newNode;
};

void dllDeleteFirst(dllHeaderT *header) {
    if (header == nullptr || header->first == nullptr) {
        return;
    }

    dllNodeT *firstNode = header->first;
    header->first = header->first->next;
    header->first->prev = nullptr;
    free(firstNode);
};

void dllDeleteLast(dllHeaderT *header) {
    if (header == nullptr || header->first == nullptr) {
        return;
    }

    dllNodeT *lastNode = header->last;
    header->last = header->last->prev;
    header->last->next = nullptr;
    free(lastNode);
};

void dllDeleteKey(dllHeaderT *header, int givenKey) {
    if (header == nullptr || header->first == nullptr) {
        return;
    }

    dllNodeT *node = dllSearchKey(header, givenKey);

    if (node == nullptr) {
        return;
    }

    if (node == header->first) {
        dllDeleteFirst(header);
        return;
    }
    if (node == header->last) {
        dllDeleteLast(header);
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
};