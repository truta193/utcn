#include <iostream>
#include "RedBlackTree.h"
#include "Profiler.h"



using std::cout, std::endl;

//!!!!Red-Black Trees are self-balanced (not perfectly balanced, but good enough)

RBTree* buildTree(int n) {
    RBTree* tree = rbTreeCreate();
    for (int i = 1; i <= n; i++) {
        rbTreeInsert(tree, i, n);
    }
    return tree;
}


void demo() {
    RBTree* tree = buildTree(11);
    cout << "Tree aster building: " << endl;
    rbTreePrint(tree, tree->root);
    cout << "=======================================" << endl;
    rbDelete(tree, 4, 11);
    rbDelete(tree, 5, 11);
    cout << "Tree after deleting 4 and 5: " << endl;
    rbTreePrint(tree, tree->root);
    cout << "=======================================" << endl;
    cout << "OSSelect for rank 2, 6, 3: ";
    cout << rbSelect(tree, tree->root, 2, 11)->key << ", ";
    cout << rbSelect(tree, tree->root, 6, 11)->key << ", ";
    cout << rbSelect(tree, tree->root, 3, 11)->key << endl;
}


int main() {
    demo();

    //report();
    return 0;
}
