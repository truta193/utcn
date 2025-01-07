#include "DisjointSet.h"

#include <iostream>
using std::cout, std::endl;

DisjointSet::DisjointSet(Profiler *profiler, int size) {
    this->profiler = profiler;
    this->size = size;
    nodes = new Node* [size];
    for (int i = 0; i < size; i++) {
        nodes[i] = nullptr;
    }
}

void DisjointSet::makeSet(int key, char *assignOp, int n) {
    Node* node = new Node;
    node->key = key;
    node->parent = node;
    node->rank = 0;
    this->profiler->countOperation(assignOp, n, 1);
    nodes[key] = node;
}

int DisjointSet::findSet(int key, char *assignOp, char *compOp, int n) {
    this->profiler->countOperation(assignOp, n, 1);
    Node* node = nodes[key];
    this->profiler->countOperation(compOp, n, 1);
    if (node == nullptr) {
        return -1;
    }
    this->profiler->countOperation(compOp, n, 1);
    if (node->parent == node) {
        return node->key;
    }
    this->profiler->countOperation(assignOp, n, 1);
    node->parent = nodes[findSet(node->parent->key, assignOp, compOp, n)];
    return node->parent->key;
}

void
DisjointSet::unionSets(int key1, int key2, char *assignOp, char *compOp, int n, char *findCompOp, char *findAssignOp) {
    int root1 = findSet(key1, findAssignOp, findCompOp, n);
    int root2 = findSet(key2, findAssignOp, findCompOp, n);
    if (root1 == -1 || root2 == -1) {
        return;
    }
    if (root1 == root2) {
        return;
    }
    this->profiler->countOperation(assignOp, n, 2);
    Node* node1 = nodes[root1];
    Node* node2 = nodes[root2];
    this->profiler->countOperation(compOp, n, 1);
    if (node1->rank < node2->rank) {
        this->profiler->countOperation(assignOp, n, 1);
        node1->parent = node2;
    }
    else if (node1->rank > node2->rank) {
        this->profiler->countOperation(compOp, n, 1);
        this->profiler->countOperation(assignOp, n, 1);
        node2->parent = node1;
    }
    else {
        this->profiler->countOperation(compOp, n, 1);
        this->profiler->countOperation(assignOp, n, 1);
        node2->parent = node1;
        node1->rank++;
    }
}

void DisjointSet::printSet(int key) {


    Node* node = nodes[key];
    std::cout << "Set of " << key << ": ";
    while (node != node->parent) {
        node = node->parent;
    }
    std::cout << node->key;
    std::cout << std::endl;
}
void DisjointSet::printAllSets() {
    for (int i = 0; i < size; i++) {
        printSet(i);
    }
}

int DisjointSet::getSize() {
    return size;
}