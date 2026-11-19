
#include "priority_queue.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 10

// Helper function declarations
static void percolateUp(PriorityQueue *pq);
static void percolateDown(PriorityQueue *pq);
static void swap(PriorityQueue *pq, int index1, int index2);


PriorityQueue *pq_create(void) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));

    if (pq == NULL) {
        return NULL;
    }

    pq->size = 0;
    pq->capacity = INITIAL_CAPACITY;

    pq->data = malloc(sizeof(HuffmanNode *) * INITIAL_CAPACITY);

    if (pq->data == NULL) {
        free(pq);
        return NULL;
    }

    return pq;
}


int pq_is_empty(PriorityQueue *pq) {
    return pq == NULL || pq->size == 0;
}


int pq_push(PriorityQueue *pq, HuffmanNode *node) {
    if (pq == NULL || node == NULL) {
        return 0;
    }

    if (pq->size == pq->capacity) {
        if (!pq_resize(pq)) {
            return 0;
        }
    }

    pq->data[pq->size] = node;
    pq->size++;

    percolateUp(pq);

    return 1;
}


static void percolateUp(PriorityQueue *pq) {
    int i = pq->size - 1;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (pq->data[i]->frequency >= pq->data[parent]->frequency) {
            break;
        }

        swap(pq, i, parent);
        i = parent;
    }
}


static void swap(PriorityQueue *pq, int index1, int index2) {
    HuffmanNode *temp = pq->data[index1];
    pq->data[index1] = pq->data[index2];
    pq->data[index2] = temp;
}


HuffmanNode *pq_pop(PriorityQueue *pq) {
    if (pq == NULL || pq->size == 0) {
        return NULL;
    }

    HuffmanNode *temp = pq->data[0];

    pq->size--;

    if (pq->size > 0) {
        pq->data[0] = pq->data[pq->size];
        percolateDown(pq);
    }

    return temp;
}


static void percolateDown(PriorityQueue *pq) {
    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int child;

        if (left >= pq->size) {
            break;
        }

        child = left;

        if (right < pq->size &&
            pq->data[right]->frequency < pq->data[left]->frequency) {
            child = right;
        }

        if (pq->data[i]->frequency <= pq->data[child]->frequency) {
            break;
        }

        swap(pq, i, child);
        i = child;
    }
}


HuffmanNode *pq_peek(PriorityQueue *pq) {
    if (pq == NULL || pq->size == 0) {
        return NULL;
    }

    return pq->data[0];
}


int pq_resize(PriorityQueue *pq) {
    if (pq == NULL) {
        return 0;
    }

    int newCapacity = pq->capacity * 2;

    HuffmanNode **temp = realloc(
        pq->data,
        sizeof(HuffmanNode *) * newCapacity
    );

    if (temp == NULL) {
        return 0;
    }

    pq->data = temp;
    pq->capacity = newCapacity;

    return 1;
}


void pq_destroy(PriorityQueue *pq) {
    if (pq == NULL) {
        return;
    }

    free(pq->data);
    free(pq);
}




