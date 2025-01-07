#pragma once

typedef struct dllNode {
    int key;
    struct dllNode *next;
    struct dllNode *prev;
} dllNodeT;

typedef struct dllHeader {
    dllNodeT *first;
    dllNodeT *last;
} dllHeaderT;

void dllInit(dllHeaderT *header);

void dllPrint(dllHeaderT *header);

void dllPrintReversed(dllHeaderT *header);

dllNodeT *dllCreateNode(int key, dllNodeT *next, dllNodeT *prev);

dllNodeT *dllSearchKey(dllHeaderT *header, int givenKey);

void dllInsertFirst(dllHeaderT *header, int givenKey);

void dllInsertLast(dllHeaderT *header, int givenKey);

void dllInsertAfterKey(dllHeaderT *header, int afterKey, int givenKey);

void dllDeleteFirst(dllHeaderT *header);

void dllDeleteLast(dllHeaderT *header);

void dllDeleteKey(dllHeaderT *header, int givenKey);