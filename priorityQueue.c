#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "iterador.h"
#include "archaeologist.h"
#include "team.h"
#include "priorityQueue.h"

// This ADT will be used to order the teams first by score, then by players, and finaly by name
struct _pQueue
{
	void* *vect;
	int actNElems;
	int cap;
};

pQueue newPQueue(int cap)
{
	pQueue pq;
	pq = (pQueue)malloc(sizeof(struct _pQueue));
	if (pq == NULL)
		return NULL;
	pq->cap = cap;
	pq->actNElems = 0;
	pq->vect = (void* *)malloc(sizeof(void*) * cap);
	return pq;
}

void destroyPQueue(pQueue pq)
{
	free(pq->vect);
	free(pq);
}

void DestroyPQueueAndElems(pQueue pq)
{
	for (int i = 0; i < pq->cap; ++i)
		destroy_team(pq->vect[i]);
	free(pq->vect);
	free(pq);
}

void swap(void* *t1, void* *t2)
{
	void* aux = *t1;
	*t1 = *t2;
	*t2 = aux;
}

int add_pq_elem(pQueue pq, void* elem, int(*comparation)(void*, void*))
{
	int actNum = pq->actNElems;
	pq->vect[pq->actNElems++] = elem;
	if (!actNum)
		return 1;

	int k = (actNum - 1) / 2;
	while (comparation(pq->vect[k], pq->vect[actNum]) && actNum != 0)
	{
		swap(&pq->vect[k], &pq->vect[actNum]);
		actNum = k;
		k = (actNum - 1) / 2;
	}
	return 1;
}

team Poll(pQueue pq, int(*comparation)(void*, void*))
{
	team t = pq->vect[0];
	swap(&pq->vect[0], &pq->vect[--pq->actNElems]);

	if (pq->actNElems == 1)
		return t;

	else if (pq->actNElems == 2)
	{
		if (comparation(pq->vect[0], pq->vect[1]))
			swap(&pq->vect[0], &pq->vect[1]);
		return t;
	}

	int kl, kr, numElem = 0;
	kl = 1;
	kr = 2;
	while (kr < pq->actNElems)
	{
		if (comparation(pq->vect[numElem], pq->vect[kl]))
		{
			if (comparation(pq->vect[kl], pq->vect[kr]))
			{
				swap(&pq->vect[kr], &pq->vect[numElem]);
				numElem = kr;
				goto skip;
			}
			swap(&pq->vect[numElem], &pq->vect[kl]);
			numElem = kl;
			goto skip;
		}
		if (comparation(pq->vect[numElem], pq->vect[kr]))
		{
			swap(&pq->vect[numElem], &pq->vect[kr]);
			numElem = kr;
			goto skip;
		}
		break;
	skip:;
		kl = numElem * 2 + 1;
		kr = numElem * 2 + 2;
	}

	return t;
}