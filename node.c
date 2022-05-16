#include "linkedList.h"
#include "node.h"
#include "archaelogist.h"

struct _node {
    void* elem;
    struct _node* previous;
    struct _node* next;
}

node newNode(void* elem){
    node aux;
    aux = (node)malloc(sizeof(struct _node));
    if(aux == NULL)
        return NULL;
    aux->elem = elem;
    aux->previous = NULL;
    aux->next = NULL;
    return aux;
}

void destroyNode(node aux, linkedList list){
    if(aux != NULL){
        setNextNode(aux->previous, aux->next);
        setPrevNode(aux->next, aux->previous);
        free(aux);
    }
}

node nextNode(node aux){
    return aux->next;
}

node prevNode(node aux){
    return aux->previous;
}

void* checkElem(node aux){
    return aux->elem;
}