#include <stdlib.h>
#include "iterator.h"
#include "Node.h"

struct _iterador {
    node head, tail, item;
    int size, reverse, current;
};

iterator new_iterador(node head, node tail, int size, int reverse) {
    iterator it = (iterator) malloc(sizeof(struct _iterador));
    if (it == NULL) return NULL;
    it->head = head;
    it->tail = tail;
    it->size = size;
    it->reverse = reverse;
    it->current = 0;
    it->item = reverse ? tail : head;
    return it;
}

void destroy_iterator(iterator it) {
    destroiNode(it->head);
    destroiNode(it->tail);
    free(it);
}

int has_next_item(iterator it) {
    if (it->current == it->size) return 0;
    return 1;
}

void* next_item(iterator it) {
    it->item = (it->reverse * previousNode(it->item)) + (!(it->reverse) * nextNode(it->item)) \
    * (it->current > 0) + (!it->current)*it->item;
    it->current++;
    return getData(it->item);
}