#pragma once

typedef struct Node {
    int key;
    struct Node* parent;
    int rank;
} Node;
