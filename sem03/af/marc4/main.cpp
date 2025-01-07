#include <iostream>
#include "Profiler.h"

using namespace std;

Profiler profiler("L4 First Report");

const char* k1Assigns = "k1Assigns";
const char* k1Comps = "k1Comps";
const char* k2Assigns = "k2Assigns";
const char* k2Comps = "k2Comps";
const char* k3Assigns = "k3Assigns";
const char* k3Comps = "k3Comps";

struct Node {
    int key;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
};

struct Heap {
    Node** array;
    int size;
    int maxSize;
};

int getLeftChild(int pos) {
    return 2 * pos + 1;
}

int getRightChild(int pos) {
    return 2 * pos + 2;
}

Node* createNode(int key) {
    Node* node = new Node;

    if (node != nullptr) {
        node->key = key;
        node->next = nullptr;
    }

    return node;
}

List* createList() {
    List* list = new List;

    if (list != nullptr) {
        list->head = nullptr;
        list->tail = nullptr;
    }

    return list;
}

Heap* createHeap(int maxSize) {
    Heap* heap = new Heap;

    if (heap != nullptr) {
        heap->maxSize = maxSize;
        heap->size = 0;
        heap->array = new Node*[maxSize];
    }

    return heap;
}

void addNode(List* list, int key) {
    if (list == nullptr) {
        return;
    }

    Node* node = createNode(key);

    if (node == nullptr) {
        return;
    }

    if (list->tail == nullptr) {
        list->head = node;
        list->tail = node;
    }
    else if (list->head == list->tail) {
        list->tail->next = node;
        list->tail = list->tail->next;
    }
    else {
        list->tail->next = node;
        list->tail = list->tail->next;
    }
}

void insertHeap(Heap* heap, Node* node) {

}

void printList(List* list) {
    if (list == nullptr) {
        return;
    }

    Node* currentNode = list->head;

    while (currentNode != nullptr) {
        cout << currentNode->key << " ";
        currentNode = currentNode->next;
    }

    cout << endl;
}

void prettyPrintList(Node* pos, int level = 0) {
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }

    cout << pos->key << endl;
    Node* left = pos;
    for (int i = 0; i < 2 * level - 1; i++) {
        left = left != nullptr ? left->next : nullptr;
    }
    left = left != nullptr ? left->next : nullptr;
    Node* right = left != nullptr ? left->next : nullptr;

    if (left != nullptr) {
        prettyPrintList(left, level + 1);
    }
    if (right != nullptr) {
        prettyPrintList(right, level + 1);
    }
}

void prettyPrintArray(Node** array, int size, int pos, int level = 0) {
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << array[pos]->key << endl;
    int l = getLeftChild(pos);
    int r = getRightChild(pos);
    if (l < size) {
        prettyPrintArray(array, size, l, level + 1);
    }
    if (r < size) {
        prettyPrintArray(array, size, r, level + 1);
    }
}

void deleteList(List* list) {
    if (list == nullptr) {
        return;
    }

    Node* prevNode = nullptr;
    Node* currentNode = list->head;

    while (currentNode != nullptr) {
        prevNode = currentNode;
        currentNode = currentNode->next;

        prevNode = nullptr;
        delete prevNode;
    }

    list->head = nullptr;
    list->tail = nullptr;

    delete list;
}

void deleteHeap(Heap* heap) {
    if (heap == nullptr) {
        return;
    }

    delete[] heap->array;

    heap->array = nullptr;

    delete heap;
}

void swapNodesWithNext(Node* &a, Node* &b) {

    Node* tempNext = a->next;
    a->next = b->next;
    b->next = tempNext;

    swap(*a, *b);
}

//void minHeapify(Node* root) {
//    if (root == nullptr) {
//        return;
//    }
//
//    Node* smallest = root;
//    Node* left = smallest->next;
//    Node* right = left != nullptr ? left->next : nullptr;
//
//    if (left != nullptr and left->key < smallest->key) {
//        smallest = left;
//    }
//
//    if (right != nullptr and right->key < smallest->key) {
//        smallest = right;
//    }
//
//    if (smallest != root) {
//        swapNodesWithNext(root, smallest);
//        minHeapify(smallest);
//    }
//}
//
//void buildMinHeap(List* list) {
//    int n = 0;
//    Node* current = list->head;
//
//    while (current != nullptr) {
//        n++;
//        current = current->next;
//    }
//
//    // Start heapify from the last non-leaf node to the first node
//    for (int i = n / 2; i >= 1; i--) {
//        current = list->head;
//        for (int j = 1; j < i; j++) {
//            current = current->next;
//        }
//        minHeapify(current);
//    }
//}

