#include <stdio.h>
#include <string.h>
#include <malloc.h>

void merge(int *arr1, int *arr2, int n1, int n2, int *out)
{
    int i = 0, j = 0, k = 0;
    int *temp = malloc(sizeof(int)*(n1+n2));

    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) {
            temp[k] = arr1[i];
            i++;
        }
        else {
            temp[k] = arr2[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        temp[k] = arr1[i];
        i++;
        k++;
    }
    while (j < n2) {
        temp[k] = arr2[j];
        j++;
        k++;
    }

    memcpy(out, temp, (n1+n2)*sizeof(int));
    free(temp);
}

void mergeSort(int *arr, int left, int right)
{
    if (left < right) {
        int m = (left + right) / 2;

        mergeSort(arr, left, m);
        mergeSort(arr, m + 1, right);

        //Ceva nu merge aici
        int *a1 = malloc(sizeof(int) * right/2+1);
        memcpy(a1, arr+left, m-left);
        int *a2 = malloc(sizeof(int) * right/2+1);
        memcpy(a2, arr+m+left+1, right-m);
        merge(a1, a2, m-left+1, right-m-1, arr);
    }
}

int main() {
    int a[10] = {2,4,6,8,10, 1,3,5,7,9};
    int *c= malloc(10*sizeof(int));
    mergeSort(a, 0, 10);
    for (int i = 0; i < 10; i++) {
        printf("%d\n", a[i]);
    }
    return 0;
}
