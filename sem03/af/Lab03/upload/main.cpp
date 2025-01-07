#include <iostream>
#include <climits>
#include "Profiler.h"

//TODO: WORST CASE NEEDS OTHER QUICKSORT NOT THE QUICKSELECT ONE
#define MAX_SIZE 10000
#define STEP 100
#define NR_TESTS 5

Profiler profiler("Average Case");

//region QuickSort

int getPivot(int *arr, int low, int high, int initialSize) {
    profiler.createOperation("qsComp", initialSize);
    profiler.createOperation("qsAssig", initialSize);

    profiler.countOperation("qsAssig", initialSize, 1);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        profiler.countOperation("qsComp", initialSize, 1);
        if (arr[j] < pivot) {
            i++;
            profiler.countOperation("qsAssig", initialSize, 3);
            std::swap(arr[i], arr[j]);
        }
    }

    profiler.countOperation("qsAssig", initialSize, 3);
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

//Quickselect
int quickSelect(int *arr, int p, int r, int i) {
    if (p == r) {
        return arr[p];
    }

    int q = getPivot(arr, p, r, 1);
    int k = q - p + 1;

    if (k == i) {
        return arr[q];
    } else if (i < k) {
        return quickSelect(arr, p, q - 1, i);
    } else {
        return quickSelect(arr, q + 1, r, i - k);
    }
}

void QuickSort(int* arr, int low, int high, int initialSize) {
    if (low >= high) {
        return;
    }
    profiler.createOperation("qsAssig", initialSize);

    //Random pivot
    srand(time(NULL));
    int i = low + rand() % (high - low);
    profiler.countOperation("qsAssig", initialSize, 3);
    std::swap(arr[i], arr[high]);

    //int p = getPivot(arr, low, high, initialSize);
    int p = getPivot(arr, low, high, initialSize);

    QuickSort(arr, low, p - 1, initialSize);
    QuickSort(arr, p + 1, high, initialSize);
}

void QuickSortWorst(int* arr, int low, int high, int initialSize) {
    if (low >= high) {
        return;
    }

    int p = getPivot(arr, low, high, initialSize);

    QuickSortWorst(arr, low, p - 1, initialSize);
    QuickSortWorst(arr, p + 1, high, initialSize);
}

void QuickSortBest(int* arr, int low, int high, int initialSize) {
    if (low >= high) {
        return;
    }

    profiler.createOperation("qsAssig", initialSize);

    int i = low + (high - low) / 2;
    profiler.countOperation("qsAssig", initialSize, 3);
    std::swap(arr[i], arr[high]);

    int p = getPivot(arr, low, high, initialSize);

    QuickSortBest(arr, low, p - 1, initialSize);
    QuickSortBest(arr, p + 1, high, initialSize);
}

//endregion

//region HeapSort

void maxHeapify(int *heap, int size, int i, int initialSize) {
    profiler.createOperation("heapComp", initialSize);
    profiler.createOperation("heapAssig", initialSize);

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    profiler.countOperation("heapComp", initialSize);
    if (left < size && heap[left] > heap[largest]) {
        largest = left;
    }
    profiler.countOperation("heapComp", initialSize);
    if (right < size && heap[right] > heap[largest]) {
        largest = right;
    }

    if (largest != i) {
        profiler.countOperation("heapAssig", initialSize, 3);
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        maxHeapify(heap, size, largest, initialSize);
    }
}

void buildHeapBottomUp(int *heap, int size, int initialSize) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, size, i, initialSize);
    }
};

void HeapSort(int* heap, int size, int initialSize) {

    buildHeapBottomUp(heap, size, initialSize);
    for (int i = size - 1; i >= 0; i--) {
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;
        size--;
        maxHeapify(heap, size, 0, initialSize);
    }
}

//endregion

//region SelectionSort
void SelectionSort(int *arr, int size, int initialSize) {
    profiler.createOperation("ssComp", initialSize);
    profiler.createOperation("ssAssig", initialSize);

    for (int i = 0; i < size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < size; j++) {
            profiler.countOperation("ssComp", initialSize, 1);
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        profiler.countOperation("ssAssig", initialSize, 3);
        std::swap(arr[min], arr[i]);
    }
}

void SelectionSortRecursive(int *arr, int size, int initialSize) {
    profiler.createOperation("ssRecComp", initialSize);
    profiler.createOperation("ssRecAssig", initialSize);

    if (size <= 1) {
        return;
    }

    int min = 0;
    for (int i = 1; i < size; i++) {
        profiler.countOperation("ssRecComp", initialSize, 1);
        if (arr[i] < arr[min]) {
            min = i;
        }
    }
    profiler.countOperation("ssRecAssig", initialSize, 3);
    std::swap(arr[min], arr[0]);
    SelectionSortRecursive(arr + 1, size - 1, initialSize);
}

