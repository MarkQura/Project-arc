#include "node.h"
#include "iterator.h"
#include "linkedList.h"

struct _linkedList{
    node head, tail;
    int nElemsTotal, nCertifiedElems;
}

linkedList newList(){
    linkedList list = (linkedList)malloc(sizeof(struct _linkedList));
    list->head = NULL;
    list->tail = NULL;
    list->nElemsTotal = 0;
    list->nBanElems = 0;
    return list;
}

void destroyList(linkedList list){
    node aux = list->head;
	while (aux != NULL){
		list->head = nextNode(aux);
		destroyNode(aux);
		aux = list->head;
	}
	free(list);
}

void destroySeqAndElems(linkedList list, void (*destroy)(void *)){
	node  aux = list->head;
	while (aux != NULL){
		list->head = nextNode(aux);
		destroyElemAndNode(aux,destroy);//a fazer ainda com node.h
		aux = list->head;
	}
	free(list);
}

node locateIndex(linkedList list, int index){
    node aux = s->head;
    for(int i = 0; i < index; ++i)
        aux = nextNode(aux);
    return aux;
}

void addHead(linkedList list, node head){
    list->nElemsTotal++;
    setPrevNode(head, NULL);
    if(!list->nElemsTotal){
        list->head = head;
        list->tail = head;
        setNextNode(head, NULL);
        return;
    }
    setNextNode(head, list->head);
    setPrevNode(list->head, head);
    list->head = head;
}

void insert(linkedList list, node newNode, int index){
    if(!index){
        addHead(list, newNode);
        return;
    }
    if(index == nCertifiedElems){
        append(list, newNode);
        return;
    }
    list->nElemsTotal++;
    node aux = locateIndex(list, index);
    setNextNode(newNode, aux);
    setNextNode(prevNode(aux), newNode);
    setPrevNode(newNode, prevNode(aux));
    setPrevNode(aux, newNode);
}

void append(linkedList list, node tail){
    list->nElemsTotal++;
    setNextNode(tail, NULL);
    if(!list->nElemsTotal){
        list->head = tail;
        list->tail = tail;
        setPrevNode(tail, NULL);
        return;
    }
    setPrevNode(tail, list->tail);
    setNextNode(list->tail, tail);
    list->tail = tail;
}

void moveHead(linkedList list, node head){
    setNextNode(prevNode(moveNode), nextNode(moveNode));
    setPrevNode(nextNode(moveNode), prevNode(moveNode));
    setPrevNode(head, NULL);
    if(!list->nElemsTotal){
        list->head = head;
        list->tail = head;
        setNextNode(head, NULL);
        return;
    }
    setNextNode(head, list->head);
    setPrevNode(list->head, head);
    list->head = head;
}

void moveToIndex(linkedList list, node moveNode, int index){
    if(!index){
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

void moveToTail(linkedList list, node tail){
    setNextNode(prevNode(moveNode), nextNode(moveNode));
    setPrevNode(nextNode(moveNode), prevNode(moveNode));
    setNextNode(tail, NULL);
    if(!list->nElemsTotal){
        list->head = tail;
        list->tail = tail;
        setPrevNode(tail, NULL);
        return;
    }
    setPrevNode(tail, list->tail);
    setNextNode(list->tail, tail);
    list->tail = tail;
}

int sizeList(linkedList list){
    return list->nElemsTotal;
}

int sizeCertified(linkedList list){
    return list->nCertifiedElems;
}

int sizeBanned(linkedList list){
    return (list->nElemsTotal - list->nCertifiedElems);
}

iterator certifiedIterator(linkedList list){
    iterador it = criaIterador(list->head, list->tail, list->nCertifiedElems, 0);
	return it;
}

iterator BannedIterator(){
    iterador it = criaIterador(list->head, list->tail, list->nCertifiedElems, 1);
	return it;
}