void minHeapify(Node** array, int size, int pos, const char* assignsName, const char* compsName, int opSize) {
    int smallest = pos;
    int l = getLeftChild(pos);
    int r = getRightChild(pos);

    profiler.countOperation(compsName, opSize);
    if (l < size and array[l]->key < array[smallest]->key) {
        smallest = l;
    }

    profiler.countOperation(compsName, opSize);
    if (r < size and array[r]->key < array[smallest]->key) {
        smallest = r;
    }

    if (smallest != pos) {
        profiler.countOperation(assignsName, opSize, 3);
        swap(array[smallest], array[pos]);
        minHeapify(array, size, smallest, assignsName, compsName, opSize);
    }
}

void buildMinHeap(Node** array, int size, const char* assignsName, const char* compsName, int opSize) {
    for (int i = (size - 1) / 2; i >= 0; i--) {
        minHeapify(array, size, i, assignsName, compsName, opSize);
    }
}

List* mergeSortedLists(List** list, int size, const char* assignsName, const char* compsName, int opSize) {
    List* result = createList();

    Heap* heap = createHeap(size);

    for (int i = 0; i < size; i++) {
        profiler.countOperation(assignsName, opSize);
        heap->array[i] = list[i]->head;
        heap->size++;
    }

    buildMinHeap(heap->array, heap->size, assignsName, compsName, opSize);

    while (heap->size > 0) {

        profiler.countOperation(compsName, opSize);
        profiler.countOperation(assignsName, opSize);
        if (result->tail != nullptr) {
            result->tail->next = heap->array[0];
        }
        else {
            result->head = heap->array[0];
        }

        profiler.countOperation(assignsName, opSize, 2);
        result->tail = heap->array[0];
        heap->array[0] = heap->array[0] != nullptr ? heap->array[0]->next : nullptr;

        profiler.countOperation(compsName, opSize);
        if (heap->array[0] == nullptr) {
            profiler.countOperation(assignsName, opSize);
            heap->array[0] = heap->array[heap->size - 1];
            heap->size--;
        }
        if (heap->size > 1) {
            minHeapify(heap->array, heap->size, 0, assignsName, compsName, opSize);
        }
    }

    return result;
}

List* mergeTwoLists(List* listOne, List* listTwo) {

    if (listOne == nullptr or listTwo == nullptr) {
        return nullptr;
    }

    List* list = createList();

    if (list == nullptr) {
        return nullptr;
    }

    Node* pointerOne = listOne->head;
    Node* pointerTwo = listTwo->head;

    while (pointerOne != nullptr and pointerTwo != nullptr) {
        if (pointerOne->key < pointerTwo->key) {
            addNode(list, pointerOne->key);
            pointerOne = pointerOne->next;
        }
        else {
            addNode(list, pointerTwo->key);
            pointerTwo = pointerTwo->next;
        }
    }

    while (pointerOne != nullptr) {
        addNode(list, pointerOne->key);
        pointerOne = pointerOne->next;
    }

    while (pointerTwo != nullptr) {
        addNode(list, pointerTwo->key);
        pointerTwo = pointerTwo->next;
    }

    return list;
}

void printNodeArray(Node** array, int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i]->key << " ";
    }
    cout << endl;
}

void demo() {

    int k = 10;
    const int size = 10;
    int arr[size + 2];

    // generate k lists
    for (int i = 0; i < k; i++) {
        List* list = createList();

        FillRandomArray<int>(arr, size, 0, size + 2, false, 1);

        for (int j = 0; j < size; j++) {
            addNode(list, arr[j]);
        }

        printList(list);

        deleteList(list);
    }

    // merge 2 arrays
    List* listOne = createList();
    List* listTwo = createList();

    cout << "\nMerging two lists:\n";

    FillRandomArray<int>(arr, size, 0, size + 2, false, 1);

    for (int j = 0; j < size; j++) {
        addNode(listOne, arr[j]);
    }

    printList(listOne);

    FillRandomArray<int>(arr, size, 0, size + 2, false, 1);

    for (int j = 0; j < size; j++) {
        addNode(listTwo, arr[j]);
    }

    printList(listTwo);

    List* newList = mergeTwoLists(listOne, listTwo);

    cout << "The merged list is:\n";
    printList(newList);
    cout << endl;

    deleteList(listOne);
    deleteList(listTwo);
    deleteList(newList);

    //// testing minHeapify
    //List* listForHeapify = createList();

    //FillRandomArray<int>(arr, size, 0, size + 2);

    //for (int j = 0; j < size; j++) {
    //    addNode(listForHeapify, arr[j]);
    //}

    //printList(listForHeapify);

    //minHeapify(listForHeapify->head);

    //cout << "List after minHeapify()\n";

    //printList(listForHeapify);

    //deleteList(listForHeapify);

    // testing buildMinHeap
    Heap* heap = createHeap(size);

    FillRandomArray<int>(arr, size, 0, size + 2);

    for (int j = 0; j < size; j++) {
        heap->array[j] = createNode(arr[j]);
        heap->size++;
    }

    printNodeArray(heap->array, heap->size);

    buildMinHeap(heap->array, heap->size, "", "", 0);

    cout << "Array after buildMinHeap()\n";

    printNodeArray(heap->array, heap->size);

    prettyPrintArray(heap->array, heap->size, 0);
    cout << endl;

    deleteHeap(heap);
}

