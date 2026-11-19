
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "huffman.h"

typedef struct {
    HuffmanNode **data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue *pq_create(void);
int pq_is_empty(PriorityQueue *pq);
int pq_push(PriorityQueue *pq, HuffmanNode *node);
HuffmanNode *pq_pop(PriorityQueue *pq);
HuffmanNode *pq_peek(PriorityQueue *pq);
int pq_resize(PriorityQueue *pq);
void pq_destroy(PriorityQueue *pq);

#endif
