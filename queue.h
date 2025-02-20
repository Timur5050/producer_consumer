#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

typedef struct __node_t {
    int value;
    struct __node_t *next;
} node_t;

typedef struct __queue_t {
    node_t *head;
    node_t *tail;
    pthread_mutex_t head_lock, tail_lock;
} queue_t;

void queue_init(queue_t **q);
void enqueue_value(queue_t *q, int value);
int dequeue_value(queue_t *q, int *value);

#endif 
