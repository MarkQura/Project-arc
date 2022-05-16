#include "node.h"
#include "linkedList.h"

struct _node {
    archaelogist elem;
    node previous;
    node next;
}

node newNode(archaelogist elem){
    node newNode;
    aux = (struct Node*) malloc(sizeof(struct Node));
    if(aux == NULL)
        return NULL;
    newNode->elem = elem;
    newNode->previous = NULL;
    newNode->next = NULL;
    return aux;
}

void destroyNode(archaelogist elem, linkedList list){
    node aux;
    aux = nodeFromElem(elem, list);
    if(aux != NULL){
        setNextNode(aux->previous, aux->next);
        setPrevNode(aux->next, aux->previous);
    }
    free(aux);
}

nodeFromElem(archaelogist elem, LinkedList list){
    node aux = list->head;
	while (aux->elem != elem || aux->next != NULL)
		aux = aux->next;
}

node nextNode(node aux){
    return aux->next;
}

node prevNode(node aux){
    return aux->previous;
}
