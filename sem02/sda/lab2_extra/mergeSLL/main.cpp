#include <iostream>

typedef struct _node {
    int key;
    struct _node *next;
} NodeT;

typedef struct _list {
    NodeT *start;
    int len;
} ListT;



void listInsert(ListT *list, int key) {
    NodeT *node = (NodeT*) malloc(sizeof(NodeT));
    node->key = key;
    if (list->start == nullptr)  {
        list->start = node;
        return;
    }

    NodeT *cursor = list->start;
    while (cursor != nullptr && cursor->next != nullptr) cursor = cursor->next;
    cursor->next = node;
    list->len++;
}

void listPrint(ListT *list) {
    NodeT *cursor = list->start;
    while (cursor != nullptr) {
        printf("%d ", cursor->key);
        cursor = cursor->next;
    }
}

int main() {
    ListT l1 = {nullptr, 0};
    ListT l2 = {nullptr, 0};

    listInsert(&l1, 2);
    listInsert(&l1, 5);
    listInsert(&l1, 6);
    listInsert(&l1, 7);
    listInsert(&l1, 12);
    listInsert(&l1, 20);

    listInsert(&l2, 1);
    listInsert(&l2, 4);
    listInsert(&l2, 5);
    listInsert(&l2, 8);
    listInsert(&l2, 15);
    listInsert(&l2, 16);
    listInsert(&l2, 19);
    listInsert(&l2, 23);
    listInsert(&l2, 28);
    listInsert(&l2, 30);

    NodeT *mergeStart = (NodeT*)malloc(sizeof(NodeT));
    NodeT *cursorM = mergeStart;
    NodeT *cursor1 = l1.start;
    NodeT *cursor2 = l2.start;

    while (cursor1 != nullptr && cursor2 != nullptr) {
        if (cursor1->key <= cursor2->key) {
            cursorM->next = cursor1;
            cursorM = cursorM->next;
            cursor1 = cursor1->next;
        } else {
            cursorM->next = cursor2;
            cursorM = cursorM->next;
            cursor2 = cursor2->next;
        }
    }
    while (cursor1 != nullptr) {
        cursorM->next = cursor1;
        cursorM = cursorM->next;
        cursor1 = cursor1->next;
    }

    while (cursor2 != nullptr) {
        cursorM->next = cursor2;
        cursorM = cursorM->next;
        cursor2 = cursor2->next;
    }

    cursorM = mergeStart;
    while (cursorM != nullptr) {
        printf("%d ", cursorM->key);
        cursorM = cursorM->next;
    }
    printf("\n");



    return 0;
}
