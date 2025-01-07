#include "BinTree.h"

#include <iostream>
#include <ostream>
#include <stdlib.h>
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP 100
#define NR_TESTS 5
#define TIME_TESTS 100

Profiler profiler2("BinaryTree");

Node *createNode(int key) {
    Node *node = nullptr;
    node = (Node *) malloc(sizeof(Node));
    if (!node) return nullptr;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void traverseTreeRecursively(Node *root, int n) {
    profiler2.createOperation("recComp", n);
    profiler2.createOperation("recAssign", n);

    profiler2.countOperation("recComp", n, 1);
    if (root == nullptr) return;


    profiler2.countOperation("recComp", n, 1);
    if (root->left != nullptr) {
        traverseTreeRecursively(root->left, n);
    }

    //std::cout << root->key << std::endl;

    profiler2.countOperation("recComp", n, 1);
    if (root->right != nullptr) {
        traverseTreeRecursively(root->right, n);
    }
}

//Threaded binary tree on the fly
void traverseTreeIteratively(Node *root, int n) {
    profiler2.createOperation("iterComp", n);
    profiler2.createOperation("iterAssign", n);

    profiler2.countOperation("iterComp", n, 1);
    if (root == nullptr) return;
    profiler2.countOperation("iterAssign", n, 1);
    Node *current = root;
    while (current != nullptr) {
        profiler2.countOperation("iterComp", n, 2);
        if (current->left == nullptr) {
            std::cout << current->key << std::endl;
            profiler2.countOperation("iterAssign", n, 1);
            current = current->right;
        } else {
            profiler2.countOperation("iterAssign", n, 1);
            Node *predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current) {
                profiler2.countOperation("iterComp", n, 2);
                profiler2.countOperation("iterAssign", n, 1);
                predecessor = predecessor->right;

            }
            profiler2.countOperation("iterComp", n, 1);
            if (predecessor->right == nullptr) {
                profiler2.countOperation("iterAssign", n, 2);
                predecessor->right = current;
                current = current->left;
            } else {
                profiler2.countOperation("iterAssign", n, 2);
                predecessor->right = nullptr;
                std::cout << current->key << std::endl;
                current = current->right;
            }
        }
    }
}

Node *createLevelOrder(int *arr, int i, int n) {
    Node *root = nullptr;

    if (i < n) {
        root = createNode(arr[i]);
        root->left = createLevelOrder(arr, 2 * i + 1, n);
        root->right = createLevelOrder(arr, 2 * i + 2, n);
    }
    return root;
}

void reportTree() {
    for (int i = STEP; i <= MAX_SIZE; i += STEP) {
        std::cout << "=====================" << i << std::endl;
        for (int test = 0; test < NR_TESTS; test++) {
            int *arr = (int *) malloc(sizeof(int) * i);
            if (!arr) return;
            FillRandomArray(arr, i, 10, 50000, false, UNSORTED);
            Node *root = createLevelOrder(arr, 0, i);

            traverseTreeRecursively(root, i);
            traverseTreeIteratively(root, i);
        }
    }
    for (int i = STEP; i <= MAX_SIZE; i += STEP) {
        std::cout << "=====================" << i << std::endl;
        for (int test = 0; test < TIME_TESTS; test++) {
            int *arr = (int *) malloc(sizeof(int) * i);
            if (!arr) return;
            FillRandomArray(arr, i, 10, 50000, false, UNSORTED);
            Node *root = createLevelOrder(arr, 0, i);

            profiler2.startTimer("trec", i);
            traverseTreeRecursively(root, i);
            profiler2.stopTimer("trec", i);
            profiler2.startTimer("titer", i);
            traverseTreeIteratively(root, i);
            profiler2.stopTimer("titer", i);
        }
    }

    //profiler2.createGroup("trec", "titer");
    profiler2.addSeries("rec", "recComp", "recAssign");
    profiler2.addSeries("iter", "iterComp", "iterAssign");
    profiler2.divideValues("rec", NR_TESTS);
    profiler2.divideValues("iter", NR_TESTS);
    profiler2.createGroup("total", "rec", "iter");
    profiler2.showReport();
}
