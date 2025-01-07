#include <cstdlib>
#include <iostream>
#include "BinaryTree.h"


BinaryTree *createBinaryTree() {
    BinaryTree *binaryTree = (BinaryTree *) malloc(sizeof(BinaryTree));
    binaryTree->root = (Node3 *) calloc(1, sizeof(Node3));
    return binaryTree;
};

void destroyBinaryTree(Node3 *root) {
    if (root == nullptr) {
        return;
    }

    destroyBinaryTree(root->leftChild);
    destroyBinaryTree(root->rightBrother);
    free(root);

};

void printBinaryTree(Node3 *root, int indent) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        std::cout << "  ";
    }
    std::cout << root->value << std::endl;
    printBinaryTree(root->leftChild, indent + 1);
    printBinaryTree(root->rightBrother, indent);
}
