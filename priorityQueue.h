#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct _pQueue *pQueue;

/***********************************************
newPQueue - creates an instance of the structure priority queue
Parametros:
    cap - max number of elements the queue can hold
Retorno: pointer to the instance of the created queue
Pre-condicoes: cap > 0
***********************************************/
pQueue newPQueue(int cap);

/***********************************************
destroyPQueue - frees the memory associated with the given queue.
Parametros:
    pq - priority queue
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void destroyPQueue(pQueue pq);

/***********************************************
destroyPQueue - frees the memory associated with the given queue and it's elements.
Parametros:
    pq - priority queue
Retorno:
Pre-condicoes: c != NULL
***********************************************/
void DestroyPQueueAndElems(pQueue pq);

/***********************************************
add_pq_elem - adds elements to the priority queue whislt satisfying the heap invariant.
Parametros:
    pq - priority queue
    elem - element to add to the queue
Retorno: 1 if it added, 0 if not
Pre-condicoes: c != NULL
***********************************************/
int add_pq_elem(pQueue pq, team elem);

/***********************************************
Poll - removes the root element of the priority queue whislt satisfying the heap invariant.
Parametros:
    pq - priority queue
Retorno: element in the root of the queue
Pre-condicoes: c != NULL
***********************************************/
team Poll(pQueue pq);

#endif // PRIORITYQUEUE_H
