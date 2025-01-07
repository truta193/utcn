#include "RedBlackTree.h"

#include <iostream>
#include <ostream>
#include <string>
#include "Profiler.h"

using std::cout, std::endl, std::string;

Profiler profiler("OS_RB_TREE");

RBTree *rbTreeCreate() {
    RBTree *tree = (RBTree *) calloc(1, sizeof(RBTree));
    if (!tree) return nullptr;
    tree->nil = nodeCreate(-1);
    tree->root = tree->nil;
    return tree;
};


Node *nodeCreate(int key) {
    Node *node = (Node *) calloc(1, sizeof(Node));
    if (node == nullptr) return nullptr;

    node->size = 1;
    node->key = key;
    return node;
}


void leftRotate(RBTree *tree, Node *node, char *assignOp, char *compOp, int n) {
    Node *y = node->right;
    profiler.countOperation(assignOp, n, 1);
    node->right = y->left;
    if (y->left != tree->nil) {
        profiler.countOperation(assignOp, n, 1);
        profiler.countOperation(compOp, n, 1);
        y->left->parent = node;
    }
    profiler.countOperation(assignOp, n, 1);

    y->parent = node->parent;
    if (node->parent == tree->nil) {
        profiler.countOperation(assignOp, n, 1);
        profiler.countOperation(compOp, n, 1);
        tree->root = y;
    } else if (node == node->parent->left) {
        profiler.countOperation(assignOp, n, 1);
        profiler.countOperation(compOp, n, 1);
        node->parent->left = y;
    } else {
        profiler.countOperation(assignOp, n, 1);
        node->parent->right = y;
    }
    profiler.countOperation(assignOp, n, 2);
    y->left = node;
    node->parent = y;

    y->size = node->size;
    node->size = 1 + SIZE(tree, node->left) + SIZE(tree, node->right);
}

void rightRotate(RBTree *tree, Node *node, char *assignOp, char *compOp, int n) {
    Node *y = node->left;
    profiler.countOperation(assignOp, n, 1);
    node->left = y->right;
    if (y->right != tree->nil) {
        profiler.countOperation(assignOp, n, 1);
        profiler.countOperation(compOp, n, 1);
        y->right->parent = node;
    }
    profiler.countOperation(assignOp, n, 1);
    y->parent = node->parent;
    if (node->parent == tree->nil) {
        profiler.countOperation(compOp, n, 1);
        profiler.countOperation(assignOp, n, 1);
        tree->root = y;
    } else if (node == node->parent->right) {
        profiler.countOperation(compOp, n, 1);
        profiler.countOperation(assignOp, n, 1);
        node->parent->right = y;
    } else {
        profiler.countOperation(assignOp, n, 1);
        node->parent->left = y;
    }
    profiler.countOperation(assignOp, n, 2);

    y->right = node;
    node->parent = y;
    node->size = y->size;
    y->size = 1 + SIZE(tree, y->left) + SIZE(tree, y->right);
}


void rbTreeValidator(RBTree *tree, Node *node, int n) {
    Node *uncle = tree->nil;
    while (node->parent != tree->nil && node->parent->color == RED) {
        profiler.countOperation("insert_comp", n, 1);
        if (node->parent == node->parent->parent->right) {
            profiler.countOperation("insert_comp", n, 1);
            profiler.countOperation("insert_assig", n, 1);
            uncle = node->parent->parent->left;
            if (uncle != tree->nil && uncle->color == RED) {
                profiler.countOperation("insert_comp", n, 1);
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                profiler.countOperation("insert_assig", n, 1);
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    profiler.countOperation("insert_comp", n, 1);
                    profiler.countOperation("insert_assig", n, 1);
                    node = node->parent;
                    rightRotate(tree, node, "insert_assig", "insert_comp", n);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(tree, node->parent->parent, "insert_assig", "insert_comp", n);
            }
        } else {
            profiler.countOperation("insert_assig", n, 1);
            uncle = node->parent->parent->right;
            if (uncle != tree->nil && uncle->color == RED) {
                profiler.countOperation("insert_comp", n, 1);
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                profiler.countOperation("insert_assig", n, 1);
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    profiler.countOperation("insert_comp", n, 1);
                    profiler.countOperation("insert_assig", n, 1);
                    node = node->parent;
                    leftRotate(tree, node, "insert_assig", "insert_comp", n);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(tree, node->parent->parent, "insert_assig", "insert_comp", n);
            }
        }
    }
    tree->root->color = BLACK;
}


