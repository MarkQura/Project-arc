#ifndef NODE_H
#define NODE_H

typedef struct _node *node;

/***********************************************
newNode - creates new node.
Parameters:
    elem - element of the node
Retorno: created node
Pre-condicoes: list != NULL
***********************************************/
node newNode(void *elem);

/***********************************************
destroyNode - Frees the memory occupied by the instance of the structure associated to the node.
Parameters:
    elem - element of the node
    list - the list to be destroyed
Retorno:
Pre-condicoes: elem != NULL, list != NULL
***********************************************/
void destroyNode(node aux);

/***********************************************
nextNode - gives the next node.
Parameters:
    aux - node to take as reference
Retorno: next node
Pre-condicoes: aux != NULL
***********************************************/
node nextNode(node aux);

/***********************************************
prevNode - gives the previous node.
Parameters:
    aux - node to take as reference
Retorno: the node before
Pre-condicoes: aux != NULL
***********************************************/
node prevNode(node aux);

void *getElem(node aux);

#endif