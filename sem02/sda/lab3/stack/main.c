#include <stdio.h>
#include "stack.h"

int main() {
    StackT stack;
    stackInit(&stack);
    stackPush(&stack, 0);
    stackPush(&stack, 1);
    stackPush(&stack, 2);
    stackPop(&stack);
    stackPush(&stack, 3);

    stackPrint(&stack);
    return 0;
}
