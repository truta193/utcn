#include <iostream>

#include "BinTree.h"
#include "QuickSort.h"

void demo() {
    Node *root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(7);
    root->left->left = createNode(2);
    root->left->right = createNode(4);
    root->right->left = createNode(6);
    root->right->right = createNode(8);

    //GO TO BinTree.cpp and uncomment the std::cout line in traversals
    std::cout << "Recursive traversal: " << std::endl;
    traverseTreeRecursively(root, 8);
    std::cout << "Iterative traversal: " << std::endl;
    traverseTreeIteratively(root, 8);

    int arr[] = {5, 3, 7, 2, 4, 6, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Array before sorting: " << std::endl;
    for (int i = 0; i < size; i++) {
        //std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    hybridQuickSort(arr, 0, size - 1, size, "comp", "assign");
    std::cout << "Array after sorting: " << std::endl;
    for (int i = 0; i < size; i++) {
        //std::cout << arr[i] << " ";
    }
}

int main() {
    //reportTree();

    report();
    demo();
    return 0;
}