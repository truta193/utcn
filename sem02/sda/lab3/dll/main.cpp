#include <iostream>
#include "DoublyLinkedList.h"

int main() {
    dllHeaderT list;
    dllInit(&list);
//    dllInsertFirst(&list, 0);
//    dllInsertFirst(&list, 1);
//    dllInsertFirst(&list, 2);
    dllInsertLast(&list, 3);
    dllInsertLast(&list, 4);
    dllInsertFirst(&list, 5);
    dllInsertAfterKey(&list, 4, 7);
    dllInsertLast(&list, 50);

    dllPrint(&list);
    dllPrintReversed(&list);

    dllNodeT *n = dllSearchKey(&list, 4);
    printf("%d\n", n->key);

    return 0;
}