void demoMergeSortedLists() {
    int k = 10;
    const int size = 5;
    int arr[size + 2];

    List** listList = new List*[k];

    cout << "Merging " << k << " ordered lists:\n";

    // generate k lists
    for (int i = 0; i < k; i++) {
        List* list = createList();

        FillRandomArray<int>(arr, size, 0, size + 2, false, 1);

        for (int j = 0; j < size; j++) {
            addNode(list, arr[j]);
        }

        printList(list);

        listList[i] = list;
    }

    cout << "The merged list is:\n";
    List* mergedList = mergeSortedLists(listList, k, "", "", 0);

    printList(mergedList);

    for (int i = 0; i < k; i++) {
        deleteList(listList[i]);
    }

    delete[] listList;
    deleteList(mergedList);
}

void generateReport() {
    const int k1 = 5;
    const int k2 = 10;
    const int k3 = 100;
    const int size = 10000;
    int arr[size + 2];

    /*List** listListK1 = new List * [k1] {};
    List** listListK2 = new List * [k2] {};
    List** listListK3 = new List * [k3] {};*/

    for (int k = 100; k <= 10000; k += 100) {

        List* listListK1[k1];
        List* listListK2[k2];
        List* listListK3[k3];

        cout << "Merging " << k1 << " ordered lists of size " << k <<":\n";

        // generate k1 lists
        for (int i = 0; i < k1; i++) {
            List* list = createList();

            FillRandomArray<int>(arr, k/k1, 0, size + 2, false, 1);

            for (int j = 0; j < k/k1; j++) {
                addNode(list, arr[j]);
            }

            listListK1[i] = list;
        }

        mergeSortedLists(listListK1, k1, k1Assigns, k1Comps, k);

        cout << "Merging " << k2 << " ordered lists of size " << k << ":\n";

        // generate k2 lists
        for (int i = 0; i < k2; i++) {
            List* list = createList();

            FillRandomArray<int>(arr, k/k2, 0, 50000, false, ASCENDING);

            for (int j = 0; j < k/k2; j++) {
                addNode(list, arr[j]);
            }

            listListK2[i] = list;
        }

        mergeSortedLists(listListK2, k2, k2Assigns, k2Comps, k);

        cout << "Merging " << k3 << " ordered lists of size " << k << ":\n";

        // generate k3 lists
        for (int i = 0; i < k3; i++) {
            List* list = createList();

            FillRandomArray<int>(arr, k/k3, 0, size + 2, false, 1);

            for (int j = 0; j < k/k3; j++) {
                addNode(list, arr[j]);
            }

            listListK3[i] = list;
        }

        mergeSortedLists(listListK3, k3, k3Assigns, k3Comps, k);

    }

//    for (int i = 0; i < k1; i++) {
//        deleteList(listListK1[i]);
//    }
//
//    delete[] listListK1;
//
//    for (int i = 0; i < k2; i++) {
//        deleteList(listListK2[i]);
//    }
//
//    delete[] listListK2;
//
//    for (int i = 0; i < k3; i++) {
//        deleteList(listListK3[i]);
//    }
//
//    delete[] listListK3;

    profiler.addSeries("5 Ordered Lists", k1Assigns, k1Comps);
    profiler.addSeries("5 Ordered Lists Comp", k1Assigns, k1Comps);
    profiler.addSeries("10 Ordered Lists", k2Assigns, k2Comps);
    profiler.addSeries("10 Ordered Lists Comp", k2Assigns, k2Comps);
    profiler.addSeries("100 Ordered Lists", k3Assigns, k3Comps);
    profiler.addSeries("100 Ordered Lists Comp", k3Assigns, k3Comps);

    profiler.createGroup("Comparison", "5 Ordered Lists Comp", "10 Ordered Lists Comp", "100 Ordered Lists Comp");

    profiler.reset("L4 Second Report");

    int n = 10000;

    for (int k = 10; k <= 500; k += 10) {
        int listSize = n / k;

        List** listList = new List*[k];

        for (int i = 0; i < k; i++) {
            List* list = createList();

            FillRandomArray<int>(arr, listSize, 0, size + 2, false, 1);

            for (int j = 0; j < listSize; j++) {
                addNode(list, arr[j]);
            }

            listList[i] = list;
        }

        mergeSortedLists(listList, k, "FixedLengthAssigns", "FixedLengthComps", k);

        for (int i = 0; i < k; i++) {
            deleteList(listList[i]);
        }

        delete[] listList;
    }

    profiler.addSeries("FixedLength", "FixedLengthAssigns", "FixedLengthComps");

    profiler.showReport();
}

int main()
{
    List* list = createList();

    addNode(list, 1);
    addNode(list, 2);
    addNode(list, 3);
    addNode(list, 4);

    printList(list);
    cout << endl;

    //demo();
    //demoMergeSortedLists();
    generateReport();
}
