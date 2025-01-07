#include "queue.h"
#include <stdio.h>

void queueInit(QueueT *queue) {
    queue->size = 0;
    queue->tail = 0;
    queue->head = 0;
};

void queueEnqueue(QueueT *queue, int key) {
    if (queue->size >= CAPACITY) {
        return;
    }
    queue->head = queue->head % CAPACITY;
    queue->vec[queue->head] = key;
    queue->head++;
    queue->size++;
};
int queueDequeue(QueueT *queue) {
    if (queue->size <= 0) {
        return 0;
    };
    int ret = queue->vec[queue->tail];
    queue->tail++;
    queue->size--;
    return ret;


};
void queuePrint(QueueT *queue) {
    if (queue->head > queue->tail) {
        for (int i = queue->tail; i < queue->head; i++) {
            printf("%d ", queue->vec[i]);
        }
        printf("\n");
    } else {
        for (int i = queue->tail; i < CAPACITY; i++) {
            printf("%d ", queue->vec[i]);

        }
        for (int i = 0; i < queue->head; i++) {
            printf("%d ", queue->vec[i]);
        }
        printf("\n");
    }
};