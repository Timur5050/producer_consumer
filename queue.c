#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void queue_init(queue_t **q)
{
    *q = (queue_t*)malloc(sizeof(queue_t));
    node_t *tmp = (node_t*)malloc(sizeof(node_t));
    tmp->next = NULL;
    (*q)->head = tmp;
    (*q)->tail = tmp;

    pthread_mutex_init(&(*q)->head_lock, NULL);
    pthread_mutex_init(&(*q)->tail_lock, NULL);
}

void enqueue_value(queue_t *q, int value)
{
    node_t *tmp = (node_t*)malloc(sizeof(node_t));
    assert(tmp != NULL);
    
    tmp->value = value;
    tmp->next = NULL;

    pthread_mutex_lock(&q->tail_lock);
    q->tail->next = tmp;
    q->tail = tmp;
    pthread_mutex_unlock(&q->tail_lock);
}

int dequeue_value(queue_t* q, int* value)
{
    pthread_mutex_lock(&q->head_lock);

    node_t* head = q->head;
    node_t* new_head = head->next;
    
    if (new_head == NULL)
    {
        pthread_mutex_unlock(&q->head_lock);
        return -1;
    }

    *value = new_head->value;
    q->head = new_head;
    pthread_mutex_unlock(&q->head_lock);
    free(head);
    return 0;
}
