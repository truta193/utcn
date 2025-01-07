#include <iostream>
#include "bst.h"

int main() {
    bstNodeT *root = nullptr;
    root = bstNodeInsert(root, 5);
    bstNodeInsert(root, 3);
    bstNodeInsert(root, 7);
    bstNodeInsert(root, 1);
    bstNodeInsert(root, 2);
    bstNodeInsert(root, 4);
    bstNodeInsert(root, 4);
    bstNodeInsert(root, 6);
    bstNodeInsert(root, 9);
    bstNodeInsert(root, 8);
    //bstDeleteKey(root, 7);

    bstPrintInorder(root);

    bstNodeT *test = nullptr;
    test = bstSearchKey(root, 5);
    printf("\n%p %d\n", test, test->key);
    //printf("min for key %d: %d\n", 7, bstFindMin(bstSearchKey(root, 7))->key);
    printf("min for key %d: %d\n", 3, bstFindMax(bstSearchKey(root, 3))->key);
    printf("pred for key %d: %d\n", 2, bstFindPredecessor(bstSearchKey(root, 2))->key);
    printf("succ for key %d: %d\n", 6, bstFindSuccessor(bstSearchKey(root, 6))->key);


    return 0;
}
