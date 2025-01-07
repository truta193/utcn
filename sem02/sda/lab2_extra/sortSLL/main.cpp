#include <iostream>

typedef struct _node {
    int key;
    struct _node *next;
} NodeT;

void push(NodeT **first, int key) {
    NodeT *newNode = (NodeT*) malloc(sizeof(NodeT));
    newNode->key = key;
    newNode->next = nullptr;

    if (*first == nullptr) {
        *first = newNode;
        return;
    }

    NodeT *cursor = *first;
    while (cursor != nullptr && cursor->next != nullptr) {
        cursor = cursor->next;
    }


    cursor->next = newNode;
}

void sortList(NodeT **first) {
    int len = 0;
    NodeT *cursor = *first;
    while (cursor != nullptr) {
        cursor = cursor->next;
        len++;
    }
    // A - B - C - D
    // A - C - B - D
    // --------
    //     ----
    //     ---------

    //Sorts by exchanging values but above in comment there's illustrated how to sort by swapping acutal elements
    for (int i = 0; i < len; i++) {
        cursor = *first;
        NodeT *prev = nullptr;
        for (int j = 0; j < len-i; j++) {
            if (prev != nullptr && prev->key > cursor->key) {
                int temp = prev->key;
                prev->key = cursor->key;
                cursor->key = temp;
            }
            prev = cursor;
            cursor = cursor->next;
        }
    }

}

int main() {
    NodeT *first = nullptr;
    push(&first, 2);
    push(&first, 8);
    push(&first, 9);
    push(&first, 21);
    push(&first, 11);
    push(&first, 5);
    push(&first, 34);
    push(&first, 3);
    push(&first, 2);

    sortList(&first);

    //List is leaked but whatevs
    while (first != nullptr) {
        printf("%d ", first->key);
        first = first->next;
    }
    printf("\n");

    return 0;
}
