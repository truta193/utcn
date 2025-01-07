#include <stdio.h>
#include "student.h"
#include <stdlib.h>

int main() {
    FILE *f = fopen("date.in", "r");

    int nrStud = 0;
    fscanf(f, "%d", &nrStud);
    Student **studArr = malloc(sizeof(Student*) * nrStud);
    for (int i = 0; i < nrStud; i++) {
        createStudent(f, &studArr[i]);
        printStudent(studArr[i]);
        printf("\n");
    }

    for (int i = 0; i < nrStud; i++) {
        printAverage(studArr[i]);
    }
    printf("\n");


    for (int i = 0; i < nrStud; i++) {
        incrementByOne(studArr[i]);
    }
    printf("\n");


    for (int i = 0; i < nrStud; i++) {
        printStudent(studArr[i]);
    }
    printf("\n");

    fclose(f);

    return 0;
}
