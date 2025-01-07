#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

int main() {
    int v[MAX_SIZE] = {0};
    int n = 0;
    scanf("%d", &n);
    FILE *fin = fopen("../input.txt", "r");
    for (int i = 0; i < n; i++) {
        fscanf(fin, "%d", &v[i]);
    }
    fclose(fin);

    FILE *fout = fopen("../output.txt", "w");
    for (int i = n - 1; i >= 0; i--) {
        fprintf(fout, "%d ", v[i]);
    }
    fclose(fout);

    int min = 0;
    int max = 0;

    printf("\nGenerare test case\n");
    printf("n, min, max = ");
    scanf("%d %d %d", &n, &min, &max);

    int *gen = malloc(sizeof(int) * n);

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        gen[i] = rand() % (max - min + 1) + min;
    }

    fout = fopen("../output.txt", "a+");
    fprintf(fout, "\n");
    for (int i = 0; i < n; i++) {
        fprintf(fout, "%d ", gen[i]);
    }


    fprintf(fout, "\n");
    int x = 100;
    for (; x <= 10000; x += 100) {
        //fprintf("%f %f %f %f %f")
    }

    fclose(fout);

    return 0;
}
