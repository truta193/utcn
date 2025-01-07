#include <stdio.h>
#include <malloc.h>
#include <limits.h>

typedef struct vector {
    int *vector;
    int capacity;
    int size;
} VectorT;

void maxLenSubseq(int *v, int n) {
    int *steps = malloc(sizeof(int) * n);


    VectorT *trace = malloc(sizeof(VectorT) * n);
    for (int i = 0; i < n; i++) {
        trace[i].vector = malloc(sizeof(int) * n);
        trace[i].capacity = n;
        trace[i].size = 0;
    }

    steps[0] = 1;
    trace[0].vector[0] = v[0];
    trace[0].size = 1;
    //50, 1, 60, 70, 2, 3, 5, 7, 9, 75, 80, 10
    //1   1  2    3  2  3  4  4  5  6   2
    for (int i = 1; i < n; i++) {
        steps[i] = 1;
        for (int j = 0; j < i; j++) {
            // Check all numbers before current; if smaller, then if new number contributes update
            if (v[i] > v[j] && steps[i] < steps[j] + 1) {
                // Retrieve smallest element that has the steps so far equal to current position
                int min = INT_MAX;
                for (int k = 0; k < i; k++) {
                    if (steps[k] == steps[j]) {
                        if (v[k] < min) {
                            min = v[k];
                        }
                    }
                }
                trace[i].vector[trace[i].size++] = min;
                steps[i] = steps[j] + 1;

            }
        }
    }

    //Get max len
    int longest = 0;
    for (int i = 0; i < n; i++) {
        if (steps[i] > longest) {
            longest = steps[i];
        }
    }

    // Finish off trace matrix
    for (int i = 0; i < n; i++) {
        trace[i].vector[trace[i].size] = v[i];
        trace[i].size += 1;
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", trace[i].vector[j]);
        }
        printf("\n");
    }

    int longestTrace = 0;
    for (int i = 0; i < n; i++) {
        if (trace[i].size > trace[longestTrace].size) {
            longestTrace = i;
        }
    }

    FILE *fout = fopen("../date.out", "w");
    fprintf(fout, "%d\n", longest);

    for (int i = 0; i < trace[longestTrace].size; i++) {
        fprintf(fout, "%d ", trace[longestTrace].vector[i]);
    }

    fclose(fout);

}

int main() {
    FILE *fin = fopen("../date.in", "r");
    int n;
    fscanf(fin, "%d", &n);
    int *arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &arr[i]);
    }
    fclose(fin);
    maxLenSubseq(arr, n);
    return 0;
}
