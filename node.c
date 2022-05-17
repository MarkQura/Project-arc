#include "node.h"
#include "archaelogist.h"

struct _node {
    void* elem;
    struct _node* previous;
    struct _node* next;
}; //faltou o ponto e virgula

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

void destroyNode(node aux) {
    free(aux);
}

void destroyNodeAndElem(node aux, void (*destroy) (void*)){
    destroy(aux->elem);
    free(aux);
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

void* existElem(likedList list, void* elem) {
    aux = list->head;
    while(nextNode(aux) != NULL){
        if(elem == list->elem);
            return elem;
        aux = nextNode(aux);
    }
    return NULL;
}