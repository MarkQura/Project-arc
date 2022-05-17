#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct _linkedList* linkedList; 

/***********************************************
newList - Creation of the structure instance associated to a sequence.
Parameters:

Retorno: pointer of linked list
Pre-condicoes:  
***********************************************/
linkedList newList();

/***********************************************
destroyList - Frees the memory occupied by the instance of the structure associated to the sequence.
Parameters:
    list - the list to be destroyed
Retorno: 
Pre-condicoes: list != NULL
***********************************************/
void destroyList(linkedList list);

/***********************************************
destroyListAndElems - Frees the memory occupied by the instance of the structure associated to the sequence and its elements.	
Parameters:
    list - sequence to destroy
	destroy - function to destroy the elements in the sequence.
Retorno: 
Pre-condicoes: list != NULL
***********************************************/
void destroyListAndElems(linkedList list, void (*destroy)(void *));

/***********************************************
addHead - Adds the given element too the firts position of the sequence.	
Parameters:
    list - sequence
	head - element's pointer
Retorno: 
Pre-condicoes: list != NULL && head != NULL
***********************************************/
void addHead(linkedList list, node head);

/***********************************************
insert - Adds the given element in the i-th sequence position.
Parameters:
	list - sequence
	newNode - element's pointer
	index - position in the sequence
Return:
Pre-conditions: list != NULL && index>0 && index<= sizeCertified
***********************************************/
void insert(linkedList list, node newNode, int index);

/***********************************************
append - Adds the given element too the last position of the sequence.	
Parameters:
    list - sequence
	tail - element's pointer
Retorno: 
Pre-condicoes: list != NULL && tail != NULL
***********************************************/
void append(linkedList list, node tail);

/***********************************************
moveHead - Moves the given element too the firts position of the sequence.	
Parameters:
    list - sequence
	head - element's pointer
Retorno: 
Pre-condicoes: list != NULL && head != NULL
***********************************************/
void moveHead(linkedList list, node head);

/***********************************************
moveToIndex - Moves the given element in the i-th sequence position.
Parameters:
	list - sequence
	moveNode - element's pointer
	index - position in the sequence
Return:
Pre-conditions: list != NULL && moveNode != NULL && index>0 && sizeCertified
***********************************************/
void moveToIndex(linkedList list, node moveNode, int index);

/***********************************************
moveToTail - Moves the given element too the last position of the sequence.	
Parameters:
    list - sequence
	tail - element's pointer
Retorno: 
Pre-condicoes: list != NULL && tail != NULL
***********************************************/
void moveToTail(linkedList list, node tail);

/***********************************************
sizeList - Checks the number of elements in the sequence.
Parameters:
	list - sequence
Return: number of elements in the sequence
Pre-conditions: list != NULL
***********************************************/
int sizeList(linkedList list);

/***********************************************
sizeCertified - Checks the number of certified elements in the sequence.
Parameters:
	list - sequence
Return: number of certified elements in the sequence
Pre-conditions: list != NULL
***********************************************/
int sizeCertified(linkedList list);

/***********************************************
sizeBanned - Checks the number of banned elements in the sequence.
Parameters:
	list - sequence
Return: number of banned elements in the sequence
Pre-conditions: list != NULL
***********************************************/
int sizeBanned(linkedList list);

/***********************************************
certifiedIterator - creates and return an iterator of a sequence of certified elements.
Parameters:
	list - sequence
Retorno: iterator of a sequence
Pre-condicoes: list != NULL
***********************************************/
iterator certifiedIterator(linkedList list);

/***********************************************
certifiedIterator - creates and return an iterator of a sequence of banned elements.
Parameters:
	list - sequence
Retorno: iterator of a sequence
Pre-condicoes: list != NULL
***********************************************/
iterator listIterator(linkedList list);

void* existElem(linkedList list, void* elem);

void sortList(linkedList list);


#endif // LINKEDLIST_H
