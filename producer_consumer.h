#ifndef PRODUCER_CONSUMER_H
#define PRODUCER_CONSUMER_H

#include "queue.h"
#include <pthread.h>

#define MAX 100

extern int done;
extern int counter;
extern pthread_mutex_t lock;
extern pthread_cond_t fill, cons;
extern queue_t *q;

void *producer(void *ptr);
void *consumer(void *ptr);

#endif