void rbTreeInsert(RBTree *tree, int key, int n) {
    Node *newNode = nodeCreate(key);
    if (!newNode || tree == nullptr) return;


    Node *y = tree->nil;
    Node *x = tree->root;

    while (x != tree->nil) {
        profiler.countOperation("insert_comp", n, 1);
        profiler.countOperation("insert_assig", n, 1);
        y = x;
        // If we pass thorugh it, it means it's gonna have another descendand somewhere in it's subtree
        y->size++;
        if (newNode->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
        profiler.countOperation("insert_assig", n, 1);

    }
    profiler.countOperation("insert_assig", n, 1);
    newNode->parent = y;
    if (y == tree->nil) {
        profiler.countOperation("insert_assig", n, 1);
        tree->root = newNode;
    } else if (newNode->key < y->key) {
        profiler.countOperation("insert_assig", n, 1);
        y->left = newNode;
    } else {
        profiler.countOperation("insert_assig", n, 1);
        y->right = newNode;
    }

    profiler.countOperation("insert_assig", n, 2);

    newNode->left = tree->nil;
    newNode->right = tree->nil;
    newNode->color = RED;

    rbTreeValidator(tree, newNode, n);
};


Node *rbFind(RBTree *tree, Node *node, int key, int n) {
    if (node == tree->nil || node->key == key) {
        profiler.countOperation("delete_comp", n, 1);
        return node;
    }

    if (key < node->key) {
        return rbFind(tree, node->left, key, n);
    } else {
        return rbFind(tree, node->right, key, n);
    }
}

Node *rbMinimum(RBTree *tree, Node *node, int n) {
    while (node->left != tree->nil) {
        profiler.countOperation("delete_comp", n, 1);
        profiler.countOperation("delete_assign", n, 1);
        node = node->left;
    }
    return node;
}

Node *rbSuccessor(RBTree *tree, Node *node, int n) {
    if (node->right != tree->nil) {
        profiler.countOperation("delete_comp", n, 1);
        return rbMinimum(tree, node->right, n);
    }
    Node *y = node->parent;
    while (y != tree->nil && node == y->right) {
        profiler.countOperation("delete_comp", n, 1);
        profiler.countOperation("delete_assign", n, 2);
        node = y;
        y = y->parent;
    }
    return y;
}

void rbDeleteFixup(RBTree *tree, Node *node, int n) {
    while (node != tree->root && node->color == BLACK) {
        profiler.countOperation("delete_comp", n, 1);
        if (node == node->parent->left) {
            profiler.countOperation("delete_comp", n, 1);
            Node *brother = node->parent->right;
            if (brother->color == RED) {
                brother->color = BLACK;
                node->parent->color = RED;
                leftRotate(tree, node->parent, "delete_assign", "delete_comp", n);
                profiler.countOperation("delete_assign", n, 1);
                brother = node->parent->right;
            }
            if (brother->left->color == BLACK && brother->right->color == BLACK) {
                brother->color = RED;
                profiler.countOperation("delete_assign", n, 1);
                node = node->parent;
            } else {
                if (brother->right->color == BLACK) {
                    brother->left->color = BLACK;
                    brother->color = RED;
                    rightRotate(tree, brother, "delete_assign", "delete_comp", n);
                    profiler.countOperation("delete_assign", n, 1);
                    brother = node->parent->right;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->right->color = BLACK;
                leftRotate(tree, node->parent, "delete_assign", "delete_comp", n);
                profiler.countOperation("delete_assign", n, 1);
                node = tree->root;
            }
        } else {
            Node *brother= node->parent->left;
            if (brother->color == RED) {
                brother->color = BLACK;
                node->parent->color = RED;
                rightRotate(tree, node->parent, "delete_assign", "delete_comp", n);
                profiler.countOperation("delete_assign", n, 1);
                brother = node->parent->left;
            }
            if (brother->right->color == BLACK && brother->left->color == BLACK) {
                brother->color = RED;
                profiler.countOperation("delete_assign", n, 1);
                node = node->parent;
            } else {
                if (brother->left->color == BLACK) {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    leftRotate(tree, brother, "delete_assign", "delete_comp", n);
                    profiler.countOperation("delete_assign", n, 1);
                    brother = node->parent->left;
                }
                brother->color = node->parent->color;
                node->parent->color = BLACK;
                brother->left->color = BLACK;
                rightRotate(tree, node->parent, "delete_assign", "delete_comp", n);
                profiler.countOperation("delete_assign", n, 1);
                node = tree->root;
            }
        }
    }
    node->color = BLACK;
}

void rbDelete(RBTree *tree, int key, int n) {
    Node *target = rbFind(tree, tree->root, key, n);
    Node *y = tree->nil;
    Node *x = tree->nil;

    if (target == tree->nil) {
        profiler.countOperation("delete_comp", n, 1);
        return;
    }

    if (target->left == tree->nil || target->right == tree->nil) {
        profiler.countOperation("delete_comp", n, 1);
        profiler.countOperation("delete_assign", n, 1);
        y = target;
    } else {
        y = rbSuccessor(tree, target, n);
    }

    if (y->left != tree->nil) {
        profiler.countOperation("delete_comp", n, 1);
        profiler.countOperation("delete_assign", n, 1);
        x = y->left;
    } else {
        profiler.countOperation("delete_assign", n, 1);
        x = y->right;
    }

    profiler.countOperation("delete_assign", n, 1);
    x->parent = y->parent;

    if (y->parent == tree->nil) {
        profiler.countOperation("delete_comp", n, 1);
        profiler.countOperation("delete_assign", n, 1);
        tree->root = x;
    } else if (y == y->parent->left) {
        profiler.countOperation("delete_comp", n, 1);
        profiler.countOperation("delete_assign", n, 1);
        y->parent->left = x;
    } else {
        profiler.countOperation("delete_assign", n, 1);
        y->parent->right = x;
    }

    if (y != target) {
        profiler.countOperation("delete_comp", n, 1);
        profiler.countOperation("delete_assign", n, 1);
        target->key = y->key;
    }

    //Update sizes
    Node *temp = y->parent;
    while (temp != tree->nil) {
        profiler.countOperation("delete_comp", n, 1);

        temp->size--;
        profiler.countOperation("delete_assign", n, 1);
        temp = temp->parent;
    }

    if (y->color == BLACK) {
        rbDeleteFixup(tree, x, n);
    }


}

void rbTreePrint(RBTree *tree, Node *root, std::string indent, bool last) {
    if (root != tree->nil) {
        cout << indent;
        indent += "    ";
        cout << root->key << "," << root->size << endl;
        rbTreePrint(tree, root->left, indent, false);
        rbTreePrint(tree, root->right, indent, true);
    }
}

Node *rbSelect(RBTree *tree, Node *node, int rank, int n) {
    if (node == tree->nil) return nullptr;

    const int leftSize = node->left != tree->nil ? node->left->size  : 0;

    if (rank == leftSize + 1) {
        profiler.countOperation("Select Total", n, 1);
        return node;
    } else if (rank < leftSize + 1) {
        profiler.countOperation("Select Total", n, 1);
        return rbSelect(tree, node->left, rank, n);
    } else {
        return rbSelect(tree, node->right, rank - leftSize - 1, n);
    }

}

void report() {
    srand(time(NULL));
    for (int i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
        cout << "i = " << i << endl;
        for (int j = 0; j < NR_TESTS; j++) {
            RBTree *tree = rbTreeCreate();
            //Build tree function basically, just insert, it's self-balanced
            for (int k = 1; k <= i; k++) {
                rbTreeInsert(tree, k, i);
            }
            int nrElementsToDelete = i;
            int nrElementsToSelect = i;

            for (int k = 0; k < i; k++) {
                int toSelect = rand() % nrElementsToSelect + 1;
                nrElementsToSelect--;
                int toDelete = rand() % nrElementsToDelete + 1;
                nrElementsToDelete--;
                //cout << nrElementsToSelect << ", " << toSelect << endl;
                rbSelect(tree, tree->root, toSelect, i);
                rbDelete(tree, toDelete, i);
            }
        }
    }


    profiler.addSeries("Build total", "insert_comp", "insert_assig");
    profiler.divideValues("Build total", NR_TESTS);
    profiler.divideValues("Select Total", NR_TESTS);
    profiler.addSeries("Delete total", "delete_comp", "delete_assign");
    profiler.divideValues("Delete total", NR_TESTS);
    profiler.showReport();
}
