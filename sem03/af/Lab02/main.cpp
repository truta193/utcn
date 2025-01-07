#include <iostream>
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP 100
#define NR_TESTS 5

Profiler profiler("Dummy");

typedef struct _Heap {
    int *array;
    int size;
    int allocatedSize;
} Heap;

int getLeftChild(int index) {
    return 2 * index + 1;
}

int getRightChild(int index) {
    return 2 * index + 2;
}

int getParent(int index) {
    return (index - 1) / 2;
}

//Max heapify
//Heapify max
void maxHeapify(Heap heap, int i) {
    profiler.createOperation("maxHeapifyComp", heap.size);
    profiler.createOperation("maxHeapifyAsig", heap.size);

    int largest = i;
    int left = getLeftChild(i);
    int right = getRightChild(i);

    profiler.countOperation("maxHeapifyComp", heap.size);
    if (left < heap.size && heap.array[left] > heap.array[largest]) {
        largest = left;
    }
    profiler.countOperation("maxHeapifyComp", heap.size);
    if (right < heap.size && heap.array[right] > heap.array[largest]) {
        largest = right;
    }

    if (largest != i) {
        profiler.countOperation("maxHeapifyAsig", heap.size, 3);
        int temp = heap.array[i];
        heap.array[i] = heap.array[largest];
        heap.array[largest] = temp;
        maxHeapify(heap, largest);
    }
}

//Min heapify
void minHeapify(Heap heap, int i) {
    profiler.createOperation("minHeapifyComp", heap.size);
    profiler.createOperation("minHeapifyAsig", heap.size);

    int largest = i;
    int left = getLeftChild(i);
    int right = getRightChild(i);

    profiler.countOperation("minHeapifyComp", heap.size);
    if (left < heap.size && heap.array[left] < heap.array[largest]) {
        largest = left;
    }
    profiler.countOperation("minHeapifyComp", heap.size);
    if (right < heap.size && heap.array[right] < heap.array[largest]) {
        largest = right;
    }

    if (largest != i) {
        profiler.countOperation("minHeapifyAsig", heap.size, 3);
        int temp = heap.array[i];
        heap.array[i] = heap.array[largest];
        heap.array[largest] = temp;
        minHeapify(heap, largest);
    }
}

//Bottom-up build heap
void buildHeapBottomUp(Heap heap) {
    for (int i = heap.size / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, i);
        //minHeapify(heap, i);
    }
}

//Top-down build heap
void buildHeapTopDown(Heap heap) {
    profiler.createOperation("topdownComp", heap.size);
    profiler.createOperation("topdownAsig", heap.size);
    for (int i = 1; i < heap.size; i++) {
        int parent = getParent(i);
        int child = i;

        while (parent >= 0 && heap.array[parent] < heap.array[child]) {
            profiler.countOperation("topdownComp", heap.size);
            profiler.countOperation("topdownAsig", heap.size, 3);
            int temp = heap.array[parent];
            heap.array[parent] = heap.array[child];
            heap.array[child] = temp;

            child = parent;
            parent = getParent(child);
        }
        //When condition is false, it still counts the operation
        profiler.countOperation("topdownComp", heap.size);

    }
}


void demoBuildHeapBU() {
    Heap heap{
            .array = new int[5]{7, 8, 4, 10, 5},
            .size = 5
    };

    buildHeapBottomUp(heap);

    for (int i = 0; i < heap.size; i++) {
        std::cout << heap.array[i] << " ";
    }

    free(heap.array);
}

void demoBuildHeapTD() {
    Heap heap{
            .array = new int[5]{7, 8, 4, 10, 5},
            .size = 5
    };

    buildHeapTopDown(heap);

    for (int i = 0; i < heap.size; i++) {
        std::cout << heap.array[i] << " ";
    }

    free(heap.array);
}

void testAverageCases() {
    profiler.reset("Average Case");

    for (int i = STEP; i <= MAX_SIZE; i += STEP) {
        for (int j = 0; j < NR_TESTS; j++) {
            Heap heap1{
                    .array = new int[i],
                    .size = i
            };
            Heap heap2{
                    .array = new int[i],
                    .size = i
            };
            FillRandomArray(heap1.array, heap1.size, 10, 50000, false);
            memcpy(heap2.array, heap1.array, sizeof(int) * heap1.size);
            buildHeapBottomUp(heap1);
            buildHeapTopDown(heap2);
            free(heap1.array);
            free(heap2.array);
        }

    }

    profiler.divideValues("maxHeapifyComp", NR_TESTS);
    profiler.divideValues("maxHeapifyAsig", NR_TESTS);
    profiler.divideValues("topdownComp", NR_TESTS);
    profiler.divideValues("topdownAsig", NR_TESTS);

    profiler.createGroup("Comparisons", "maxHeapifyComp", "topdownComp");
    profiler.createGroup("Assignments", "maxHeapifyAsig", "topdownAsig");
    profiler.addSeries("Bottom-up", "maxHeapifyComp", "maxHeapifyAsig");
    profiler.addSeries("Top-down", "topdownComp", "topdownAsig");
    profiler.createGroup("Total", "Bottom-up", "Top-down");
    profiler.showReport();
}

void testWorstCase() {
    profiler.reset("Worst Case");

    for (int i = STEP; i <= MAX_SIZE; i += STEP) {
        Heap heap1{
                .array = new int[i],
                .size = i
        };
        Heap heap2{
                .array = new int[i],
                .size = i
        };
        //Bottom-up worst case is an ascending array
        FillRandomArray(heap1.array, heap1.size, 10, 50000, false, ASCENDING);
        memcpy(heap2.array, heap1.array, sizeof(int) * heap1.size);
        buildHeapBottomUp(heap1);
        buildHeapTopDown(heap2);
        free(heap1.array);
        free(heap2.array);

    }

    profiler.createGroup("Worst Case Comparisons", "maxHeapifyComp", "topdownComp");
    profiler.createGroup("Worst Case Assignments", "maxHeapifyAsig", "topdownAsig");
    profiler.addSeries("Bottom-up", "maxHeapifyComp", "maxHeapifyAsig");
    profiler.addSeries("Top-down", "topdownComp", "topdownAsig");
    profiler.createGroup("Worst Case Total", "Bottom-up", "Top-down");
    profiler.showReport();
}

void heapSort(Heap heap) {

    buildHeapBottomUp(heap);
    for (int i = heap.size - 1; i >= 0; i--) {
        int temp = heap.array[0];
        heap.array[0] = heap.array[i];
        heap.array[i] = temp;
        heap.size--;
        maxHeapify(heap, 0);
    }
}

int main() {
    Heap heap = {
            .array = new int[10]{4, 1, 3, 2, 16, 9, 10, 14, 8, 7},
            .size = 10,
            .allocatedSize = 10
    };

    heapSort(heap);

    for (int i = 0; i < 10; i++) {
        std::cout << heap.array[i] << " ";
    }
    std::cout << std::endl;

//    testWorstCase();
//    testAverageCases();

    std::cout << std::endl;
    demoBuildHeapBU();
    std::cout << std::endl;
    demoBuildHeapTD();

    return 0;
}