void testSelection() {
    for (int i = STEP; i <= MAX_SIZE; i += STEP) {
        for (int j = 0; j < 1; j++) {
            int arr1[i];
            int arr2[i];
            FillRandomArray(arr1, i, 10, 50000, false);
            memcpy(arr2, arr1, i * sizeof(int));
            SelectionSort(arr1, i, i);
            SelectionSortRecursive(arr2, i, i);
        }
    }


    profiler.createGroup("Comparisons", "ssComp", "ssRecComp");
    profiler.createGroup("Assignments", "ssAssig", "ssRecAssig");
    profiler.addSeries("ssTotal", "ssComp", "ssAssig");
    profiler.addSeries("ssRecTotal", "ssRecComp", "ssRecAssig");
    profiler.createGroup("Total", "ssTotal", "ssRecTotal");

    for (int i = STEP; i <= MAX_SIZE; i += STEP) {

        int arr1[i];
        int arr2[i];
        FillRandomArray(arr1, i, 10, 50000, false);
        memcpy(arr2, arr1, i * sizeof(int));
        profiler.startTimer("ssTimer", i);
        SelectionSort(arr1, i, i);
        profiler.stopTimer("ssTimer", i);

        profiler.startTimer("ssRecTimer", i);
        SelectionSortRecursive(arr2, i, i);
        profiler.stopTimer("ssRecTimer", i);


    }

    profiler.createGroup("Timer", "ssTimer", "ssRecTimer");

    profiler.showReport();
}

//endregion

void testAverageCase() {
    for (int i = STEP; i <= MAX_SIZE; i += STEP) {
        for (int j = 0; j < NR_TESTS; j++) {
            int arr1[i];
            int arr2[i];
            FillRandomArray(arr1, i, 10, 50000, false);
            memcpy(arr2, arr1, i * sizeof(int));
            QuickSort(arr1, 0, i - 1, i);
            HeapSort(arr2, i, i);
        }
    }

    profiler.divideValues("qsComp", NR_TESTS);
    profiler.divideValues("qsAssig", NR_TESTS);
    profiler.divideValues("heapComp", NR_TESTS);
    profiler.divideValues("heapAssig", NR_TESTS);

    profiler.createGroup("Comparisons", "qsComp", "heapComp");
    profiler.createGroup("Assignments", "qsAssig", "heapAssig");
    profiler.addSeries("qsTotal", "qsComp", "qsAssig");
    profiler.addSeries("heapTotal", "heapComp", "heapAssig");
    profiler.createGroup("Total", "qsTotal", "heapTotal");
    profiler.showReport();
}

void testBestCase() {
    for (int i = STEP; i <= MAX_SIZE; i += STEP) {
        int arr1[i];
        int arr2[i];

        FillRandomArray(arr1, i, 10, 50000, false, DESCENDING);

        FillRandomArray(arr2, i, 10, 50000, false, ASCENDING);
        HeapSort(arr1, i, i);
        QuickSortBest(arr2, 0, i - 1, i);

        printf("%d\n", i);

    }
    profiler.createGroup("Comparisons", "qsComp", "heapComp");
    profiler.createGroup("Assignments", "qsAssig", "heapAssig");
    profiler.addSeries("qsTotal", "qsComp", "qsAssig");
    profiler.addSeries("heapTotal", "heapComp", "heapAssig");
    profiler.createGroup("Total", "qsTotal", "heapTotal");
    profiler.showReport();
}

void testWorstCase() {
    for (int i = STEP; i <= MAX_SIZE; i += STEP) {
        int arr1[i];
        int arr2[i];

        FillRandomArray(arr1, i, 10, 50000, false, ASCENDING);
        //Quicksort worst case (pivot is always the smallest element)
        //We pick high as the pivot element so we get the worst case (not random)
        FillRandomArray(arr2, i, 10, 50000, false, ASCENDING);

        HeapSort(arr1, i, i);
        QuickSortWorst(arr2, 0, i - 1, i);


    }
    profiler.createGroup("Comparisons", "qsComp", "heapComp");
    profiler.createGroup("Assignments", "qsAssig", "heapAssig");
    profiler.addSeries("qsTotal", "qsComp", "qsAssig");
    profiler.addSeries("heapTotal", "heapComp", "heapAssig");
    profiler.createGroup("Total", "qsTotal", "heapTotal");
    profiler.showReport();
}

//Quicksort demo
void demo() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    QuickSort(arr, 0, n - 1, n);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
}

//Quickselect demo
void demo2() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int k = quickSelect(arr, 0, n - 1, 6);

    QuickSort(arr,0, n - 1, n);

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n%d", k);
}

int main() {
    testAverageCase();
    profiler.reset("Worst Case");
    testWorstCase();
    profiler.reset("Best Case");
    testBestCase();
    //profiler.reset("Selection vs Selection Recursive");
    //testSelection();

    return 0;
}
