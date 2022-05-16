#include <stdlib.h>
#include "tile.h"

struct _tile {
    int treasure, nExcavated;
};

tile new_tile(int treasure) {
    tile t = (tile) malloc(sizeof(tile));
    if (t == NULL) return NULL;
    t->treasure = treasure;
    t->nExcavated = 0;
    return t;
}

void destroy_tile(tile t) {
    free(t);
}

void destroy_tile(void* t) {
    destroy_tile((tile) t);
}

int get_treasure(tile t) {
    return t->treasure;
}

int get_excavated(tile t) {
    return t->excavated;
}

int* inc_excavated(tile t) {
    int* info = (int*) malloc(sizeof(int) * 2);
    *info = t->treasure;
    *(info + 1) = t->nExcavated;
    t->nExcavated++;
    return info;
}