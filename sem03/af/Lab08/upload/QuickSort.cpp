#include <iostream>
#include "QuickSort.h"

#include "Profiler.h"

#define THRESHOLD 30
#define MAX_SIZE 10000
#define STEP 100
#define NR_TESTS 5
#define TIME_TESTS 100


Profiler profiler("QuickSort");

void insertionSort(int *arr, int size, int initialSize, char *compOp, char *asigOp) {
    profiler.createOperation(asigOp, initialSize);
    profiler.createOperation(compOp, initialSize);
    int cursor, aux;
    for (int i = 1; i < size; i++) {
        profiler.countOperation(asigOp, initialSize);
        aux = arr[i];
        cursor = i - 1;
        while (cursor >= 0) {
            profiler.countOperation(compOp, initialSize);
            if (arr[cursor] > aux) {
                profiler.countOperation(asigOp, initialSize);
                arr[cursor + 1] = arr[cursor];
            } else {
                break;
            }
            cursor--;
        }
        profiler.countOperation(asigOp, size);
        arr[cursor + 1] = aux;
    }
}

int getPivot(int *arr, int low, int high, int initialSize, char *compOp, char *assignOp) {
    profiler.createOperation(compOp, initialSize);
    profiler.createOperation(assignOp, initialSize);

    profiler.countOperation(assignOp, initialSize, 1);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        profiler.countOperation(compOp, initialSize, 1);
        if (arr[j] < pivot) {
            i++;
            profiler.countOperation(assignOp, initialSize, 3);
            std::swap(arr[i], arr[j]);
        }
    }

    profiler.countOperation(assignOp, initialSize, 3);
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int *arr, int low, int high, int initialSize, char *compOp, char *assignOp) {
    if (low >= high) {
        return;
    }
    profiler.createOperation(assignOp, initialSize);

    //Random pivot
    srand(time(NULL));
    int i = low + rand() % (high - low);
    profiler.countOperation(assignOp, initialSize, 3);
    std::swap(arr[i], arr[high]);

    int p = getPivot(arr, low, high, initialSize, compOp, assignOp);

    quickSort(arr, low, p - 1, initialSize, compOp, assignOp);
    quickSort(arr, p + 1, high, initialSize, compOp, assignOp);
}

void
hybridQuickSort(int *arr, int low, int high, int initialSize, char *compOp, char *assignOp, int threshold) {
    if (low >= high) {
        return;
    }

    if (high - low + 1 < threshold) {
        insertionSort(arr, high - low + 1, initialSize, compOp, assignOp);
    } else {
        int p = getPivot(arr, low, high, initialSize, compOp, assignOp);
        hybridQuickSort(arr, low, p - 1, initialSize, compOp, assignOp);
        hybridQuickSort(arr, p + 1, high, initialSize, compOp, assignOp);
    }
}

void report() {
    for (int i = STEP; i < MAX_SIZE; i += STEP) {
        for (int test = 0; test < NR_TESTS; test++) {
            int *arr = new int[i];
            int *arrCopy = new int[i];
            FillRandomArray(arr, i, 10, 50000, false, UNSORTED);
            for (int j = 0; j < i; j++) {
                arrCopy[j] = arr[j];
            }

            quickSort(arr, 0, i - 1, i, "qsComp", "qsAssig");
            hybridQuickSort(arrCopy, 0, i - 1, i, "hqsComp", "hqsAssig");
        }
    }

    profiler.addSeries("QuickSortTotal", "qsComp", "qsAssig");
    profiler.addSeries("HybridQuickSortTotal", "hqsComp", "hqsAssig");
    profiler.divideValues("QuickSortTotal", NR_TESTS);
    profiler.divideValues("HybridQuickSortTotal", NR_TESTS);
    profiler.createGroup("TotalOps", "QuickSortTotal", "HybridQuickSortTotal");


    for (int i = STEP; i < MAX_SIZE; i += STEP) {
        for (int test = 0; test < TIME_TESTS; test++) {
            int *arr = new int[i];
            int *arrCopy = new int[i];
            FillRandomArray(arr, i, 10, 50000, false, UNSORTED);
            for (int j = 0; j < i; j++) {
                arrCopy[j] = arr[j];
            }

            profiler.startTimer("qsTimer", i);
            quickSort(arr, 0, i - 1, i, "qsComp", "qsAssig");
            profiler.stopTimer("qsTimer", i);
            profiler.startTimer("hqsTimer", i);
            hybridQuickSort(arrCopy, 0, i - 1, i, "hqsComp", "hqsAssig");
            profiler.stopTimer("hqsTimer", i);
        }
    }

    profiler.createGroup("TotalTime", "qsTimer", "hqsTimer");

    //Number of Operations
    for (int i = 0; i < 200; i++) {
        for (int test = 0; test < NR_TESTS; test++) {
            int *arr = new int[10000];
            int *arrCopy = new int[10000];
            FillRandomArray(arr, 10000, 10, 50000, false, UNSORTED);
            for (int j = 0; j < 10000; j++) {
                arrCopy[j] = arr[j];
            }

            quickSort(arr, 0, 9999, i, "qsComp2", "qsAssig2");
            hybridQuickSort(arrCopy, 0, 9999, i, "hqsCompTVar", "hqsAssigTVar", i);
        }
    }
    //Time
    for (int i = 0; i < 200; i++) {
        std::cout << "i: " << i << "\n";
        for (int test = 0; test < TIME_TESTS; test++) {
            int *arr = new int[10000];
            int *arrCopy = new int[10000];
            FillRandomArray(arr, 10000, 10, 50000, false, UNSORTED);
            for (int j = 0; j < 10000; j++) {
                arrCopy[j] = arr[j];
            }

            profiler.startTimer("TimerH", i);
            hybridQuickSort(arrCopy, 0, 9999, i, "tvmrc", "tvmra", i);
            profiler.stopTimer("TimerH", i);
        }
    }

    profiler.addSeries("QuickSortTotalVar", "qsComp2", "qsAssig2");
    profiler.addSeries("HybridQuickSortTotalVar", "hqsCompTVar", "hqsAssigTVar");
    profiler.divideValues("QuickSortTotalVar", 10);
    profiler.divideValues("HybridQuickSortTotalVar", 10);
    profiler.createGroup("TotalVar", "QuickSortTotalVar", "HybridQuickSortTotalVar");


    profiler.showReport();

}