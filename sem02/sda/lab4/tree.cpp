#include "tree.h"
#include <cstdlib>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

treeNodeT *createTreeNode(int key) {
    treeNodeT *node = nullptr;
    node = (treeNodeT *) malloc(sizeof(treeNodeT));
    if (node == nullptr) {
        return nullptr;
    }

    node->key = key;
    node->left = nullptr;
    node->right = nullptr;

    return node;

}

treeNodeT *treeCreate(FILE *fin) {
    int key = 0;
    fscanf(fin, "%d", &key);
    if (key == 0) {
        return nullptr;
    }

    treeNodeT *node = nullptr;
    node = createTreeNode(key);
    if (node != nullptr) {
        node->left = treeCreate(fin);
        node->right = treeCreate(fin);
    }
    return node;

};

void deleteTree(treeNodeT **node) {
    treeNodeT *inode = *node;
    if (node == nullptr || *node == nullptr)
        return;

    deleteTree(&inode->left);
    deleteTree(&inode->right);
}

void treePrintPreorder(treeNodeT *node) {
    if (node == nullptr)
        return;

    printf("%d ", node->key);
    treePrintPreorder(node->left);
    treePrintPreorder(node->right);
};

void treePrintInorder(treeNodeT *node) {
    if (node == nullptr)
        return;

    treePrintInorder(node->left);
    printf("%d ", node->key);
    treePrintInorder(node->right);

};

void treePrintPostorder(treeNodeT *node) {
    if (node == nullptr)
        return;

    treePrintPostorder(node->left);
    treePrintPostorder(node->right);
    printf("%d ", node->key);
};

int treeGetHeight(treeNodeT *node) {
    if (node == nullptr) {
        return -1;
    }

    int hLeft = treeGetHeight(node->left);
    int hRight = treeGetHeight(node->right);

    return 1 + MAX(hLeft, hRight);
}

int treeGetDiamater(treeNodeT *node) {
    if (node == nullptr) {
        return 0;
    };

    int hLeft = 0;
    int hRight = 0;
    if (node->left)
        hLeft = treeGetHeight(node->left);
    if (node->right)
        hRight = treeGetHeight(node->right);

    int dLeft = treeGetDiamater(node->left);
    int dRight = treeGetDiamater(node->right);

    return MAX(hLeft + hRight + 2,
               MAX(dLeft, dRight)); //In muchii, +2 pentru muchiile care conecteaza subarborele stang si drept de nod

};

int treeGetLeafCount(treeNodeT *node) {
    if (node == nullptr)
        return 0;
    if (node->left == nullptr && node->right == nullptr)
        return 1;

    return treeGetLeafCount(node->left) + treeGetLeafCount(node->right);
};

int treeGetInternalNodeCount(treeNodeT *node) {
    if (node == nullptr)
        return 0;
    if (node->left == nullptr && node->right == nullptr)
        return 0;

    return 1 + treeGetInternalNodeCount(node->left) + treeGetInternalNodeCount(node->right);

};

treeNodeT *treeSearchKey(treeNodeT *node, int key) {
    if (node == nullptr)
        return nullptr;

    treeNodeT *ret = nullptr;

    if (node->key == key) {
        ret = node;
        return ret;
    }


    ret = treeSearchKey(node->left, key);
    if (ret != nullptr)
        return ret;
    ret = treeSearchKey(node->right, key);
    if (ret != nullptr)
        return ret;

    return ret;

};

int treeGetNodeLevel(treeNodeT *root, treeNodeT *node) {
    int rootHeight = treeGetHeight(root);
    int nodeHeight = treeGetHeight(node);
    return rootHeight - nodeHeight;



//    if (node == nullptr)
//        return -1;
//
//    int hLeft = treeGetKeyHeight(node->left, key);
//    //Daca am gasit nodul nu mai continuam
////    if (node->key == key)
////        return 0;
//
//    int hRight = treeGetKeyHeight(node->right, key);
////    if (node->key == key)
////        return 0;
//
//    return 1 + MAX(hLeft, hRight);

};

static treeNodeT *treeBalancedCreateInternal(FILE *fin, int numberOfNodes) {
    if (numberOfNodes <= 0)
        return nullptr;

    int key = 0;
    fscanf(fin, "%d", &key);
    treeNodeT *node = createTreeNode(key);
    int numberOfLeftNodes = numberOfNodes / 2;
    int numberOfRightNodes = numberOfNodes - numberOfLeftNodes - 1;

    node->left = treeBalancedCreateInternal(fin, numberOfLeftNodes);
    node->right = treeBalancedCreateInternal(fin, numberOfRightNodes);

    return node;

};

treeNodeT *treeBalancedCreate(FILE *fin) {
    int numberOfNodes = 0;
    fscanf(fin, "%d", &numberOfNodes);
    if (numberOfNodes <= 0)
        return nullptr;

    return treeBalancedCreateInternal(fin, numberOfNodes);

}







