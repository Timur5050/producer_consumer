#include "producer_consumer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int done = 0;
int counter = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
pthread_cond_t cons = PTHREAD_COND_INITIALIZER;

queue_t *q = NULL;

void *producer(void* ptr)
{   
    int id = *((int*)ptr);
    for (int i = id; i < MAX; i += 2)
    {   
        pthread_mutex_lock(&lock);
        while (counter == MAX)
        {
            pthread_cond_wait(&fill, &lock);
        }
        enqueue_value(q, i);
        counter++;
        printf("Producer %d produced: %d\n", id, i);
        pthread_cond_broadcast(&cons);
        pthread_mutex_unlock(&lock);
        usleep(50000);
    }
    return NULL;
}

void *consumer(void* ptr)
{
    while (1)  
    {
        pthread_mutex_lock(&lock);

        while (counter == 0)
        {
            if (done) 
            {
                pthread_mutex_unlock(&lock);
                return NULL;
            }
            pthread_cond_wait(&cons, &lock);
        }
    
        int value; 
        if (dequeue_value(q, &value) == 0)
        {
            printf("Consumer got: %d\n", value);
            counter--;
        }
        
        pthread_cond_broadcast(&fill);
        pthread_mutex_unlock(&lock);
        usleep(100000);
    }
}
