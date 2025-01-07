#include <stdio.h>

int binarySearch(int* v, int n, int key) {
    int st = 0;
    int dr = n;
    int m = 0;
    while (st <= dr) {
        m = (st + dr)/2;
        if ( v[m] == key) {
            return m;
        }
        if (v[m] < key)
            st = m+1;
        else
            dr = m-1;
    }

    if (m >= n) {
        return n+1;
    }
    return m;
}

int main() {
    int arr[10] = {1,3,5,7,9,11,13,15,17,19};
    int k = binarySearch(arr, 10, 20);
    printf("%d\n", k);
    return 0;
}
