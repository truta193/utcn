#include <iostream>
#include <cstdio>
#include "tree.h"

int main() {
    FILE *fin = fopen("date.in", "r");
    if (fin == nullptr) {
        std::cout << "cannot open file" << std::endl;
        return -1;
    }

    treeNodeT *root = nullptr;
    root = treeCreate(fin);

    treePrintPreorder(root);
    printf("\n");
    treePrintInorder(root);
    printf("\n");
    treePrintPostorder(root);
    printf("\n");

    printf("Tree Height: %d\n", treeGetHeight(root));
    printf("Tree Diameter: %d\n", treeGetDiamater(root));
    printf("Tree leaf count: %d\n", treeGetLeafCount(root));
    printf("Tree internal node count: %d\n", treeGetInternalNodeCount(root));
    treeNodeT *n = nullptr;
    n = treeSearchKey(root, 4);
    if (n == nullptr)
        printf("n si null\n");
    else
        printf("Node searched for: %p, %d\n", n, n->key);


    printf("Node height: %d\n", treeGetNodeLevel(root, n));

    FILE *ff = fopen("bal.in", "r");
    treeNodeT *balRoot = nullptr;
    balRoot = treeBalancedCreate(ff);

    treePrintInorder(balRoot);

    return 0;
}
