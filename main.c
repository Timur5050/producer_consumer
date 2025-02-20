#include "producer_consumer.h"
#include <stdio.h>
#include <pthread.h>

int main()
{   
    queue_init(&q);
    
    pthread_t p1, p2, c1, c2;
    int id1 = 0, id2 = 1;

    pthread_create(&p1, NULL, producer, &id1);
    pthread_create(&p2, NULL, producer, &id2);
    pthread_create(&c1, NULL, consumer, NULL);
    pthread_create(&c2, NULL, consumer, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    pthread_mutex_lock(&lock);
    done = 1;
    pthread_cond_broadcast(&cons);
    pthread_mutex_unlock(&lock);

    pthread_join(c1, NULL);
    pthread_join(c2, NULL);

    return 0;
}
