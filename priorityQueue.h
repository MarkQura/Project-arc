#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct _pQueue * pQueue;

pQueue newPQueue(int cap);

void destroyPQueue(pQueue pq);

void DestroyPQueueAndElems(pQueue pq, void (*destroi)(void *));

int adicionaElemPq(pQueue pq, team elem);

team Poll(pQueue pq);

#endif // PRIORITYQUEUE_H
