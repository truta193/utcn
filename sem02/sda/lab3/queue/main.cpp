#include <iostream>
#include "queue.h"

int main() {
    QueueT queue;
    queueInit(&queue);
    queueEnqueue(&queue, 0);
    queueEnqueue(&queue, 1);
    queueEnqueue(&queue, 2);
    queueEnqueue(&queue, 3);
    queueEnqueue(&queue, 4);
    queueEnqueue(&queue, 5);
    queueEnqueue(&queue, 6);
    queueEnqueue(&queue, 7);
    queueEnqueue(&queue, 8);
    queueEnqueue(&queue, 9);
    queueEnqueue(&queue, 10);
    queueEnqueue(&queue, 11);
    queueEnqueue(&queue, 12);
    queueDequeue(&queue);
    queueDequeue(&queue);
    queueDequeue(&queue);
    queueDequeue(&queue);
    queueDequeue(&queue);
    queueEnqueue(&queue, 12);
    queuePrint(&queue);

    return 0;
}
