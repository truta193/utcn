#pragma once
#include "list.h"

typedef struct _stack {
    NodeT *top;
    unsigned size;
} StackT;

void stackInit(StackT *stack);
void stackPush(StackT *stack, int givenKey);
void stackPop(StackT *stack);
void stackPrint(StackT *stack);
