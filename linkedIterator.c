#include <stdlib.h>

#include "node.h"
#include "iterator.h"

struct _iterador
{
    node head, tail, item;
    int size, reverse, current;
};

iterator new_iterador(node head, node tail, int size, int reverse)
{
    iterator it = (iterator)malloc(sizeof(struct _iterador));
    if (it == NULL)
        return NULL;
    it->tail = tail;
    it->head = head;
    it->size = size;
    it->reverse = reverse;
    it->current = 0;
    it->item = reverse ? tail : head;
    return it;
}

void destroy_iterator(iterator it)
{
    destroyNode(it->head);
    destroyNode(it->tail);
    free(it);
}

int has_next_item(iterator it)
{
    if (it->current == it->size)
        return 0;
    return 1;
}

void *next_item(iterator it)
{
    it->item = (it->reverse * prevNode(it->item)) + (!(it->reverse) * nextNode(it->item)) * (it->current > 0) + (!it->current) * it->item;
    it->current++;
    return getElem(it->item);
}
