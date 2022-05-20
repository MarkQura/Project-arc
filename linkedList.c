#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "iterator.h"
#include "linkedList.h"

struct _linkedList
{
    node head, tail;
    int nElemsTotal, nCertifiedElems;
};

linkedList newList()
{
    linkedList list = (linkedList)malloc(sizeof(struct _linkedList));
    list->head = NULL;
    list->tail = NULL;
    list->nElemsTotal = 0;
    list->nCertifiedElems = 0;
    return list;
}

void destroyList(linkedList list)
{
    node aux = list->head;
    while (aux != NULL)
    {
        list->head = nextNode(aux);
        destroyNode(aux);
        aux = list->head;
    }
    free(list);
}

void destroyListAndElems(linkedList list, void (*destroy)(void *))
{
    node aux = list->head;
    while (aux != NULL)
    {
        list->head = nextNode(aux);
        destroyNodeAndElems(aux, destroy);
        aux = list->head;
    }
    free(list);
}

node locateIndex(linkedList list, int index)
{
    node aux = list->head;
    for (int i = 0; i < index; ++i)
        aux = nextNode(aux);
    return aux;
}

void addHead(linkedList list, void *elem)
{
    node head = newNode(elem);
    if (!list->nElemsTotal)
    {
        list->head = head;
        list->tail = head;
        list->nElemsTotal++;
        return;
    }
    setNextNode(head, list->head);
    setPrevNode(list->head, head);
    list->head = head;
    list->nElemsTotal++;
}

void insert(linkedList list, void *elem, int index)
{
    if (!index)
    {
        addHead(list, elem);
        return;
    }
    if (index == list->nCertifiedElems)
    {
        append(list, elem);
        return;
    }
    node nNode = newNode(elem);
    list->nElemsTotal++;
    node aux = locateIndex(list, index);
    setNextNode(nNode, aux);
    setNextNode(prevNode(aux), nNode);
    setPrevNode(nNode, prevNode(aux));
    setPrevNode(aux, nNode);
}

void append(linkedList list, void *elem)
{
    node tail = newNode(elem);
    if (!list->nElemsTotal)
    {
        list->head = tail;
        list->tail = tail;
        list->nElemsTotal++;
        return;
    }
    setPrevNode(tail, list->tail);
    setNextNode(list->tail, tail);
    list->tail = tail;
    list->nElemsTotal++;
}

void moveHead(linkedList list, node head)
{
    setNextNode(prevNode(head), nextNode(head));
    setPrevNode(nextNode(head), prevNode(head));
    setPrevNode(head, NULL);
    if (!list->nElemsTotal)
    {
        list->head = head;
        list->tail = head;
        setNextNode(head, NULL);
        return;
    }
    setNextNode(head, list->head);
    setPrevNode(list->head, head);
    list->head = head;
}

void moveToIndex(linkedList list, node moveNode, int index)
{
    if (!index)
    {
        moveHead(list, moveNode);
        return;
    }
    setNextNode(prevNode(moveNode), nextNode(moveNode));
    setPrevNode(nextNode(moveNode), prevNode(moveNode));
    node aux = locateIndex(list, index);
    setNextNode(prevNode(aux), moveNode);
    setPrevNode(moveNode, prevNode(aux));
    setPrevNode(aux, moveNode);
    setNextNode(moveNode, aux);
}

void moveToTail(linkedList list, node tail)
{
    setNextNode(prevNode(tail), nextNode(tail));
    setPrevNode(nextNode(tail), prevNode(tail));
    setNextNode(tail, NULL);
    if (!list->nElemsTotal)
    {
        list->head = tail;
        list->tail = tail;
        setPrevNode(tail, NULL);
        return;
    }
    setPrevNode(tail, list->tail);
    setNextNode(list->tail, tail);
    list->tail = tail;
}

int sizeList(linkedList list)
{
    return list->nElemsTotal;
}

int sizeCertified(linkedList list)
{
    return list->nCertifiedElems;
}

int sizeBanned(linkedList list)
{
    return (list->nElemsTotal - list->nCertifiedElems);
}

node getHead(linkedList list)
{
    return (list->head);
}

node getTail(linkedList list)
{
    return (list->tail);
}

iterator certifiedIterator(linkedList list)
{
    node auxHead = newNode(getElem(list->head));
    setNextNode(auxHead, nextNode(list->head));
    node auxTail = newNode(getElem(list->tail));
    setPrevNode(auxHead, prevNode(list->tail));
    iterator it = new_iterator(auxHead, auxTail, list->nCertifiedElems, 0);
    return it;
}

iterator listIterator(linkedList list)
{
    node auxHead = newNode(getElem(list->head));
    setNextNode(auxHead, nextNode(list->head));
    node auxTail = newNode(getElem(list->tail));
    setPrevNode(auxHead, prevNode(list->tail));
    iterator it = new_iterator(auxHead, auxTail, list->nElemsTotal, 0);
    return it;
}

// split the linked list in the middle
node partition(node head)
{
    node fast, slow;
    fast = slow = head;

    while (nextNode(fast) != NULL && nextNode(nextNode(fast)) != NULL)
    {
        fast = nextNode(nextNode(fast));
        slow = nextNode(slow);
    }

    fast = nextNode(slow);
    setNextNode(slow, NULL);
    return fast;
}

// junta as partições da lista ligada por ordem
node merge(node first, node second, int (*getScore)(void *elem))
{
    if (first == NULL)
        return second;
    if (second == NULL)
        return first;

    if (getScore(getElem(first)) < getScore(getElem(second)))
    {
        setNextNode(first, merge(nextNode(first), second, getScore));
        setPrevNode(nextNode(first), first);
        setPrevNode(first, NULL);
        return first;
    }
    else
    {
        setNextNode(second, merge(first, nextNode(second), getScore));
        setPrevNode(nextNode(second), second);
        setPrevNode(second, NULL);
        return second;
    }
}

node mergeSort(node head, int (*getScore)(void *elem))
{
    if (head == NULL || nextNode(head) == NULL)
        return head;

    node second = partition(head);

    head = mergeSort(head, getScore);
    second = mergeSort(second, getScore);

    return merge(head, second, getScore);
}

void destroyBanned(linkedList list, void (*destroy)(void *elem))
{
    int banned = list->nElemsTotal - list->nCertifiedElems;
    node aux = list->tail;
    for (int i = 0; i < banned; ++i)
    {
        list->tail = prevNode(aux);
        destroyNodeAndElems(aux, destroy);
        aux = list->head;
    }
}

void sortList(linkedList list, int (*getScore)(void *elem), void (*destroy)(void *elem))
{
    destroyBanned(list, destroy);
    list->head = mergeSort(list->head, getScore);
}

node existElem(linkedList list, char *name, char *(*getName)(void *))
{
    node aux = list->head;
    while (aux != NULL)
    {
        if (!strcmp(name, getName(getElem(aux))))
            return aux;
        aux = nextNode(aux);
    }
    return NULL;
}
