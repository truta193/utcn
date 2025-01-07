#include "bst.h"
#include <cstdio>
#include <cstdlib>

bstNodeT *bstNodeCreate(bstNodeT *parent, int key) {
    bstNodeT *node = nullptr;
    node = (bstNodeT *) malloc(sizeof(bstNodeT));
    if (node == nullptr) {
        return nullptr;
    }

    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = parent;

    return node;

};

bstNodeT *bstNodeInsert(bstNodeT *root, int key) {
    if (root == nullptr) {
        bstNodeT *newRoot = bstNodeCreate(nullptr, key);
        return newRoot;
    }

    bstNodeT *node = root;
    bstNodeT *nodeParent = node->parent;

    while (node != nullptr) {
        nodeParent = node;
        if (node->key > key) {
            node = node->left;
        } else if (node->key < key) {
            node = node->right;
        } else {
            return node;
        }
    }

    bstNodeT *newNode = bstNodeCreate(nodeParent, key);

    if (nodeParent->key > key) {
        nodeParent->left = newNode;
    } else {
        nodeParent->right = newNode;
    }

    return newNode;

};

void bstPrintPreorder(bstNodeT *node) {
    if (node == nullptr)
        return;

    printf("%d ", node->key);
    bstPrintPreorder(node->left);
    bstPrintPreorder(node->right);
};

void bstPrintInorder(bstNodeT *node) {
    if (node == nullptr)
        return;

    bstPrintInorder(node->left);
    printf("%d ", node->key);
    bstPrintInorder(node->right);

};

void bstPrintPostorder(bstNodeT *node) {
    if (node == nullptr)
        return;

    bstPrintPostorder(node->left);
    bstPrintPostorder(node->right);
    printf("%d ", node->key);
};

bstNodeT *bstSearchKey(bstNodeT *root, int key) {
    bstNodeT *node = root;

    while (node != nullptr) {
        if (node->key > key) {
            node = node->left;
        } else if (node->key < key) {
            node = node->right;
        } else {
            return node;
        }
    }

    return nullptr;
};

bstNodeT *bstFindMin(bstNodeT *node) {
    bstNodeT *prc = node;
    while (prc != nullptr && prc->left != nullptr) {
        prc = prc->left;
    }

    return prc;
};

bstNodeT *bstFindMax(bstNodeT *node) {
    bstNodeT *prc = node;
    while (prc != nullptr && prc->right != nullptr) {
        prc = prc->right;
    }

    return prc;
};

bstNodeT *bstFindPredecessor(bstNodeT *node) {
    if (node != nullptr && node->left != nullptr) {
        return bstFindMax(node->left);
    }

    while (node != nullptr && node->parent != nullptr && node->parent->right != node) {
        node = node->parent;
    }

    return node->parent;

};

bstNodeT *bstFindSuccessor(bstNodeT *node) {
    if (node->right != nullptr) {
        return bstFindMin(node->right);
    }

    while (node != nullptr && node->parent != nullptr && node->parent->left != node) {
        node = node->parent;
    }

    return node->parent;

};

void bstDeleteKey(bstNodeT *root, int key) {
    bstNodeT *node = bstSearchKey(root, key);
    if (node != nullptr && node->left == nullptr && node->right == nullptr) {
        if (node->parent->right == node) {
            node->parent->right = nullptr;
        } else if (node->parent->left == node) {
            node->parent->left = nullptr;
        }
        free(node);
        return;
    }

    if (node != nullptr && node->left == nullptr && node->right != nullptr) {

        if (node->parent->right == node) {
            node->parent->right = node->right;
        } else if (node->parent->left == node) {
            node->parent->left = node->right;
        }

        free(node);
        return;
    }

    if (node != nullptr && node->left != nullptr && node->right == nullptr) {

        if (node->parent->right == node) {
            node->parent->right = node->left;
        } else if (node->parent->left == node) {
            node->parent->left = node->left;
        }

        free(node);
        return;
    }

    if (node != nullptr && node->left != nullptr && node->right != nullptr) {
        bstNodeT *minR = bstFindMin(node->right);
        if (minR->parent->right == minR) {
            minR->parent->right = nullptr;
        } else if (minR->parent->left == minR) {
            minR->parent->left = nullptr;
        }

        node->left->parent = minR;
        node->right->parent = minR;
        minR->left = node->left;
        minR->right = node->right;

        if (node->parent->right == node) {
            node->parent->right = minR;
        } else if (node->parent->left == node) {
            node->parent->left = minR;
        }

        free(node);
        return;
    }

};



