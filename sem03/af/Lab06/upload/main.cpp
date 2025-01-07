#include <iostream>
#include "MultiwayTree.h"
#include "ParentVectorTree.h"
#include "BinaryTree.h"

using std::cout, std::endl;


MultiwayTree *T1(ParentVectorTree *parentVectorTree) {
    Node2 *root = nullptr;
    Node2 **nodes = (Node2 **) calloc(parentVectorTree->size, sizeof(Node2 *));
    for (int i = 0; i < parentVectorTree->size; i++) {
        nodes[i] = (Node2 *) malloc(sizeof(Node2));
        nodes[i]->value = i;
        nodes[i]->numberOfChildren = 0;
        nodes[i]->children = nullptr;
    }

    for (int i = 0; i < parentVectorTree->size; i++) {
        if (parentVectorTree->parent[i] == -1) {
            root = nodes[i];
        } else {
            nodes[parentVectorTree->parent[i]]->numberOfChildren++;
        }
    }

    for (int i = 0; i < parentVectorTree->size; i++) {
        if (nodes[i]->numberOfChildren > 0) {
            nodes[i]->children = (Node2 **) malloc(sizeof(Node2 *) * nodes[i]->numberOfChildren);
            nodes[i]->numberOfChildren = 0;
        }
    }

    for (int i = 0; i < parentVectorTree->size; i++) {
        if (parentVectorTree->parent[i] != -1) {
            nodes[parentVectorTree->parent[i]]->children[nodes[parentVectorTree->parent[i]]->numberOfChildren++] = nodes[i];
        }
    }

    MultiwayTree *multiwayTree = (MultiwayTree *) malloc(sizeof(MultiwayTree));
    multiwayTree->root = root;
    return multiwayTree;
}

Node3 *T2helper(Node2 *node) {
    Node3 *result = (Node3 *) calloc(1, sizeof(Node3));
    result->value = node->value;

    if (node->numberOfChildren > 0) {
        result->leftChild = T2helper(node->children[0]);
        Node3 *last = result->leftChild;
        for (int j = 1; j < node->numberOfChildren; j++) {
            Node3 *current = T2helper(node->children[j]);
            last->rightBrother = current;
            last = current;
        }
    }
    return result;
}

BinaryTree *T2(MultiwayTree *multiwayTree) {
    BinaryTree *binTree = createBinaryTree();
    binTree->root = T2helper(multiwayTree->root);
    return binTree;
}

int main() {
    int arr[9] = {1, 6, 4, 1, 6, 6, -1, 4, 1};
    ParentVectorTree *parentVectorTree = createParentVectorTree(9);
    for (int i = 0; i < 9; ++i) {
        parentVectorTree->parent[i] = arr[i];
    }
    printParentVectorTree(parentVectorTree);
    MultiwayTree *multiwayTree = T1(parentVectorTree);
    //printMultiwayTree(multiwayTree->root);
    BinaryTree *binaryTree = T2(multiwayTree);
    //printBinaryTree(binaryTree->root);


    return 0;
}
