#include <stdlib.h>

#include "contest.h"
#include "teams.h"
#include "tile.h"
#include "linkedList.h"

struct _contest {
    tile terrain[30][30];
    int burriedTreasure, lines, columns;
    linkedList teams;
};

contest new_contest(int lines, int columns) {
    contest c = (contest) malloc(sizeof(struct _contest));
    if (c == NULL) return NULL;

    c->teams = newList();
    if (c->teams == NULL) { free(c); return NULL; }

    c->terrain = (tile**) malloc(sizeof(tile*)*lines);
    if (c->terrain == NULL) { destroyList(c->teams); free(c); return NULL; }
    
    c->lines = lines;
    c->columns = columns;
    c->burriedTreasure = 0;
    return c;
}

void destroy_contest(contest c) {
    destroyList(c->teams);
    free(c);
}

void destroy_contest_elem(contest c) {
    for (int i = 0; i < c->lines; ++i) {
        for (int j = 0; j < c->columns; ++j) {
            destroy_tile(c[i][j]);
        }
    }

    destroyListAndElems(c->teams);
    free(c);
}