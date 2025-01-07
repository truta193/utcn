#include <iostream>
#include "MultiwayTree.h"

MultiwayTree *createMultiwayTree(int rootValue) {
    MultiwayTree *multiwayTree = (MultiwayTree *) malloc(sizeof(MultiwayTree));
    multiwayTree->root = (Node2 *) malloc(sizeof(Node2));
    multiwayTree->root->value = rootValue;
    multiwayTree->root->numberOfChildren = 0;
    multiwayTree->root->children = nullptr;
    return multiwayTree;
}

void destroyMultiwayTree(Node2 *root) {
    if (root == nullptr) {
        return;
    }

    if (root->numberOfChildren == 0) {
        free(root);
        return;
    }

    for (int i = 0; i < root->numberOfChildren; ++i) {
        destroyMultiwayTree(root->children[i]);
    }
};


void addChild(Node2 *parent, int childValue) {
    //Not necessairly efficient to reallocate memory for every child but it's easier to implement
    parent->children = (Node2 **) realloc(parent->children, sizeof(Node2 *) * (parent->numberOfChildren + 1));
    parent->children[parent->numberOfChildren] = (Node2 *) malloc(sizeof(Node2));
    parent->children[parent->numberOfChildren]->value = childValue;
    parent->children[parent->numberOfChildren]->numberOfChildren = 0;
    parent->children[parent->numberOfChildren]->children = nullptr;
    parent->numberOfChildren++;
}

void printMultiwayTree(Node2 *root, int indent) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        std::cout << "  ";
    }
    std::cout << root->value << std::endl;
    for (int i = 0; i < root->numberOfChildren; i++) {
        printMultiwayTree(root->children[i], indent + 1);
    }
};
