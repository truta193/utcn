#include <iostream>
#include "Profiler.h"

Profiler profiler("Average Cases");

#define MAX_SIZE 10000
#define STEP 100
#define NR_TESTS 5

void Selection_Sort(int *arr, int size, char *compOp, char *asigOp) {
    profiler.createOperation(asigOp, size);
    profiler.createOperation(compOp, size);
    int minIndex, aux;
    for (int i = 0; i < size - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < size; j++) {
            profiler.countOperation(compOp, size);
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            profiler.countOperation(asigOp, size, 3);
            aux = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = aux;
        }
    }
}

void Insertion_Sort(int *arr, int size, char *compOp, char *asigOp) {
    profiler.createOperation(asigOp, size);
    profiler.createOperation(compOp, size);
    int cursor, aux;
    for (int i = 1; i < size; i++) {
        profiler.countOperation(asigOp, size);
        aux = arr[i];
        cursor = i - 1;
        while (cursor >= 0) {
            profiler.countOperation(compOp, size);
            if (arr[cursor] > aux) {
                profiler.countOperation(asigOp, size);
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

void Insertion_Sort_Binary_Insertion(int *arr, int size, char *compOp, char *asigOp) {
    profiler.createOperation(asigOp, size);
    profiler.createOperation(compOp, size);
    int aux, left, right, mid;
    for (int i = 1; i < size; i++) {
        profiler.countOperation(asigOp, size);
        aux = arr[i];
        left = 0;
        right = i - 1;

        while (left <= right) {
            mid = (left + right) / 2;
            profiler.countOperation(compOp, size);
            if (arr[mid] > aux) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        for (int j = i - 1; j >= left; j--) {
            profiler.countOperation(asigOp, size);
            arr[j + 1] = arr[j];
        }
        profiler.countOperation(asigOp, size);
        arr[left] = aux;
    }
}

void Bubble_Sort(int *arr, int size, char *compOp, char *asigOp) {
    profiler.createOperation(asigOp, size);
    profiler.createOperation(compOp, size);
    int aux;
    bool sorted = false;
    for (int i = 0; i < size; i++) {
        sorted = true;
        for (int j = 0; j < size - i - 1; j++) {
            profiler.countOperation(compOp, size);
            if (arr[j] > arr[j + 1]) {
                profiler.countOperation(asigOp, size, 3);
                aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
                sorted = false;
            }
        }
        if (sorted) break;
    }
}

void Demo_Selection() {
    int arr[] = {9, 6, 15, 9, -2, 34, -50};
    Selection_Sort(arr, sizeof(arr) / sizeof(int), (char *) "sel-comp", (char *) "sel-asig");

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void Demo_Binary_Insertion() {
    int arr[] = {9, 6, 15, 9, -2, 34, -50};
    Insertion_Sort_Binary_Insertion(arr, sizeof(arr) / sizeof(int), (char *) "ins-bin-comp", (char *) "ins-bin-asig");

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void Demo_Insertion() {
    int arr[] = {9, 6, 15, 9, -2, 34, -50};
    Insertion_Sort(arr, sizeof(arr) / sizeof(int), (char *) "ins-comp", (char *) "ins-asig");

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void Demo_Bubble() {
    int arr[] = {9, 6, 15, 9, -2, 34, -50};
    Bubble_Sort(arr, sizeof(arr) / sizeof(int), (char *) "bub-comp", (char *) "bub-asig");

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void computeAverageCases(int size) {
    int arr[size];
    int arr2[size];
    int arr3[size];
    int arr4[size];
    for (int i = STEP; i <= size; i += STEP) {
        for (int j = 0; j < NR_TESTS; j++) {
            FillRandomArray(arr, size);
            memcpy(arr2, arr, sizeof(int) * size);
            memcpy(arr3, arr, sizeof(int) * size);
            memcpy(arr4, arr, sizeof(int) * size);
            Selection_Sort(arr, i, (char *) "sel-comp", (char *) "sel-asig");
            Insertion_Sort_Binary_Insertion(arr2, i, (char *) "ins-bin-comp", (char *) "ins-bin-asig");
            Bubble_Sort(arr3, i, (char *) "bub-comp", (char *) "bub-asig");
            Insertion_Sort(arr4, i, (char *) "ins-comp", (char *) "ins-asig");

//            printf("%d", IsSorted(arr, i));
//            printf("%d", IsSorted(arr2, i));
//            printf("%d", IsSorted(arr3, i));
//            printf("%d", IsSorted(arr4, i));

        }
        printf("%d\n", i);
    }

    profiler.divideValues("sel-comp", NR_TESTS);
    profiler.divideValues("sel-asig", NR_TESTS);
    profiler.divideValues("bub-comp", NR_TESTS);
    profiler.divideValues("bub-asig", NR_TESTS);
    profiler.divideValues("ins-bin-comp", NR_TESTS);
    profiler.divideValues("ins-bin-asig", NR_TESTS);
    profiler.divideValues("ins-comp", NR_TESTS);
    profiler.divideValues("ins-asig", NR_TESTS);

}

void computeBestCases(int size) {
    int arr[size];
    int arr2[size];
    int arr3[size];
    int arr4[size];

    //Selection best case
    FillRandomArray(arr, size, 10, 50000, false, ASCENDING);
    // Insertion best case
    memcpy(arr2, arr, sizeof(int) * size);
    //Bubble sort best case
    memcpy(arr3, arr, sizeof(int) * size);
    //Insertion best case
    memcpy(arr4, arr, sizeof(int) * size);

    for (int i = STEP; i <= size; i += STEP) {
        Selection_Sort(arr, i, (char *) "sel-comp", (char *) "sel-asig");
        Insertion_Sort_Binary_Insertion(arr2, i, (char *) "ins-bin-comp", (char *) "ins-bin-asig");
        Bubble_Sort(arr3, i, (char *) "bub-comp", (char *) "bub-asig");
        Insertion_Sort(arr4, i, (char *) "ins-comp", (char *) "ins-asig");
    }
}

void computeWorstCases(int size) {
    int arr[size];
    int arr2[size];
    int arr3[size];
    int arr4[size];

    //Selection worst case
    FillRandomArray(arr, size, 10, 50000, false, DESCENDING);
    // Insertion worst case
    memcpy(arr2, arr, sizeof(int) * size);
    //Bubble sort worst case
    memcpy(arr3, arr, sizeof(int) * size);
    // Insertion worst case
    memcpy(arr4, arr, sizeof(int) * size);

    for (int i = STEP; i <= size; i += STEP) {
        Selection_Sort(arr, i, (char *) "sel-comp", (char *) "sel-asig");
        Insertion_Sort_Binary_Insertion(arr2, i, (char *) "ins-bin-comp", (char *) "ins-bin-asig");
        Bubble_Sort(arr3, i, (char *) "bub-comp", (char *) "bub-asig");
        Insertion_Sort(arr4, i, (char *) "ins-comp", (char *) "ins-asig");
    }
}

int main() {
    computeAverageCases(MAX_SIZE);
    profiler.createGroup("Comparisons", "bub-comp", "sel-comp", "ins-bin-comp", "ins-comp");
    profiler.createGroup("Assignments", "sel-asig", "bub-asig", "ins-bin-asig", "ins-asig");
    profiler.addSeries("bub-total", "bub-comp", "bub-asig");
    profiler.addSeries("sel-total", "sel-comp", "sel-asig");
    profiler.addSeries("ins-bin-total", "ins-bin-comp", "ins-bin-asig");
    profiler.addSeries("ins-total", "ins-comp", "ins-asig");
    profiler.createGroup("Total Operations", "bub-total", "sel-total", "ins-bin-total", "ins-total");

    profiler.reset("Best Cases");

    computeBestCases(MAX_SIZE);
    profiler.createGroup("Comparisons", "bub-comp", "sel-comp", "ins-bin-comp", "ins-comp");
    profiler.createGroup("Assignments", "sel-asig", "bub-asig", "ins-bin-asig", "ins-asig");
    profiler.addSeries("bub-total", "bub-comp", "bub-asig");
    profiler.addSeries("sel-total", "sel-comp", "sel-asig");
    profiler.addSeries("ins-bin-total", "ins-bin-comp", "ins-bin-asig");
    profiler.addSeries("ins-total", "ins-comp", "ins-asig");
    profiler.createGroup("Total Operations", "bub-total", "sel-total", "ins-bin-total", "ins-total");


    profiler.reset("Worst Cases");

    computeWorstCases(MAX_SIZE);
    profiler.createGroup("Comparisons", "bub-comp", "sel-comp", "ins-bin-comp", "ins-comp");
    profiler.createGroup("Assignments", "sel-asig", "bub-asig", "ins-bin-asig", "ins-asig");
    profiler.addSeries("bub-total", "bub-comp", "bub-asig");
    profiler.addSeries("sel-total", "sel-comp", "sel-asig");
    profiler.addSeries("ins-bin-total", "ins-bin-comp", "ins-bin-asig");
    profiler.addSeries("ins-total", "ins-comp", "ins-asig");
    profiler.createGroup("Total Operations", "bub-total", "sel-total", "ins-bin-total", "ins-total");


    profiler.showReport();

    Demo_Selection();
    Demo_Insertion();
    Demo_Bubble();
    Demo_Binary_Insertion();

    return 0;
}
