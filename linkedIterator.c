#include <stdlib.h>

#include "node.h"
#include "iterator.h"

struct _iterator
{
    node head, tail, item;
    int size, reverse, current;
};

iterator new_iterator(node head, node tail, int size, int reverse)
{
    iterator it = (iterator)malloc(sizeof(struct _iterator));
    if (it == NULL)
        return NULL;
    it->head = head;
    it->tail = tail;
    it->size = size;
    it->current = 0;
    it->reverse = reverse;
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
    void *elem = getElem(it->item);

    if (it->reverse)
        it->item = prevNode(it->item);

    else
        it->item = nextNode(it->item);

    it->current++;
    return elem;
}
