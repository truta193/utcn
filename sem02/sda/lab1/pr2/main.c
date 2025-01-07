/*
 * Se citesc de la tastatura 2 numere, CAPACITY si SIZE. Sa se aloce dinamic un sir care poata sa contina
CAPACITY elemente reale. Sa se scrie o functie care adauga un element in sir, pe ultima pozitie a sirului.
Folosind functia creata sa se insereze in sir SIZE numere. Ce se intampla daca CAPACITY ≥ SIZE si
daca CAPACITY < SIZE. Afisati sirul de numere dupa fieecare operatie de inserare.
 */

#include <stdio.h>
#include "vector.h"
#include <stdlib.h>

int main() {
    int cap, size;
    scanf("%d %d", &cap, &size);
    Vector_t *vector = NULL;
    if (createVector(cap, &vector) != STAT_SUCCESS) {
        return 1;
    };

    vectorPush(vector, 5.0f);
    vectorPrint(vector);

    float *batch = malloc(sizeof(float) * size);
    if (batch == NULL) {
        return 1;
    }
    for (int i = 0; i < size; i++) {
        batch[i] = (float) i;
    }

    vectorPushBatch(vector, batch, size);
    vectorPrint(vector);

    return 0;
}
