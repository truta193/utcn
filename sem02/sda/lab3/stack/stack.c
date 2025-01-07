#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void stackInit(StackT *stack) {
    stack->top = NULL;
    stack->size = 0;
}

void stackPush(StackT *stack, int givenKey) {
    NodeT *node = createNode(givenKey, stack->top);
    stack->top = node;
    stack->size++;
};
void stackPop(StackT *stack) {
    NodeT *top = stack->top;
    stack->top = stack->top->next;
    free(top);
    stack->size--;
};
void stackPrint(StackT *stack) {
    while (stack->top != NULL) {
        printf("%d ", stack->top->key);
        stack->top = stack->top->next;
    }
    printf("\n");
};
