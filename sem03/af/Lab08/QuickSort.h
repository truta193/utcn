#pragma once

#define THRESHOLD 30

void insertionSort(int *arr, int size, int initialSize, char *compOp, char *asigOp);

void quickSort(int *arr, int low, int high, int initialSize, char *compOp, char *assignOp);

void hybridQuickSort(int *arr, int low, int high, int initialSize, char *compOp, char *assignOp, int threshold = THRESHOLD);

void report();