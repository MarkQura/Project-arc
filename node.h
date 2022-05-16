typedef struct _node* node; 

/***********************************************
newNode - creates new node.
Parameters:
    elem - element of the node
Retorno: created node
Pre-condicoes: list != NULL
***********************************************/
node newNode(archaelogist elem);

/***********************************************
destroyNode - Frees the memory occupied by the instance of the structure associated to the node.
Parameters:
    elem - element of the node
    list - the list to be destroyed
Retorno: 
Pre-condicoes: elem != NULL, list != NULL
***********************************************/
void destroyNode(archaelogist elem, linkedList list);

/***********************************************
nodeFromElem - gives the node from the element.
Parameters:
    elem - element of the node
    list - the list to be destroyed
Retorno: node that contains the element 
Pre-condicoes: elem != NULL, list != NULL
***********************************************/
node nodeFromElem(archaelogist elem, LinkedList list);

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
