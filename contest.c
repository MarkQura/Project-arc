#include <stdlib.h>

#include "contest.h"
#include "team.h"
#include "tile.h"
#include "linkedList.h"
#include "iterator.h"

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
    for (int i = 0; i < c->line; ++i) {
        for (int j = 0; j < c->columns; ++j) {
            destroy_tile(c[i][j]);
        }
    }

    destroyListAndElems(c->teams);
    free(c);
}

team has_team(contest c, char* name) {
    existElem(c->teams, name, team_name_gen);
}

void set_tile_treasure(contest c, int line, int column, int treasure) {
    tile t = new_tile(treasure);
    c->terrain[line][column] = t;
    c->burriedTreasure += treasure;
}

int get_lines(contest c) {
    return c->lines;
}

int get_columns(contest c) {
    return c->columns;
}

tile get_tile(contest c, int line, int column) {
    return c->terrain[line][column];
}

void sort_teams(contest c) {
    mergeSort(c->teams, get_team_score_gen);
}

iterator contest_iterator (contest c) {
    return listIterator(c->teams);
}