#pragma once

#define CAPACITY 10
typedef struct _queue {
    int vec[CAPACITY];
    int size;
    int head, tail;
} QueueT;

void queueInit(QueueT *queue);
void queueEnqueue(QueueT *queue, int key);
int queueDequeue(QueueT *queue);
void queuePrint(QueueT *queue);